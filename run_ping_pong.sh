#!/bin/bash

SIZE=20
CYCLES=5

while getopts ":s:c:" flag
do
	case "${flag}" in
		s) SIZE=$OPTARG;;
		c) CYCLES=$OPTARG;;
		?) echo "Invalid argument: ${OPTARG}.";exit1;;
	esac
done

export OMPI_MCA_btl=tcp,self
srun --partition largemem -N 2 -n 2 ./build/pingpong -s ${SIZE} -c ${CYCLES}
