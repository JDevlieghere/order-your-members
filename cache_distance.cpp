#include "benchmark.h"

#include <iostream>

constexpr auto LENGTH = 10000000;
constexpr auto ITERATIONS = 100;

struct FarApart {
  char a;
  char c[128];
  char b;
};

struct CloseTogether {
  char c[128];
  char a;
  char b;
};

template <typename T>
void benchmarkCache(T* t, int s) {
  int j = 0;
  for (int i = 0; i != s; ++i) {
    if (t[i].a == t[i].b) j++;
  }
}

std::pair<double, double> runBenchmark() {
  CloseTogether* ct = new CloseTogether[LENGTH];
  FarApart* fa = new FarApart[LENGTH];
  const double d1 = benchmark(benchmarkCache<CloseTogether>, ct, LENGTH).count();
  const double d2 = benchmark(benchmarkCache<FarApart>, fa, LENGTH).count();
  delete[] ct;
  delete[] fa;
  return {d1, d2};
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
