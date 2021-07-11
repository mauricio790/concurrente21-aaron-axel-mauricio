#include"Calculator.hpp"

Calculator::Calculator(){

}

void Calculator::consume(const Task& task){
    GoldbachCalculator calculadora;

    calculadora.leerDatos(task.number);
    task.resultSums->at(task.index) = calculadora.sums_goldbach.str();
    Task newTask(task);
    this->mutex.lock();
    newTask.numbersProcessed++;
    if(*task.numbersProcessed == task.numbersToProcess){
        this->produce(newTask);
    }
    this->mutex.unlock();
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