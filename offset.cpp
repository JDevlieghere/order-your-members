#include "benchmark.h"

#include <iostream>

constexpr auto LENGTH = 10000000;
constexpr auto ITERATIONS = 10000000;

struct LargeOffset {
  char a[128];
  char c;
};

struct SmallOffset {
  char c;
  char a[128];
};

template <typename T>
void benchmarkOffset(T* t, int s) {
  for (int i = 0; i != s; ++i) {
    t[i].c = 's';
  }
}

std::pair<double, double> runBenchmark() {
  SmallOffset* soa = new SmallOffset[LENGTH];
  LargeOffset* loa = new LargeOffset[LENGTH];
  const double d1 = benchmark(benchmarkOffset<SmallOffset>, soa, LENGTH).count();
  const double d2 = benchmark(benchmarkOffset<LargeOffset>, loa, LENGTH).count();
  delete[] soa;
  delete[] loa;
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
  std::cout << "Small offset: " << s1 << std::endl;
  std::cout << "Large offset: " << s2 << std::endl;
}
