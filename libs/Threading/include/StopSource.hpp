#ifndef DIODE_STOP_SOURCE_HPP
#define DIODE_STOP_SOURCE_HPP

#include <StopToken.hpp>

namespace diode
{

class StopSource
{

public:

    StopSource()
        : m_state{std::make_shared<StopToken::State>()}
    {}

    [[nodiscard]]
    StopToken GetToken() const noexcept
    {
        return m_state ? StopToken{m_state} : StopToken{};
    }

    bool RequestStop()
    {
        if (!m_state)
        {
            return false;
        }

        auto lock = std::unique_lock{m_state->m_mutex};
        bool false_v = false;
        const auto wasStopRequestedBefore = m_state->isStopRequested.compare_exchange_strong(false_v, true);
        lock.unlock();
        m_state->m_cv.notify_all();

        return wasStopRequestedBefore;
    }

    [[nodiscard]]
    bool IsStopRequested() const noexcept
    {
        return m_state && m_state->isStopRequested;
    }

private:

    std::shared_ptr<StopToken::State> m_state = nullptr;

};

} // namespace diode

#endif // DIODE_STOP_SOURCE_HPP
