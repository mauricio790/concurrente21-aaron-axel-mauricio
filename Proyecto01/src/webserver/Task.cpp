#include "Task.hpp"

Task::Task(){
    this->index = -1;
    this->number = -1;
    this->numbersProcessed = nullptr;
    this->numbersToProcess = 0;
    this->request = nullptr;
    this->response = nullptr;
    this->resultSums = nullptr;
}

Task::Task(const Task& other){
    this->index = other.index;
    this->number = other.number;
    this->numbersProcessed = other.numbersProcessed;
    this->numbersToProcess = other.numbersToProcess;
    this->request = other.request;
    this->response = other.response;
    this->resultSums = other.resultSums;

}

Task::Task(HttpRequest* request, HttpResponse* response, int64_t number,
  size_t index, size_t numbersToProcess, size_t *numbersProcessed, std::vector<std::string>* result){
    this->request = request;
    this->response = response;
    this->number = number;
    this->index = index;
    this->numbersToProcess = numbersToProcess;
    this->numbersProcessed = numbersProcessed;
    this->resultSums = result;
}

Task::~Task(){

}

bool Task::operator==(const Task& other) const {
    bool isEqual = this->index == other.index 
                    && this->number == other.number 
                    && this->numbersProcessed == other.numbersProcessed 
                    && this->numbersToProcess == other.numbersToProcess
                    && this->request == other.request 
                    && this->response == other.response
                    && this->resultSums == other.resultSums;

  return isEqual;
}