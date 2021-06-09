
#include "HttpConnectionHandler.hpp"
#include "HttpServer.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "WebServer.hpp"
#include "Socket.hpp"
#include "assert.h"


HttpConnectionHandler::HttpConnectionHandler() {
}

int HttpConnectionHandler::run(){
  // Start the forever loop to consume all clien connectios
  this->consumeForever();
  return 1;
}



void HttpConnectionHandler::consume(const Socket& client){
  Socket client_copy(client);
  (void)client;
  // TODO(you) Move the following loop to a consumer thread class -- Listo
  // While the same client asks for HTTP requests in the same connection
  while (true) {
    // Create an object that parses the HTTP request from the socket
    HttpRequest httpRequest(client_copy);

    // If the request is not valid or an error happened
    if (!httpRequest.parse()) {
      // Non-valid requests are normal after a previous valid request. Do not
      // close the connection yet, because the valid request may take time to
      // be processed. Just stop waiting for more requests
      break;
    }

    // A complete HTTP client request was received. Create an object for the
    // server responds to that client's request
    HttpResponse httpResponse(client_copy);

    // Give subclass a chance to respond the HTTP request
    const bool handled =  WebServer::getInstance().handleHttpRequest(httpRequest, httpResponse);

    // If subclass did not handle the request or the client used HTTP/1.0
    if (!handled || httpRequest.getHttpVersion() == "HTTP/1.0") {
      // The socket will not be more used, close the connection
      client_copy.close();
      break;
    }

  }
}