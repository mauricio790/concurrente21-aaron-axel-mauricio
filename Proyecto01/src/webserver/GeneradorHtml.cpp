#include "GeneradorHtml.hpp"

GeneradorHtml::GeneradorHtml(){   
}
GeneradorHtml::~GeneradorHtml(){
}
std::stringstream GeneradorHtml::generarHtml(std::vector<GoldbachCalculator::Sumas>* sumGoldbach, int cantidad,int64_t number){
  std::stringstream sums_goldbach ;
  bool print_sums_flag = false;
  if (number < 0){
    print_sums_flag = true;
    number *= -1;
  }

  sums_goldbach << "<font size=5>" << number << ": </font>";
  if(number <= 5) {
     sums_goldbach << "<font size=5 color=red> NA </font>" ;
  } else {
    sums_goldbach << "<font size=5>" << cantidad << " sums <br> </font>"; 
    if (print_sums_flag) {
      for (int index =0; index < cantidad; index++) {
        if ((*sumGoldbach)[index].num3 == 0){
          sums_goldbach << index +1 << ". " << (*sumGoldbach)[index].num1 << " + " << (*sumGoldbach)[index].num2 << "<br>";
        } else {
          sums_goldbach << index +1 << ". " << (*sumGoldbach)[index].num1 << " + " << (*sumGoldbach)[index].num2 << " + "<< (*sumGoldbach)[index].num3 <<"<br>";
        }
      }
    }
  }
  return sums_goldbach;
}
