#ifndef TASK_HPP
#define TASK_HPP

#include"HttpRequest.hpp"
#include"HttpResponse.hpp"
#include<vector>
class Task{
    public:
        Task();
        Task(HttpRequest* request, HttpResponse* response, int64_t number, size_t index,
          size_t numberToProcess, size_t *numbersProcessed, std::vector<std::string>* result);
        Task(const Task& other);
        ~Task();

    public:
        std::vector<std::string>* resultSums;

        HttpRequest* request;
        HttpResponse* response; 

        size_t index;
        int64_t number;
        size_t numbersToProcess;
        size_t *numbersProcessed;   

         /// Returns true if this socket represents the same connection than the other
        bool operator==(const Task& other) const; 
};

#endif