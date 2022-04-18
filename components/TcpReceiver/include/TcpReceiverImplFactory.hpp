#ifndef DIODE_TCP_RECEIVER_IMPL_FACTORY_HPP
#define DIODE_TCP_RECEIVER_IMPL_FACTORY_HPP

#include <functional>
#include <memory>

#include <DataStorage.hpp>
#include <Consumer.hpp>
#include <TcpReceiver.hpp>

namespace diode
{

struct TcpReceiverImplFactory
{

public:

    TcpReceiverImplFactory();

    std::unique_ptr<TcpReceiver>
    operator()(
        std::shared_ptr<const DataStorage> dataStorage,
        std::shared_ptr<Consumer> consumer
    );

};

} // namespace diode

#endif // DIODE_TCP_RECEIVER_IMPL_FACTORY_HPP
