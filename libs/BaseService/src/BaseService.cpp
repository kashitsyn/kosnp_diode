#include <BaseService.hpp>

#include <cassert>

#include <iostream>

#include <BaseException.hpp>
#include <ExceptionHelper.hpp>

namespace diode
{

void BaseService::Start()
{
    switch (m_state)
    {
    case State::Started:
    case State::Defunct:
        return;
    case State::Stopped:
        break;
    case State::Starting:
    case State::Stopping:
        assert(!"Unreachable");
        throw std::logic_error(
            "diode::BaseService::Start(): invalid state"
        );
    }

    try
    {
        DoStart();

        assert(m_state == State::Started);
        assert(m_controlStatus == Status::OK);
        return;
    }
    catch (const BaseException& e)
    {
        try
        {
            DoRollback();
        }
        catch (...)
        {
            assert(m_state == State::Defunct);
            assert(m_controlStatus == Status::FailedToRollback);
            throw;
        }

        assert(m_state == State::Stopped);
        assert(m_controlStatus == Status::FailedToStart);
        throw;
    }
    catch (...)
    {
        assert(m_state == State::Defunct);
        assert(m_controlStatus == Status::FailedToStart);
        throw;
    }

    assert(!"Unreachable");
}

void BaseService::Stop()
{
    switch (m_state)
    {
    case State::Stopped:
    case State::Defunct:
        return;
    case State::Started:
        break;
    case State::Starting:
    case State::Stopping:
        assert(!"Unreachable");
        throw std::logic_error(
            "diode::BaseService::Stop(): invalid state"
        );
    }

    try
    {
        DoStop();

        assert(m_state == State::Stopped);
        assert(m_controlStatus == Status::OK);
        return;
    }
    catch (...)
    {
        assert(m_state == State::Defunct);
        assert(m_controlStatus == Status::FailedToStop);
        throw;
    }

    assert(!"Unreachable");
}

void BaseService::DoStart()
{
    assert(m_state == State::Stopped);

    try
    {
        std::cout << "Info: "
            << "Starting the " << m_name << " service"
            << std::endl;
        m_state = State::Starting;
        m_controlStatus = Status::OK;
        DoUp();
        m_state = State::Started;
        std::cout << "Info: "
            << "The " << m_name << " service has been started"
            << std::endl;
    }
    catch (const BaseException& e)
    {
        std::cerr << "Error: "
            << "The " << m_name << " service has been failed to start: "
            << ExceptionHelper::CreateErrorMessage()
            << std::endl;
        throw;
    }
    catch (...)
    {
        std::cerr << "Error: "
            << "The " << m_name << " service has been failed to start: "
            << ExceptionHelper::CreateErrorMessage()
            << std::endl;
        m_state = State::Defunct;
        m_controlStatus = Status::FailedToStart;
        std::cout << "Info: "
            << "The " << m_name << " service is now defunct"
            << std::endl;
        throw;
    }
}

void BaseService::DoRollback()
{
    assert(m_state == State::Starting);

    try
    {
        std::cout << "Info: "
            << "Rolling back the " << m_name << " service"
            << std::endl;
        m_state = State::Stopping;
        m_controlStatus = Status::FailedToStart;
        DoDown();
        m_state = State::Stopped;
        std::cout << "Info: "
            << "The " << m_name << " service has been rolled back"
            << std::endl;
    }
    catch (...)
    {
        std::cerr << "Error: "
            << "The " << m_name << " service has been failed to roll back: "
            << ExceptionHelper::CreateErrorMessage()
            << std::endl;
        m_state = State::Defunct;
        m_controlStatus = Status::FailedToRollback;
        std::cout << "Info: "
            << "The " << m_name << " service is now defunct"
            << std::endl;
        throw;
    }
}

void BaseService::DoStop()
{
    assert(m_state == State::Started);

    try
    {
        std::cout << "Info: "
            << "Stopping the " << m_name << " service"
            << std::endl;
        m_state = State::Stopping;
        m_controlStatus = Status::OK;
        DoDown();
        m_state = State::Stopped;
        std::cout << "Info: "
            << "The " << m_name << " service has been stopped"
            << std::endl;
    }
    catch (...)
    {
        std::cerr << "Error: "
            << "The " << m_name << " service has been failed to stop: "
            << ExceptionHelper::CreateErrorMessage()
            << std::endl;
        m_state = State::Defunct;
        m_controlStatus = Status::FailedToStop;
        std::cout << "Info: "
            << "The " << m_name << " service is now defunct"
            << std::endl;
        throw;
    }
}

} // namespace diode
