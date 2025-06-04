#!/usr/bin/env bash

for i in {1..8}; do 
    echo "Running serial (depth $i)"
    build/benchmark_Oware "$i" s >> bench.log
done

for i in {1..8}; do 
    echo "Running parallel (depth $i)"
    build/benchmark_Oware "$i" p >> bench.log
done


