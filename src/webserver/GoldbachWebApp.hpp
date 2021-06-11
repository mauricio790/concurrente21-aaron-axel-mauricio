
#ifndef GOLDBACHWEBAPP_H
#define GOLDBACHWEBAPP_H

#include "WebServer.hpp"

class GoldbachWebApp{
  DISABLE_COPY(GoldbachWebApp);

public:
  //Constructor
  GoldbachWebApp();
  //Destructor
  ~GoldbachWebApp();
  /// Route, that provide an answer according to the URI value
  /// For example, home page is handled different than a number
  bool route(HttpRequest& httpRequest, HttpResponse& httpResponse);
  /// Sends the homepage as HTTP response
  bool serveHomepage(HttpRequest& httpRequest, HttpResponse& httpResponse);
  /// Sends a page for a non found resouce in this server
  bool serveNotFound(HttpRequest& httpRequest, HttpResponse& httpResponse);
  /// Calculate the prime factorization of a number asked by the client, and
  /// sends the response in HTML format as HTTP response
  bool serveGoldbachSums(HttpRequest& httpRequest
    , HttpResponse& httpResponse, int64_t number);

};

#endif