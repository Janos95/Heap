
#define WITH_STD_HEAP

#include "Heap.h"

#include <benchmark/benchmark.h>
#include <random>


static void BenchBaseline(benchmark::State& state) {
    std::vector<int> elements(state.range() + 1);
    std::default_random_engine engine;
    std::uniform_int_distribution<int> uniform;
    for (auto _ : state) {
        benchmark::DoNotOptimize(uniform(engine));
    }
}

template<class H>
static void BenchBoth(benchmark::State& state) {
    std::vector<int> elements(state.range() + 1);
    std::default_random_engine engine;
    std::uniform_int_distribution<int> uniform;
    H h(state.range() + 1);
    std::generate(elements.begin(), elements.end(), [&]{ return uniform(engine); });
    h.insert(elements.begin(), elements.end());
    for (auto _ : state) {
        benchmark::DoNotOptimize(h.extractMin());
        benchmark::DoNotOptimize(h.emplace(uniform(engine)));
    }
}


BENCHMARK_TEMPLATE(BenchBoth, Heap<int, Less, HeapAlgorithm::StdHeap>)->DenseRange(0, 1<<13, 1 << 7);
BENCHMARK_TEMPLATE(BenchBoth, Heap<int, Less, HeapAlgorithm::TwoAry>)->DenseRange(0, 1<<13, 1 << 7);
BENCHMARK_TEMPLATE(BenchBoth, Heap<int, Less, HeapAlgorithm::FourAry>)->DenseRange(0, 1<<13, 1 << 7);
BENCHMARK_TEMPLATE(BenchBoth, Heap<int, Less, HeapAlgorithm::MinMax>)->DenseRange(0, 1<<13, 1 << 7);

BENCHMARK(BenchBaseline);

BENCHMARK_MAIN();
