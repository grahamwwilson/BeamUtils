#!/bin/sh
#
# This needs the CLI11.hpp include (it is provided) or you can install the CLI11 
# header file on your system. 
#

fn=${1:-Smear}

# Compile with high optimization. No need for any libraries with this for now.
g++ -O3 ${fn}.cpp -o ${fn}

exit
