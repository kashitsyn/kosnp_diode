#include "ServiceManagerImpl.hpp"

#include <string>
#include <utility>

#include <ExceptionHelper.hpp>

using namespace std::string_literals;

namespace diode
{

ServiceManagerImpl::ServiceManagerImpl(
    std::shared_ptr<TcpSender> sender,
    std::shared_ptr<TcpReceiver> receiver
)
    : BaseService("Service Manager"s)
    , m_receiver{std::move(receiver)}
    , m_sender{std::move(sender)}
{}

void ServiceManagerImpl::DoUp()
{
    ExceptionHelper::Ignore([&] { m_sender->Start(); });
    ExceptionHelper::Ignore([&] { m_receiver->Start(); });
}

void ServiceManagerImpl::DoDown()
{
    ExceptionHelper::Ignore([&] { m_receiver->Stop(); });
    ExceptionHelper::Ignore([&] { m_sender->Stop(); });
}

std::unique_ptr<ServiceManager>
ServiceManagerImplFactory::operator()(
    std::shared_ptr<TcpSender> sender,
    std::shared_ptr<TcpReceiver> receiver
)
{
    return std::make_unique<ServiceManagerImpl>(
        std::move(sender),
        std::move(receiver)
    );
}

} // namespace diode
