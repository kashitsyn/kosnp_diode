#ifndef DIODE_INTERRUPTER_IMPL_HPP
#define DIODE_INTERRUPTER_IMPL_HPP

#include <csignal>

#include <InterrupterImplFactory.hpp>

namespace diode
{

class InterrupterImpl : public Interrupter
{

public:

    explicit
    InterrupterImpl()
    {
        SingleInterrupterContext::GetInstance();
    }

    // Interrupter

    void Wait() const override
    {
        SingleInterrupterContext::GetInstance().Wait();
    }

private:

    class SingleInterrupterContext
    {

    private:

        explicit
        SingleInterrupterContext();

        ~SingleInterrupterContext() = default;

    public:

        SingleInterrupterContext(const SingleInterrupterContext& other) = delete;
        SingleInterrupterContext& operator=(const SingleInterrupterContext& other) = delete;

        SingleInterrupterContext(SingleInterrupterContext&& other) = delete;
        SingleInterrupterContext& operator=(SingleInterrupterContext&& other) = delete;

        static
        SingleInterrupterContext& GetInstance()
        {
            static SingleInterrupterContext s_instance{};
            return s_instance;
        }

        void Wait() const;

    private:

        sigset_t m_signalMask{};

    };

};

} // namespace diode

#endif // DIODE_INTERRUPTER_IMPL_HPP
