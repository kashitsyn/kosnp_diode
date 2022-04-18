#ifndef DIODE_BASE_SERVICE_HPP
#define DIODE_BASE_SERVICE_HPP

#include <Service.hpp>

namespace diode
{

class BaseService : public virtual Service
{

public:

    explicit
    BaseService(std::string name)
        : m_name{std::move(name)}
    {}

    ~BaseService() override = default;

    BaseService(const BaseService&) = delete;
    BaseService& operator=(const BaseService&) = delete;

    BaseService(BaseService&&) = delete;
    BaseService& operator=(BaseService&&) = delete;

    // Service

    std::string GetName() const override
    {
        return m_name;
    }

    void SetName(std::string name) override
    {
        m_name = std::move(name);
    }

    State GetState() const override
    {
        return m_state;
    }

    Status GetStatus() const override
    {
        return m_state == State::Started ?
            GetOperatingStatus() : m_controlStatus;
    }

    void Start() override;

    void Stop() override;

protected:

    virtual
    void DoUp() = 0;

    virtual
    void DoDown() = 0;

    virtual
    Status GetOperatingStatus() const
    {
        return Status::OK;
    }

private:

    void DoStart();

    void DoRollback();

    void DoStop();

    std::string m_name{};
    State m_state = State::Stopped;
    Status m_controlStatus = Status::OK;

};

} // namespace diode

#endif // DIODE_BASE_SERVICE_HPP
