#!/bin/bash
#run the pi calculation in serial, and mpi with 1, 2, 3, 4, 8, 12 and 16 nodes, user oversubscribe to allow more nodes than the physical cores

# Serial
echo "Serial"
cd /compartido/serial
gcc pi_serial.c -o pi_serial
for i in 100000000 1000000000 2000000000; do
    echo "Serial with $i iterations"
    for j in $(seq 1 4); do
        echo "$i, $j" >> /home/mpiuser/serial_node
        ./pi_serial $i >> /home/mpiuser/serial_node
done

# MPI
echo "MPI"
cd /compartido/mpi
mpicc pi_mpi.c -o pi_mpi

for i in 1 2 3 4 8 12 16; do
    for j in $(seq 1 4); do
        for k in 100000000 1000000000 2000000000; do
            echo "MPI with $i nodes and $k iterations"
            echo "$i, $k, $j" >> /home/mpiuser/mpi_node
            mpirun --oversubscribe -np $i --hostfile /compartido/hostfile ./pi_mpi $k >> /home/mpiuser/mpi_node
        done
done

echo "Done"

