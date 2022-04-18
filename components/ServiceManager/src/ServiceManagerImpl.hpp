#ifndef DIODE_CONTROL_SERVICE_MANAGER_IMPL_HPP
#define DIODE_CONTROL_SERVICE_MANAGER_IMPL_HPP

#include <memory>

#include <BaseService.hpp>
#include <Task.hpp>

#include <ServiceManagerImplFactory.hpp>

namespace diode
{

class ServiceManagerImpl
    : public ServiceManager
    , public BaseService
{

public:

    explicit
    ServiceManagerImpl(
        std::shared_ptr<TcpSender> sender,
        std::shared_ptr<TcpReceiver> receiver
    );

protected:

    // BaseService

    void DoUp() override;

    void DoDown() override;

private:

    std::shared_ptr<TcpReceiver> m_receiver{};
    std::shared_ptr<TcpSender> m_sender{};

};

} // namespace diode

#endif // DIODE_CONTROL_SERVICE_MANAGER_IMPL_HPP
