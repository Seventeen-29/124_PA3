#!/bin/bash
for i in $(seq 1 100)
do
    echo "Run $i:"
    python3 generate_data.py 
    echo "KK:"
    ./partition 1 0 input.txt 
    echo "Repeated Random:"
    ./partition 1 1 input.txt
    echo "Hill Climbing:"
    ./partition 1 2 input.txt
    echo "Simulated Annealing:"
    ./partition 1 3 input.txt
    echo "Prepartitioned Repeated Random:"
    ./partition 1 11 input.txt
    echo "Prepartitioned Hill Climbing:"
    ./partition 1 12 input.txt
    echo "Prepartitioned Simulated Annealing:"
    ./partition 1 13 input.txt
done