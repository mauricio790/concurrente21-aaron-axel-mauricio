#include "GeneradorHtml.hpp"

GeneradorHtml::GeneradorHtml(){   
}
GeneradorHtml::~GeneradorHtml(){
}
std::stringstream GeneradorHtml::generarHtml(std::vector<GoldbachCalculator::Sumas> sumGoldbach, int cantidad,int64_t number){
  std::stringstream sums_goldbach ;
  sums_goldbach << number << ": ";
  sums_goldbach << cantidad << " sums <br>"; 
  if (number < 0) {
    for (int index =0; index < cantidad; index++) {
      if (sumGoldbach[index].num3 == 0){
        sums_goldbach << index +1 << ". " << sumGoldbach[index].num1 << " + " << sumGoldbach[index].num2 << "<br>";
      } else {
        sums_goldbach << index +1 << ". " << sumGoldbach[index].num1 << " + " << sumGoldbach[index].num2 << " + "<< sumGoldbach[index].num3 <<"<br>";
      }
    }
  }
  return sums_goldbach;
}
