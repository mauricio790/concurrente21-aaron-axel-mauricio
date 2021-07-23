#ifndef TASK_HPP
#define TASK_HPP

#include"HttpRequest.hpp"
#include"HttpResponse.hpp"
#include<vector>
class Task{
 public:
  Task();
  Task(HttpRequest* request, HttpResponse* response, int64_t number,
  size_t index);
  Task(const Task& other);
  ~Task();
 public:
  HttpRequest* request;
  HttpResponse* response;
  int64_t number;
  size_t index;
  std::string resultSums;
  /// Returns true if this socket represents 
  //the same connection than the other
  bool operator==(const Task& other) const; 
};

#endif
