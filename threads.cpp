#include <iostream>
#include <thread>
#include <unistd.h>
//#include <vector>

double n_global = 1;

void delayFunction(double n) { sleep(8); n_global += n; }

int main() {
/*
  delayFunction(2);
  delayFunction(2);
*/
// OJO INVESTIGAR ESTO!! ASI APARECE EN EL LAB DE LA CHICAGO UNIV Y CREO RECORDAR QUE ASI ERA EN LA ENTREVISTA!!!
  std::thread t1(&delayFunction, 2);
  std::thread t2(&delayFunction, 2);
  t1.join();
  t2.join();


  std::cout << "\n\nn_global = " << n_global << "\n";


/*
  std::vector<std::thread> threads;

  for (double i = 0; i < 2; i++) {
    threads.push_back(std::thread(delayFunction, i));
    //delayFunction(i);
  }

  for (auto &t : threads) {
    t.join();
  }
*/

  return (0);
}
