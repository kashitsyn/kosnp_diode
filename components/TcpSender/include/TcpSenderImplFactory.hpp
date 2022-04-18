#ifndef DIODE_TCP_SENDER_IMPL_FACTORY_HPP
#define DIODE_TCP_SENDER_IMPL_FACTORY_HPP

#include <functional>
#include <memory>

#include <DataStorage.hpp>
#include <TcpSender.hpp>

namespace diode
{

struct TcpSenderImplFactory
{

public:

    explicit
    TcpSenderImplFactory();

    std::unique_ptr<TcpSender>
    operator()(
        std::shared_ptr<const DataStorage> dataStorage
    );

private:

//    std::shared_ptr<const PkiDataManager> m_pkiDataManager;

};

} // namespace diode

#endif // DIODE_TCP_SENDER_IMPL_FACTORY_HPP
