import pandas as pd
import numpy as np
import sys
from datetime import datetime
from itertools import combinations
fin =sys.argv[1]

df = pd.read_csv(fin,sep =' ',names = ['otu','well']).drop_duplicates().sort_values(by = 'well').reset_index(drop=True)
otupairs = {}
for ii in np.arange(0,2305):
	print(ii)
	otu_tmp = df['otu'].loc[df['well']==ii]
	comb = combinations(otu_tmp,2)
	for jj in comb:
		tmp = np.sort(jj)
		tmpkey = tuple((tmp[0],tmp[1]))
		try:
			otupairs[tmpkey]+=1
		except KeyError:
			otupairs[tmpkey]=1
df2 = pd.DataFrame({'pair':list(otupairs.keys()),'count':list(otupairs.values())}).sort_values(by = 'count' ,ascending =0)
df2['tag1'] = df2['pair'].apply(lambda x: x[0])
df2['tag2'] = df2['pair'].apply(lambda x: x[1])
df2[['tag1','tag2','count']].to_csv('pair_count_20180115.csv',header =False)


	
