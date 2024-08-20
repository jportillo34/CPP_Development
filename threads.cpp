#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>

using namespace std;

double funcOne(double n) { sleep(8); return n; }

int main() {
  std::vector<std::thread> threads;

  for (double i = 0; i < 2; i++) {
    threads.push_back(std::thread(funcOne, i));
    // funcOne(i);
  }
  for (auto &t : threads) {
    t.join();
  }
  return (0);
}