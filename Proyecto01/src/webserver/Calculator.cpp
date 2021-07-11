#include"Calculator.hpp"

Calculator::Calculator(){

}

void Calculator::consume(const Task& task){
    GoldbachCalculator calculadora;
    Task newTask(task);

    calculadora.leerDatos(task.number);
    std::cout << "numero a procesar: " << calculadora.sums_goldbach.str() << std::endl;
    newTask.resultSums->at(task.index) = calculadora.sums_goldbach.str();
    
    this->mutex.lock();
    std::cout << " Task: " << *task.numbersProcessed<< std::endl;
    std::cout << " New Task: " << *newTask.numbersProcessed<< std::endl;
    size_t aux = *(newTask.numbersProcessed);
    *(newTask.numbersProcessed)++;
    std::cout << " Task: " << *task.numbersProcessed<< std::endl;
    std::cout << " New Task: " << *newTask.numbersProcessed<< std::endl;
    if(*task.numbersProcessed == task.numbersToProcess){
        std::cout << "Produce New Task" << std::endl;
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