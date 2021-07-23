#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include"HttpResponse.hpp"
#include"HttpRequest.hpp"
#include"Assembler.hpp"
#include"GoldbachCalculator.hpp"
#include"Task.hpp"

class Calculator : public Assembler<Task, Task>{
 public:
  explicit Calculator();
  int run() override;
  /// Override this method to process any data extracted from the queue
  void consume(const Task& task) override;
  void sendStopCondition();
};
#endif
