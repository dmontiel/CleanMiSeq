#!/bin/bash

#fin='AR_AD_ARRY_LIB01_00001_F.fq'

#seqtk seq -aQ64 -q20 $fin > $fin.tmp
#python clean_seq.py $fin.tmp > clean.tmp
#python sort_seq.py clean.tmp 7 > tmp.sort
for i in `ls ./data/nr*.nr`;
do
outname=${i:7:8}
echo $outname
python step1_clean_seq.py $i > clean.tmp
python step2_sort_seq.py clean.tmp 7 > ./clean_wells/$outname.clean
done
rm clean.tmp
