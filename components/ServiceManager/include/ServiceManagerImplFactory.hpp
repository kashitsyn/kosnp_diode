#ifndef DIODE_CONTROL_SERVICE_MANAGER_IMPL_FACTORY_HPP
#define DIODE_CONTROL_SERVICE_MANAGER_IMPL_FACTORY_HPP

#include <memory>

#include <ServiceManager.hpp>
#include <TcpSender.hpp>
#include <TcpReceiver.hpp>

namespace diode
{

struct ServiceManagerImplFactory
{

    std::unique_ptr<ServiceManager>
    operator()(
        std::shared_ptr<TcpSender> sender,
        std::shared_ptr<TcpReceiver> receiver
    );

};

} // namespace diode

#endif // DIODE_CONTROL_SERVICE_MANAGER_IMPL_FACTORY_HPP
