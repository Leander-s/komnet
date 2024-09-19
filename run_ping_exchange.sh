#!/bin/bash

SIZE=20
CYCLES=5
PART=largemem

while getopts ":s:c:p:" flag
do
	case "${flag}" in
		s) SIZE=$OPTARG;;
		c) CYCLES=$OPTARG;;
        p) PART=$OPTARG;;
		?) echo "Invalid argument: ${OPTARG}.";exit1;;
	esac
done

echo "Running on ${PART}"

export OMPI_MCA_btl=tcp,self
srun --partition $PART -N 2 -n 2 ./build/ping_exchange -s $SIZE -c $CYCLES
