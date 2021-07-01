#ifndef HTTPCONNECTIONHANDLER_H
#define HTTPCONNECTIONHANDLER_H

#include "Consumer.hpp"
#include "Socket.hpp"


/**
 * @brief A HttpConnectionHandler is a consumer of its own queue. For each data pushed to its queue 
 * the HttpConnectionHandlers consumes it. Each element consumed corresponds no a new request.
 */
class HttpConnectionHandler : public Consumer<Socket>{
    DISABLE_COPY(HttpConnectionHandler);

 protected:
        /// Delay of consumer to consume a package, negative for max random
 public:
        /// Constructor
        explicit HttpConnectionHandler();
        /// Consume the clients in its own execution thread
        int run() override;
        /// Override this method to process any data extracted from the queue
        void consume(const Socket& client) override;
        void sendStopCondition();
};

#endif  // HTTPCONNECTIONHANDLER_H
