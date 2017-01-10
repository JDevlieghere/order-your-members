# Benchmarks

Benchmarks for blog post titled "Order Your Members":
https://jonasdevlieghere.com/order-your-members

## Building

```
$ mkdir build && cd build
$ cmake ..
$ cmake --build .
```

## Running

There is one binary for each benchmark. Running them will run 100 iterations of
the respective benchmark.

 - `offset`
 - `cache_sharing`
 - `cache_distance`