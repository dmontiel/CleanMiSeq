import numpy as np
import pandas as pd
import editdistance
import sys
#command line inputs of file name and threshold
fin = sys.argv[1]
thresh = int(sys.argv[2])

#read in data from tab delimited file headers in one column, sequence in next
df = pd.read_csv(fin,sep = '\t',names = ['headers','seq','size'])
df = df.sort_values(by = 'size',ascending = 0)
#extract columns into numpy arrays
seqlist = np.array(df['seq'].values)
hlist = np.array(df['headers'].values)
szlist = np.array(df['size'].values)

visited = np.zeros(len(seqlist))#array for checking if sequence has already been added to cluster


#loop through all pairs of sequences to check if edit distance is less than threshold
for ii in np.arange(0,len(seqlist)-1):
	if visited[ii]==0:# if already visited then skips over
		visited[ii]=1
		tmpcnt = 1#how many sequences are being aggregated together
		tmpsz = szlist[ii]#keep track of total size of cluster
		for jj in np.arange(ii,len(seqlist)):
			if visited[jj]==0:
				lev_dist = editdistance.eval(seqlist[ii],seqlist[jj])
				if lev_dist <=thresh: 
					visited[jj]=1
					tmpcnt+=1
					tmpsz +=szlist[jj]
		if tmpcnt >1:
			print hlist[ii]+';'+str(tmpcnt)+';size='+str(tmpsz)#+'\t'+seqlist[ii]
			print seqlist[ii]
