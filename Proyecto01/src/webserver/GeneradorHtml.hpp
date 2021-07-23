#ifndef GENERADORHTML_H
#define GENERADORHTML_H
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "GoldbachCalculator.hpp"
class GeneradorHtml{
 public:
  GeneradorHtml();
  ~GeneradorHtml();
  std::stringstream generarHtml(std::vector
  <GoldbachCalculator::Sumas>* sumGoldbach, int cantidad, int64_t number);
};

#endif  // GENERADORHTML_H
