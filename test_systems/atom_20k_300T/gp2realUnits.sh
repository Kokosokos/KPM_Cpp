#!/bin/bash
##transform Gp data to [GPa] and frequency to [s^{-1} x 10^{-15}]
#pls use [x 1/10000] factor for the data from 'wiggle' test too

file=$1 #"Gp.dat" 
GA0=$2
awk -v G0=$GA0 '{print $1/1000,($2+G0)/10000}' $file
