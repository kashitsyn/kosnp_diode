#ifndef DIODE_STOP_TOKEN_HPP
#define DIODE_STOP_TOKEN_HPP

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>
#include <utility>

namespace diode
{

class StopToken
{

    friend class StopSource;

public:

    StopToken() noexcept = default;

    [[nodiscard]]
    bool IsStopRequested() const noexcept
    {
        return m_state && m_state->isStopRequested;
    }

    void Wait() const
    {
        if (!m_state)
        {
            return;
        }

        auto lock = std::unique_lock{m_state->m_mutex};
        m_state->m_cv.wait(lock, [this] { return IsStopRequested(); });
    }

    template<typename Clock, typename Duration>
    bool WaitUntil(const std::chrono::time_point<Clock, Duration>& timeout) const
    {
        if (!m_state)
        {
            return false;
        }

        auto lock = std::unique_lock{m_state->m_mutex};
        return m_state->m_cv.wait_until(lock, timeout, [this] { return IsStopRequested(); });
    }

    template<typename Rep, typename Period>
    bool WaitFor(const std::chrono::duration<Rep, Period>& interval) const
    {
        return WaitUntil(std::chrono::steady_clock::now() + interval);
    }

protected:

    struct State
    {
        std::mutex m_mutex{};
        std::condition_variable m_cv{};
        std::atomic<bool> isStopRequested = false;
    };

    explicit
    StopToken(std::shared_ptr<State> state)
        : m_state{std::move(state)}
    {}

    std::shared_ptr<State> m_state = nullptr;

};

struct NonStopToken : public StopToken
{
    NonStopToken() : StopToken{std::make_shared<State>()} {}
};

} // namespace diode

#endif // DIODE_STOP_TOKEN_HPP
