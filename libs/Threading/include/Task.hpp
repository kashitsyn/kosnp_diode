#ifndef DIODE_TASK_HPP
#define DIODE_TASK_HPP

#include <chrono>
#include <functional>
#include <future>
#include <utility>

#include <ExceptionHelper.hpp>
#include <StopSource.hpp>
#include <StopToken.hpp>

namespace diode
{

class Task
{

public:

    using Action = std::function<void(StopToken)>;

    Task() = default;

    explicit
    Task(Action action)
        : m_action{std::move(action)}
    {}

    template<typename F, typename... Args>
    Task(F&& f, Args&&... args)
        : Task{
            Action{
                std::bind(
                    std::forward<F>(f),
                    std::forward<Args>(args)...,
                    std::placeholders::_1
                )
            }
        }
    {}

    ~Task()
    {
        ExceptionHelper::Ignore([&] { Stop(); });
    }

    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;

    Task(Task&&) = default;
    Task& operator=(Task&&) = default;

    void Start()
    {
        if (m_futureCompletion.valid())
        {
            return;
        }

        m_futureCompletion = std::async(std::launch::async,
            m_action, m_stopSource.GetToken());
    }

    void Stop()
    {
        if (!m_futureCompletion.valid())
        {
            return;
        }

        m_stopSource.RequestStop();
        m_futureCompletion.wait();

        m_futureCompletion = std::shared_future<void>{};
        m_stopSource = StopSource{};
    }

    bool IsStarted() const noexcept
    {
        return m_futureCompletion.valid();
    }

    bool IsRunning() const noexcept
    {
        return m_futureCompletion.valid() && m_futureCompletion.wait_for(
            std::chrono::seconds::zero()) == std::future_status::timeout;
    }

    bool IsFailed() const noexcept
    {
        if (m_futureCompletion.valid())
        {
            const auto status = m_futureCompletion.wait_for(
                std::chrono::seconds::zero());
            if (status == std::future_status::ready)
            {
                try
                {
                    m_futureCompletion.get();
                }
                catch (...)
                {
                    return true;
                }
            }
        }

        return false;
    }

private:

    Action m_action{};
    StopSource m_stopSource{};
    std::shared_future<void> m_futureCompletion{};

};

} // namespace diode

#endif // DIODE_TASK_HPP
