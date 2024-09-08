#!/bin/bash

export OMPI_MCA_btl=tcp,self
srun --partition largemem -N 2 -n 2 ./build/ping_exchange
