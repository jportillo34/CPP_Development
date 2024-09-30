#include <iostream>
#include <thread>
#include <unistd.h>
#include <mutex>
//#include <vector>

std::mutex mtx;

double n_global = 1;    // <---- Usamos una variable global para ver el efecto de: hilos usando una memoria comun.

//void sharedResource(double n) { sleep(8); n_global += n; }

void sharedResource(double x) { mtx.lock(); sleep(8); n_global += x; mtx.unlock(); }

int main() {
/*
  sharedResource(3);
  sharedResource(2);
*/
  std::thread t1(sharedResource, 3);    // Pudiera pasar la direccion de la funcion "&delayFunction"!!
  std::thread t2(sharedResource, 2);

  t1.join();
  t2.join();


  std::cout << "\n\nn_global = " << n_global << "\n";


/*
  std::vector<std::thread> threads;

  for (double i = 0; i < 2; i++) {
    threads.push_back(std::thread(sharedResource, i));
    //sharedResource(i);
  }

  for (auto &t : threads) {
    t.join();
  }
*/

  return (0);
}
