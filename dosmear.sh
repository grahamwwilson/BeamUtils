#!/bin/sh

./Smear -s 13001
./Smear -s 13002 -i GP-Z-7X.ee -o GP-Z-7X.eedat -e 45.6 --sigma1 0.300e-2 --sigma2 0.300e-2
./Smear -s 13003 -i GP-W-8X.ee -o GP-W-8X.eedat -e 80.7 --sigma1 0.203e-2 --sigma2 0.203e-2

exit
