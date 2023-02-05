#!/bin/sh

FN=${1:-4X5X}

if [ -e localee.out ]
then 
   rm localee.out
fi

# Make symbolic link

ln -s /home/graham/gpDigest/lumi-Run${FN}.ee.out localee.out

cut -d " " -f1-2 localee.out >GP-${FN}.ee

exit
