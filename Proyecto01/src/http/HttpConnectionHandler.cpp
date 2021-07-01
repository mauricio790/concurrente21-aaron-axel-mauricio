#include "HttpConnectionHandler.hpp"
#include "HttpServer.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "WebServer.hpp"
#include "Socket.hpp"
#include "assert.h"


HttpConnectionHandler::HttpConnectionHandler()  {
}

/**
 * @brief This method sends a stop condition to its own queue to stop consuming.
 */
void HttpConnectionHandler::sendStopCondition() {
  this->consumingQueue->push(this->stopCondition);
}

/**
 * @brief This method is called when the thread is start it. Once called, it consumes forever from its own queue
 */
int HttpConnectionHandler::run() {
  // Start the forever loop to consume all client connectios
  this->consumeForever();
  return EXIT_SUCCESS;
}

/**
 * @brief This method consumed data from its own queue while it still has requests from the same client
 * @param client Socket& client is the element consumed form its own queue
 */
void HttpConnectionHandler::consume(const Socket& client) {
  (void)client;
  // TODO(you) Move the following loop to a consumer thread class -- Done
  // While the same client asks for HTTP requests in the same connection
  while (true) {
    // Create an object that parses the HTTP request from the socket
    HttpRequest httpRequest(client);

    // If the request is not valid or an error happened
    if (!httpRequest.parse()) {
      // Non-valid requests are normal after a previous valid request. Do not
      // close the connection yet, because the valid request may take time to
      // be processed. Just stop waiting for more requests
      break;
    }

    // A complete HTTP client request was received. Create an object for the
    // server responds to that client's request
    HttpResponse httpResponse(client);

    // Give subclass a chance to respond the HTTP request
    const bool handled =
    WebServer::getInstance().handleHttpRequest(httpRequest, httpResponse);

    // If subclass did not handle the request or the client used HTTP/1.0
    if (!handled || httpRequest.getHttpVersion() == "HTTP/1.1") {
      // The socket will not be more used, close the connection
      client.close();
      break;
    }
  }
}
