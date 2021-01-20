dtilt=$1
paste aforceX1.dump aforceX2.dump | tail -n +10 | awk -v dtilt=$dtilt '{print ($4-$1)/dtilt;print ($5-$2)/dtilt;print ($6-$3)/dtilt}' > dF.csv
