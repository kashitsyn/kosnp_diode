#include <ExceptionHelper.hpp>

#include <cassert>
#include <cerrno>
#include <cstring>

#include <iostream>
#include <stdexcept>
#include <system_error>

#ifdef __KOS__

#include <nk/errno.h>

#endif // __KOS__

#include <BaseException.hpp>

using namespace std::string_literals;

namespace diode
{

// static
std::string ExceptionHelper::CreateErrorMessage(const std::exception_ptr& eptr)
noexcept
{
    try
    {
        assert(eptr);

        if (eptr)
        {
            std::rethrow_exception(eptr);
        }

        assert(!"Unreachable");
        return "<UNREACHABLE>"s;
    }
    catch (const BaseException& e)
    {
        return "<INTERNAL>"s;
    }
    catch (const std::ios_base::failure& e)
    {
        return errno ? std::strerror(errno) : e.code().message();
    }
    catch (const std::system_error& e)
    {
        return e.code().message();
    }
    catch (const std::exception& e)
    {
        return e.what();
    }
    catch(...)
    {
        return "<UNKNOWN>"s;
    }
}

// static
void ExceptionHelper::LogErrorMessage(const std::exception_ptr& eptr) noexcept
{
    try
    {
        assert(eptr);

        if (eptr)
        {
            std::rethrow_exception(eptr);
        }
    }
    catch (const BaseException& e)
    {
        std::cerr << "Error: "
            << "Catch unhandled internal exception"
            << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: "
            << "Catch unhandled standard exception: "
            << CreateErrorMessage()
            << std::endl;
    }
    catch (...)
    {
        std::cerr << "Error: "
            << "Catch unhandled unknown exception"
            << std::endl;
    }
}

#ifdef __KOS__

// static
void ExceptionHelper::HandleNkReturnCode(const nk_err_t rc, const int resRc,
    std::string_view methodName, std::function<void(int)> checkRc)
{
    switch (rc)
    {
    case NK_EOK:
        switch (resRc)
        {
        case 0:
            break;
        case -1:
            throw std::runtime_error{
                std::string{methodName} + ": <GENERIC>"
            };
        case -2:
            throw BaseException{};
            break;
        default:
            if (checkRc)
            {
                checkRc(resRc);
            }
            throw std::runtime_error{
                std::string{methodName} + ": <UNKNOWN>"
            };
        }
        break;
    default:
        throw std::runtime_error{
            std::string{methodName} + ": IPC failed"
        };
    }
}

#endif // __KOS__

// static
void ExceptionHelper::LogIgnoreMessage() noexcept
{
    std::cerr << "Info: "
        << "Ignoring the exception and continue"
        << std::endl;
}

} // namespace diode
