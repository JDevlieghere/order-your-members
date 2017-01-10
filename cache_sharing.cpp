#include "benchmark.h"

#include <iostream>
#include <thread>

constexpr auto LENGTH = 10000000;
constexpr auto ITERATIONS = 100;

struct CloseTogether {
  char c[128];
  int a;
  int b;
};

struct FarApart {
  int a;
  char c[128];
  int b;
};

template <typename T>
void readA(T* t) {
  int s = 0;
  for (int i = 0; i != LENGTH; ++i) s += t->a;
}

template <typename T>
void writeB(T* t) {
  for (int i = 0; i != LENGTH; ++i) t->b++;
}

template <typename T>
void benchmarkSharing() {
  T t;
  t.a = 1;
  t.b = 1;
  std::thread t1(readA<T>, &t);
  std::thread t2(writeB<T>, &t);
  t1.join();
  t2.join();
}

std::pair<double, double> runBenchmark() {
  double t1 = benchmark(benchmarkSharing<CloseTogether>).count();
  double t2 = benchmark(benchmarkSharing<FarApart>).count();
  return {t1, t2};
}

int main() {
  double s1 = 0;
  double s2 = 0;
  for (int i = 0; i != ITERATIONS; ++i) {
    auto p = runBenchmark();
    s1 += p.first;
    s2 += p.second;
  }
  s1 = s1 / ITERATIONS;
  s2 = s2 / ITERATIONS;
  std::cout << "Close togeher: " << s1 << std::endl;
  std::cout << "Far apart: " << s2 << std::endl;
}
