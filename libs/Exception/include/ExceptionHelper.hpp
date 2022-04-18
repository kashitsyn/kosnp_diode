#ifndef DIODE_EXCEPTION_HELPER_HPP
#define DIODE_EXCEPTION_HELPER_HPP

#include <exception>
#include <functional>
#include <string>
#include <string_view>
#include <utility>

#ifdef __KOS__

#include <nk/types.h>

#endif // __KOS__

namespace diode
{

class ExceptionHelper
{

public:

    ExceptionHelper() = delete;

    static
    std::string CreateErrorMessage(
        const std::exception_ptr& eptr = std::current_exception()
    ) noexcept;

    static
    void LogErrorMessage(
        const std::exception_ptr& eptr = std::current_exception()
    ) noexcept;

    template<typename F, typename... Args>
    static
    void Ignore(F&& f, Args&&... args) noexcept
    {
        try
        {
            std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
        }
        catch (...)
        {
            LogErrorMessage();
            LogIgnoreMessage();
        }
    }

#ifdef __KOS__

    static
    void HandleNkReturnCode(nk_err_t rc, int resRc,
        std::string_view methodName, std::function<void(int)> checkRc = {});

#endif // __KOS__

private:

    static
    void LogIgnoreMessage() noexcept;

};

} // namespace diode:core

#endif // DIODE_EXCEPTION_HELPER_HPP
