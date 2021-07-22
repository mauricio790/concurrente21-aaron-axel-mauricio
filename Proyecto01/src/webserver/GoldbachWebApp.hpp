#ifndef GOLDBACHWEBAPP_H
#define GOLDBACHWEBAPP_H

#include <vector>
#include "WebServer.hpp"
/**
 * @brief A class that receives the HTTP requests made by the client, extract the numbers and
 * use the GoldbachCalculator to proccess the numbers and generate the HTTP response.S
 */
class GoldbachWebApp{
  DISABLE_COPY(GoldbachWebApp);

 public:
  // Constructor
  GoldbachWebApp();
  // Destructor
  ~GoldbachWebApp();
  /// Route, that provide an answer according to the URI value
  /// For example, home page is handled different than a number
  bool route(HttpRequest& httpRequest, HttpResponse& httpResponse);
  /// Sends the homepage as HTTP response
  bool serveHomepage(HttpRequest& httpRequest, HttpResponse& httpResponse);
  /// Sends a page for a non found resouce in this server
  bool serveNotFound(HttpRequest& httpRequest, HttpResponse& httpResponse);
  /// Calculate the goldbach sums of a number asked by the client, and
  /// sends the response in HTML format as HTTP response
  bool serveGoldbachSums(HttpRequest& httpRequest
    , HttpResponse& httpResponse, std::vector<int64_t>* user_numbers);
  // Set HTTP response metadata (headers)
  void setHeaders(HttpResponse& httpResponse, int error);
  //
  void setPageTitle(HttpResponse& httpResponse, std::string title);
};

#endif
