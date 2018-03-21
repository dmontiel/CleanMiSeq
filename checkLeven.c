#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int levenshtein(const char *s, const char *t)
{
	int ls = strlen(s), lt = strlen(t);
	int d[ls + 1][lt + 1];
 
	for (int i = 0; i <= ls; i++)
		for (int j = 0; j <= lt; j++)
			d[i][j] = -1;
 
	int dist(int i, int j) {
		if (d[i][j] >= 0) return d[i][j];
 
		int x;
		if (i == ls)
			x = lt - j;
		else if (j == lt)
			x = ls - i;
		else if (s[i] == t[j])
			x = dist(i + 1, j + 1);
		else {
			x = dist(i + 1, j + 1);
 
			int y;
			if ((y = dist(i, j + 1)) < x) x = y;
			if ((y = dist(i + 1, j)) < x) x = y;
			x++;
		}
		return d[i][j] = x;
	}
	return dist(0, 0);
}

int main(int argc, char *argv[]){
/*if (argc!=4){
	printf("./checkLeven.o <fin> <# sequences>");
}*/

//FILE *fp = fopen("AR_00526_clean.fa", "r");
FILE *fp = fopen(argv[1], "r");
//FILE *fp = fopen(argv[1], "r");

//printf("this %d %s\n\n",argc,argv[1]);
int linecnt  = atoi(argv[2]);
int j=0;
int k=0;
int n=0;
int val0;//use wc -l to count lines and divide by 2
int val1;
int lenval;
int maxval;
int maxind;
int levdist = 100;
//int visited[314]={0};
int *visited;
visited=(int*)calloc(linecnt,sizeof(int));
//const char **seqval[314][250];
typedef char * string;
string **seqval;
seqval = malloc(linecnt * sizeof(string));
int jj;
for(jj = 0; jj < linecnt; jj++){
	seqval[jj] = malloc(250* sizeof(char));
}
string **headers;
headers = malloc(linecnt *sizeof(string));
for(jj = 0; jj< linecnt; jj++){
	headers[jj] = malloc(1000*sizeof(char));
}


//const char (*headers[linecnt])= malloc(sizeof(char[linecnt][250]));
//const char **seqval = (char *)malloc(211*[314][211];
//const char **headers[314][250];
const char htmp[100];
//int sizearr[314]={0};
int *sizearr;
sizearr = (int *)calloc(linecnt,sizeof(int));
int *headarr;
headarr = (int *)calloc(linecnt,sizeof(int));
int currsum =0;
int numseq = 0;
for (j=0;j<linecnt*2;j+=2){
	//fscanf(fp,">AR_%d_%d_%d\n",&val0,&val1,&lenval);
	fscanf(fp,"%s\n",headers[k]);
	sscanf(headers[k],">AR_%d_%d_%d\n",&val0,&headarr[k],&sizearr[k]);
	fscanf(fp,"%s\n",seqval[k]);
//	printf("%d %d %d %d\n",j,val0, val1,lenval);
	k+=1;
}
k=0;
for (k = 0; k<linecnt-1;k+=1){
	maxval = sizearr[k];
	maxind = k;
	currsum = sizearr[k];
	if (visited[k]==0){
		numseq++;
		for(n=(k+1);n<linecnt;n+=1){
			if (visited[n]==0){
				levdist = levenshtein(seqval[k],seqval[n]);
				if ((levdist <=6) && (headarr[k]!=headarr[n])){
					if (sizearr[n]>maxval){
						maxind = n; 
						maxval = sizearr[n];
					}
					currsum += sizearr[n];
			//		printf("%d %d %d %s %s \n",levdist,k,currsum,headers[k],headers[n]);
//					printf("worked.\n");
//					printf("%s\n",headers[n]);
//					printf("%s\n",seqval[n]);
					visited[n]=1;
				}
			}
		}
		
		printf(">AR_%05d_%05d_%05d\n",val0,numseq,currsum);
		printf("%s\n",seqval[maxind]);
		//printf("\n");
		//printf("%d %d\n",sizearr[k],currsum);
	}
	visited[k]=1;
//	printf("%d\n",k);
	//printf("%d\n",currsum);
}
free(headarr);
free(seqval);
free(sizearr);
free(headers);
free(visited);
fclose(fp);
//fclose(seqval);
//fclose(headers);
return 0;
}
