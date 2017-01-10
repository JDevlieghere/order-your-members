#include <chrono>
#include <type_traits>
#include <utility>

template <class F, class... Args>
std::chrono::duration<double> benchmark(F&& f, Args&&... args) {
  using clock = std::conditional<std::chrono::high_resolution_clock::is_steady, std::chrono::high_resolution_clock,
                                 std::chrono::steady_clock>::type;
  const auto t0 = clock::now();
  std::forward<F>(f)(std::forward<Args>(args)...);
  return std::chrono::duration<double>(clock::now() - t0);
}
