#include <regex>
#include <stdexcept>
#include <string>
#include <vector>
#include "GoldbachWebApp.hpp"
#include "GoldbachCalculator.hpp"
#include "Task.hpp"

GoldbachWebApp::GoldbachWebApp() {
}
GoldbachWebApp::~GoldbachWebApp() {
}
/**
 * @brief Provide an answer according to the client Request
 * @details If the client enter one or more comma separated values (directly in the URL or using the text box
 * in the home page), the subroutine extract all values using regular expressions, check if the value is larger
 * than a int64_t, if isn't add the values to a vector of int64_t and call serveGoldbachSums()
 * If the user puts a value larger than int64_t the request is rejected
 * @param httpRequest Http request (client request)
 * @param httpResponse Http response
 * @return a boolean to check if httpResponse could send the response.
 * */
bool GoldbachWebApp::route(HttpRequest& httpRequest,
HttpResponse& httpResponse) {
  // If the home page was asked
  if (httpRequest.getMethod() == "GET" && httpRequest.getURI() == "/") {
    return this->serveHomepage(httpRequest, httpResponse);
  }
  std::smatch matches;
  // If a number was asked in the form "/goldbach/1223"
  // or "/goldbach?number=1223" or "/goldbach?text=1223"
  std::regex inQuery("^/goldbach(/|\\?number=|\\?text=)(((-?\\d+)(,|%2C)?)+)$");
  if (std::regex_search(httpRequest.getURI(), matches, inQuery)) {
    assert(matches.length() >= 3);
    std::vector<int64_t> user_numbers;

    inQuery = ("(?!2C)(-?\\d+)");
    std::smatch num_matches;
    std::string numbers_in_URL = matches[2];
    // extract all numbers in the URL using regular expressions
    while (std::regex_search(numbers_in_URL, num_matches, inQuery)) {
      try {
        int64_t number = std::stoll(num_matches[1]);
        user_numbers.push_back(number);
      } catch (const std::out_of_range& out_of_range) {
        return this->serveNotFound(httpRequest, httpResponse);
      }
      numbers_in_URL = num_matches.suffix().str();

    }
    return this->serveGoldbachSums(httpRequest, httpResponse, &user_numbers);
  }
  // Unrecognized request
  return this->serveNotFound(httpRequest, httpResponse);
}

/**
 * @brief Sends the homepage as HTTP response
 * @param httpRequest Http request (client request)
 * @param httpResponse Http response
 * @return a boolean to check if httpResponse could send the response.
 * */
bool GoldbachWebApp::serveHomepage(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;

  setHeaders(httpResponse, 0);
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
/**
 * @brief Sends a page for a non found resouce in this server
 * @details The error code send is 404, sends the response in HTML format as HTTP response
 * @param httpRequest Http request (client request)
 * @param httpResponse Http response
 * @return a boolean to check if httpResponse could send the response.
 * */
bool GoldbachWebApp::serveNotFound(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;

  setHeaders(httpResponse, 404);

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

/**
 * @brief Calculate the goldbach sums of a number asked by the client
 * @details Sends the response in HTML format as HTTP response
 * @param httpRequest Http request (client request)
 * @param httpResponse Http response
 * @param user_numbers Vector of type int64_t, contains the client values
 * @return a boolean to check if httpResponse could send the response.
 * */
bool GoldbachWebApp::serveGoldbachSums(HttpRequest& httpRequest
    , HttpResponse& httpResponse, std::vector<int64_t>* user_numbers) {
  (void)httpRequest;
  size_t user_number_counter = (*user_numbers).size();
  size_t numbers_Processed = 1;
  std::vector<std::string> result;
  result.resize(user_number_counter);

  for(size_t index = 0; index < user_number_counter; index++){
    
    Task task(&httpRequest, &httpResponse ,(*user_numbers)[index],
      index,(size_t)user_number_counter, &numbers_Processed, &result);

    WebServer::getInstance().tasks_queue.push(task);
  
  }

  size_t cont_respuestas = 0;
  while(cont_respuestas < user_number_counter){
    std::cout << "que esta psandooo" <<std::endl;
    Task task_result = WebServer::getInstance().producedTasks_queue.pop();
    if (*(task_result.request) == httpRequest ) {
      setHeaders(httpResponse, 0);
    // Build the body of the response
    std::string title = "Goldbach sums for ";  // + std::to_string(number);
    httpResponse.body() << "<!DOCTYPE html>\n"
      << "<html lang=\"en\">\n"
      << "  <meta charset=\"ascii\"/>\n"
      << "  <title>" << title << "</title>\n"
      << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
      << "  <h1>" << title << "</h1>\n" << "<p>" << (*task_result.resultSums).at(task_result.index) << "</p>\n";
      cont_respuestas++;
    } else {
      WebServer::getInstance().tasks_queue.push(task_result);
    }
  }
  //delete numbers_Processed;
  /*
  setHeaders(httpResponse, 0);
  // Build the body of the response
  std::string title = "Goldbach sums for ";  // + std::to_string(number);
  httpResponse.body() << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << title << "</title>\n"
    << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
    << "  <h1>" << title << "</h1>\n"
    << "<p>" << sums << "</p>\n";
  //-----------------
  // Send the response to the client (user agent)*/
  return httpResponse.send();
}
/**
 * @brief Set HTTP response metadata (headers)
 * @details Set the headers of HTTP response
 * @param httpResponse Http response
 * @param error codigo de error
 * */
void GoldbachWebApp::setHeaders(HttpResponse& httpResponse, int error) {
  if (error == 404)
    httpResponse.setStatusCode(404);

  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");
}
