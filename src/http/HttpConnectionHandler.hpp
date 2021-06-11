#ifndef HTTPCONNECTIONHANDLER_H
#define HTTPCONNECTIONHANDLER_H

#include "Consumer.hpp"
#include "Socket.hpp"



class HttpConnectionHandler : public Consumer<Socket>{
    DISABLE_COPY(HttpConnectionHandler);

    protected:
        /// Delay of consumer to consume a package, negative for max random
        int consumerDelay = 5000;
    
    public:
        /// Constructor
        explicit HttpConnectionHandler(int consumerDelay);
        /// Consume the messages in its own execution thread
        int run() override;
        /// Override this method to process any data extracted from the queue
        void consume(const Socket& client) override;
        
};

#endif  //HTTPCONNECTIONHANDLER_H