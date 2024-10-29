#!/bin/bash
#run the pi calculation in serial, and mpi with 1, 2, 3, 4, 8, 12 and 16 nodes, user oversubscribe to allow more nodes than the physical cores

#create files
touch /compartido/mpiResult
touch /compartido/serialResult
#remove previous results
echo "" > /compartido/mpiResult
echo "" > /compartido/serialResult

# Serial
echo "Serial"
cd /compartido/serial
gcc pi_serial.c -o pi_serial
for i in 100000000 1000000000 2000000000; do
    echo "Serial with $i iterations"
    for j in $(seq 1 4); do
        echo "$i, $j" >> /compartido/serialResult
        ./pi_serial $i >> /compartido/serialResult
    done
done

#wait for user input
read -p "Press enter to continue"

# MPI
echo "MPI"
cd /compartido/mpi
mpicc pi_mpi.c -o pi_mpi

for i in 1 2 3 4 8 12 16; do
    for j in $(seq 1 4); do
        for k in 100000000 1000000000 2000000000; do
            echo "MPI with $i nodes and $k iterations"
            echo "$i, $k, $j" >> /compartido/mpiResult
            mpirun --oversubscribe -np $i --hostfile /compartido/hostfile ./pi_mpi $k >> /compartido/mpiResult
        done
    done
done

echo "Done"