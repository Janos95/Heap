
#define WITH_STD_HEAP

#include "Heap.h"

#include <benchmark/benchmark.h>
#include <random>
#include <iostream>

static void BenchBaseline(benchmark::State& state) {
    std::default_random_engine engine;
    std::uniform_int_distribution<int> uniform;
    for (auto _ : state) {
        benchmark::DoNotOptimize(uniform(engine));
    }
}

template<class H>
static void BenchBoth(benchmark::State& state) {
    std::vector<int> elements(state.range());
    std::default_random_engine engine;
    std::uniform_int_distribution<int> uniform;
    H h(state.range()); /* avoid allocation */
    std::generate(elements.begin(), elements.end(), [&]{ return uniform(engine); });
    h.insert(elements.begin(), elements.end());
    for (auto _ : state) {
        benchmark::DoNotOptimize(h.extractMin());
        h.emplace(uniform(engine));
    }
}


BENCHMARK_TEMPLATE(BenchBoth, Heap<int, MinHeap, HeapAlgorithm::StdHeap>)->DenseRange(1, 1<<13, 128);
BENCHMARK_TEMPLATE(BenchBoth, Heap<int, MinHeap, HeapAlgorithm::TwoAry>)->DenseRange(1, 1<<13, 128);
BENCHMARK_TEMPLATE(BenchBoth, Heap<int, MinHeap, HeapAlgorithm::FourAry>)->DenseRange(1, 1<<13, 128);
BENCHMARK_TEMPLATE(BenchBoth, Heap<int, MinHeap, HeapAlgorithm::MinMax>)->DenseRange(1, 1<<13, 128);

BENCHMARK(BenchBaseline);

BENCHMARK_MAIN();
