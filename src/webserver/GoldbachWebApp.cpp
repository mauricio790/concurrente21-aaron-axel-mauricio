
#include <regex>
#include <stdexcept> 
#include <string>
#include <vector>
//borrar luego
#include <iostream>

#include "GoldbachWebApp.hpp"

GoldbachWebApp::GoldbachWebApp(){
}
  
GoldbachWebApp::~GoldbachWebApp(){
}

bool GoldbachWebApp::route(HttpRequest& httpRequest, HttpResponse& httpResponse) {
  // If the home page was asked
  if (httpRequest.getMethod() == "GET" && httpRequest.getURI() == "/") {
    return this->serveHomepage(httpRequest, httpResponse);
  }

  // TODO(you): URI can be a multi-value list, e.g: 100,2784,-53,200771728 //Listo
  // TODO(you): change for sendGoldbachSums() if you prefer it
  std::smatch matches;

  // TODO(you): Numbers given by user may be larger than int64_t, reject them

  // If a number was asked in the form "/goldbach/1223"
  // or "/goldbach?number=1223"
  // or "/goldbach?text=1223"
  std::regex inQuery("^/goldbach(/|\\?number=|\\?text=)(((-?\\d+)(,|%2C)?)+)$");
  if (std::regex_search(httpRequest.getURI(), matches, inQuery)) {
    assert(matches.length() >= 3);
    std::vector<int64_t> user_numbers;

    inQuery = ("(?!2C)(-?\\d+)");
    std::smatch num_matches;
    std::cout << "URL:"<<matches[2] << std::endl;
    std::string numbers_in_URL = matches[2];
    
    while(std::regex_search(numbers_in_URL, num_matches, inQuery)){
      try {
        int64_t number = std::stoll(num_matches[1]);
        user_numbers.push_back(number); 
      } catch (const std::out_of_range& out_of_range){
        return this->serveNotFound(httpRequest, httpResponse);
      }
      numbers_in_URL = num_matches.suffix().str();
    }
    return this->serveGoldbachSums(httpRequest, httpResponse, &user_numbers);
  }

  // Unrecognized request
  return this->serveNotFound(httpRequest, httpResponse);
}

// TODO(you): Fix code redundancy in the following methods

bool GoldbachWebApp::serveHomepage(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;

  // TODO(you) Move form to your view class, e.g GoldbachWebApp

  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  // Build the body of the response
  std::string title = "Goldbach sums";
  httpResponse.body() << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << title << "</title>\n"
    << "  <style>body {font-family: monospace}</style>\n"
    << "  <h1>" << title << "</h1>\n"
    << "  <form method=\"get\" action=\"/goldbach\">\n"
    << "    <label for=\"number\">Number</label>\n"
    << "    <input type=\"text\" name=\"text\" required/>\n"
    << "    <button type=\"submit\">Calculate</button>\n"
    << "  </form>\n"
    << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.send();
}

bool GoldbachWebApp::serveNotFound(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setStatusCode(404);
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  // Build the body of the response
  std::string title = "Not found";
  httpResponse.body() << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << title << "</title>\n"
    << "  <style>body {font-family: monospace} h1 {color: red}</style>\n"
    << "  <h1>" << title << "</h1>\n"
    << "  <p>The requested resouce was not found in this server.</p>\n"
    << "  <hr><p><a href=\"/\">Homepage</a></p>\n"
    << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.send();
}

//#include <unistd.h>

// TODO(you) Move domain-logic from WebServer controller to a view class
// e.g GoldbachWebApp, and a model class e.g GoldbachCalculator //listo

bool GoldbachWebApp::serveGoldbachSums(HttpRequest& httpRequest
    , HttpResponse& httpResponse, std::vector<int64_t>* user_numbers) {
  (void)httpRequest;
  //Borrar ---------------------
  std::cout << "user numbers:" << std::endl;
  for(std::vector<int64_t>::iterator it = user_numbers->begin();
    it != user_numbers->end(); ++it){
      std::cout << ' ' << *it;  
  }
  //-----------------
  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  //usleep(8000000);
  // Build the body of the response
  std::string title = "Goldbach sums for "; // + std::to_string(number);
  httpResponse.body() << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << title << "</title>\n"
    << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
    << "  <h1>" << title << "</h1>\n"
    << "  <h2>25</h2>\n"
    << "  <p>25: 5 sums</p>\n"
    << "  <h2 class=\"err\">-3</h2>\n"
    << "  <p>-3: NA</p>\n"
    << "  <h2>-13</h2>\n"
    << "  <p>-13: 2 sums</p>\n"
    << "  <ol>\n"
    << "    <li>3 + 3 + 7</li>\n"
    << "    <li>3 + 5 + 5</li>\n"
    << "  </ol>\n"
    << "  <hr><p><a href=\"/\">Back</a></p>\n"
    << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.send();
}
