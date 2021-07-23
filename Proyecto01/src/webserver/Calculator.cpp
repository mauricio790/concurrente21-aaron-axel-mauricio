#include"Calculator.hpp"

Calculator::Calculator(){

}

void Calculator::consume(const Task& task){
    GoldbachCalculator calculadora;
    Task newTask(task);
    
    calculadora.leerDatos(task.number);
    newTask.resultSums = calculadora.sums_goldbach.str();
    this->produce(newTask);
}   

/**
 * @brief This method is called when the thread is start it. Once called, it consumes forever from its own queue
 */
int Calculator::run() {
  // Start the forever loop to consume all client connectios
  this->consumeForever();
  return EXIT_SUCCESS;
}

/**
 * @brief This method sends a stop condition to its own queue to stop consuming.
 */
void Calculator::sendStopCondition() {
  this->consumingQueue->push(this->stopCondition);
}