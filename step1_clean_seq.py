import numpy as np
import pandas as pd
from Bio import SeqIO
import sys
fin = sys.argv[1]
with open(fin,"rU") as handle:
	well = fin.split('_')[1].split('.')[0]
	count = 0
	for record in SeqIO.parse(handle,'fasta'):
		if len(str(record.seq))>240:
			sz = str(record.id).split('size=')[1]
			print "_".join(['>',well.zfill(4),str(count).zfill(4),sz]) +'\t' + str(record.seq)[0:200].upper()+'\t'+sz
			count+=1
