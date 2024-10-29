#!/bin/bash
#run the matrix multiplication in serial, and mpi with 1, 2, 3, 4, 8, 12 and 16 nodes, user oversubscribe to allow more nodes than the physical cores

#create files
touch /compartido/mpiResultMatrix
touch /compartido/serialResultMatrix
#remove previous results
echo "" > /compartido/mpiResultMatrix
echo "" > /compartido/serialResultMatrix

# # Serial
# echo "Serial"
# cd /compartido/serial
# gcc serial-mm.c -o serial-mm
# for i in 900 1000 4000 6000; do
#     echo "Serial with $i matrix"
#     for j in $(seq 1 4); do
#         echo "$i, $j" >> /compartido/serialResultMatrix
#         ./serial-mm $i >> /compartido/serialResultMatrix
#     done
# done

# #wait for user input
# read -p "Press enter to continue"

# MPI
echo "MPI"
cd /compartido/mpi
mpicc mpi-mm.c -o mpi-mm

for i in 2 3 4 8 12 16; do
    for j in $(seq 1 1); do
        for k in 900 1000 4000 6000; do
            echo "MPI with $i nodes and $k matrix"
            echo "$i, $k, $j" >> /compartido/mpiResultMatrix
            mpirun --oversubscribe -np $i --hostfile /compartido/hostfile ./mpi-mm $k >> /compartido/mpiResultMatrix
        done
    done
done

echo "Done"