#!/bin/bash

fin='fin.fq'

seqtk seq -aQ64 fin.fq > out.fa1
#seqtk trimfq -e 40 out.fa1 > out.fa
python clean_seq.py > clean.tmp2
