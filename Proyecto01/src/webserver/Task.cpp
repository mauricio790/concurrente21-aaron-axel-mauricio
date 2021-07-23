#include "Task.hpp"

Task::Task(){
    this->number = -1;
    this->index = -1;
    this->request = nullptr;
    this->response = nullptr;
    this->resultSums = "";
}

Task::Task(const Task& other){
    this->number = other.number;
    this->index = other.index;
    this->request = other.request;
    this->response = other.response;
    this->resultSums = other.resultSums;

}

Task::Task(HttpRequest* request, HttpResponse* response, int64_t number,
  size_t index){
    this->request = request;
    this->response = response;
    this->number = number;
    this->index = index;
    this->resultSums = "";
}

Task::~Task(){

}

bool Task::operator==(const Task& other) const {
  bool isEqual =  this->number == other.number
    && this->request == other.request 
    && this->response == other.response
    && this->resultSums == other.resultSums;
  return isEqual;
}