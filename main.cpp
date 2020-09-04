
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
static void BenchExtractEmplace(benchmark::State& state) {
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

template<class H>
static void BenchExtract(benchmark::State& state) {
    std::vector<int> elements(state.range());
    std::default_random_engine engine;
    std::uniform_int_distribution<int> uniform;
    std::generate(elements.begin(), elements.end(), [&]{ return uniform(engine); });
    H h(elements.size()); /* avoid allocation */
    for (auto _ : state) {
        state.PauseTiming();
        h.insert(elements.begin(), elements.end());
        state.ResumeTiming();
        for(int i = 0; i < state.range(); ++i)
            benchmark::DoNotOptimize(h.extractMin());
    }
}

template<class H>
static void BenchEmplace(benchmark::State& state) {
    std::vector<int> elements(state.range());
    std::default_random_engine engine;
    std::uniform_int_distribution<int> uniform;
    H h(state.range()); /* avoid allocation */
    std::generate(elements.begin(), elements.end(), [&]{ return uniform(engine); });
    for (auto _ : state) {
        h.clear();
        for(auto x : elements)
            h.emplace(x);
    }
}


template<class H>
static void BenchMakeHeap(benchmark::State& state) {
    std::vector<int> elements(state.range());
    std::default_random_engine engine;
    std::uniform_int_distribution<int> uniform;
    H h(state.range()); /* avoid allocation */
    std::generate(elements.begin(), elements.end(), [&] { return uniform(engine); });
    for(auto _ : state) {
        h.clear();
        h.insert(elements.begin(), elements.end());
    }
}

BENCHMARK_TEMPLATE(BenchExtractEmplace, Heap<int, MinHeap, HeapAlgorithm::StdHeap>)->DenseRange(1, 1<<13, 128);
BENCHMARK_TEMPLATE(BenchExtractEmplace, Heap<int, MinHeap, HeapAlgorithm::TwoAry>)->DenseRange(1, 1<<13, 128);
BENCHMARK_TEMPLATE(BenchExtractEmplace, Heap<int, MinHeap, HeapAlgorithm::FourAry>)->DenseRange(1, 1<<13, 128);
BENCHMARK_TEMPLATE(BenchExtractEmplace, Heap<int, MinHeap, HeapAlgorithm::MinMax>)->DenseRange(1, 1<<13, 128);

//BENCHMARK_TEMPLATE(BenchExtract, Heap<int, MinHeap, HeapAlgorithm::StdHeap>)->DenseRange(1, 1<<13, 128);
//BENCHMARK_TEMPLATE(BenchExtract, Heap<int, MinHeap, HeapAlgorithm::TwoAry>)->DenseRange(1, 1<<13, 128);
//BENCHMARK_TEMPLATE(BenchExtract, Heap<int, MinHeap, HeapAlgorithm::FourAry>)->DenseRange(1, 1<<13, 128);
//BENCHMARK_TEMPLATE(BenchExtract, Heap<int, MinHeap, HeapAlgorithm::MinMax>)->DenseRange(1, 1<<13, 128);

//BENCHMARK_TEMPLATE(BenchEmplace, Heap<int, MinHeap, HeapAlgorithm::StdHeap>)->DenseRange(1, 1<<13, 128);
//BENCHMARK_TEMPLATE(BenchEmplace, Heap<int, MinHeap, HeapAlgorithm::TwoAry>)->DenseRange(1, 1<<13, 128);
//BENCHMARK_TEMPLATE(BenchEmplace, Heap<int, MinHeap, HeapAlgorithm::FourAry>)->DenseRange(1, 1<<13, 128);
//BENCHMARK_TEMPLATE(BenchEmplace, Heap<int, MinHeap, HeapAlgorithm::MinMax>)->DenseRange(1, 1<<13, 128);

//BENCHMARK_TEMPLATE(BenchMakeHeap, Heap<int, MinHeap, HeapAlgorithm::StdHeap>)->DenseRange(1, 1<<13, 128);
//BENCHMARK_TEMPLATE(BenchMakeHeap, Heap<int, MinHeap, HeapAlgorithm::TwoAry>)->DenseRange(1, 1<<13, 128);
//BENCHMARK_TEMPLATE(BenchMakeHeap, Heap<int, MinHeap, HeapAlgorithm::FourAry>)->DenseRange(1, 1<<13, 128);
//BENCHMARK_TEMPLATE(BenchMakeHeap, Heap<int, MinHeap, HeapAlgorithm::MinMax>)->DenseRange(1, 1<<13, 128);

BENCHMARK(BenchBaseline);

BENCHMARK_MAIN();
