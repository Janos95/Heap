# Heap

This is a wrapper around the Binary Heap, Quad Heap and Min-Max Heap written by [Malte Skarupke](https://github.com/skarupke/heap)
and the Heap implementation provided by the stl. See also this [blog post](https://probablydance.com/2020/08/31/on-modern-hardware-the-min-max-heap-beats-a-binary-heap/).

For one extract min and one insert (of a random number) operation I* obtained the following timings:
![alt text](https://github.com/Janos95/Heap/blob/master/plot.png "Plot1")

For the make heap operations
![alt text](https://github.com/Janos95/Heap/blob/master/make_heap.png "Plot2")

If you want to run the benchmark yourself, comment out the correct benchmarks in the main.cpp file and run

```
git submodule update --recursive
mkdir build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Release
make -j
./bench --benchmark_format=csv | python ../plot.py  
```


*my system 
Running ./bench
Run on (28 X 4300 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x14)
  L1 Instruction 32 KiB (x14)
  L2 Unified 1024 KiB (x14)
  L3 Unified 19712 KiB (x1)
Load Average: 0.33, 0.49, 0.63
