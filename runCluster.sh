#!/bin/bash
#Auto orchestrate the MPI cluster and add the ip of the nodes to ./compartido/hostfile

# Get mpi_node count from argument
mpi_node=$1

# Orchestrate the cluster
docker compose up --scale mpi_node=$mpi_node -d # Start the cluster detached

# Get the ip of the nodes
docker inspect -f '{{range .NetworkSettings.Networks}}{{.IPAddress}}{{end}}' $(docker ps -q) > ./compartido/hostfile # Get the ip of the nodes and write it to hostfile


