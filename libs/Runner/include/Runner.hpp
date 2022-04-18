#ifndef DIODE_RUNNER_HPP
#define DIODE_RUNNER_HPP

#include <utility>

#include <ExceptionHelper.hpp>

namespace diode
{

template<typename Coordinator>
class Runner
{

public:

    static
    int Run() noexcept
    {
        try
        {
            auto runner = Runner<Coordinator>{};
            runner.DoWork();
            runner.Shutdown();
            return runner.m_status;
        }
        catch (...)
        {
            return Runner::HandleException();
        }
    }

private:

    Runner() = default;

    void DoWork() noexcept
    {
        try
        {
            m_coordinator.OnStartup();
            m_coordinator.Wait();
        }
        catch (...)
        {
            UpdateStatus(Runner::HandleException());
        }
    }

    void Shutdown() noexcept
    {
        try
        {
            m_coordinator.OnShutdown();
        }
        catch (...)
        {
            UpdateStatus(Runner::HandleException());
        }
    }

    static
    int HandleException() noexcept
    {
        ExceptionHelper::LogErrorMessage();
        return EXIT_FAILURE;
    }

    void UpdateStatus(int status) noexcept
    {
        // NOTE: Do not update previous non-success status.
        if (m_status == EXIT_SUCCESS)
        {
            m_status = status;
        }
    }

private:

    int m_status = EXIT_SUCCESS;
    Coordinator m_coordinator{};

};

} // namespace diode

#endif // DIODE_RUNNER_HPP
