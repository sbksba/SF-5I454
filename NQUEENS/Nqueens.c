#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("USAGE: ./%s <Grid Size>\n",argv[0]);
		return 1;
	}

	int N = atoi(argv[1]);
	int nbVar = N * N;
	int i,j,k,tmp,nbClause=0;
	FILE *fp;
  
	char *command = argv[1];
	char *extension = ".cnf";
	strcat(command, "queens");
	strcat(command, extension);

	fp = fopen(command, "w+");
	fprintf(fp,"p cnf %d NB \n", nbVar);
  
	/* ROW */
	for(k=1; k<=nbVar; k=k+N) {
		for(tmp=k; tmp<(N+k); tmp++) {
			fprintf(fp," %d",tmp);
		}
		fprintf(fp," 0\n");
		nbClause++;
		for(i=k; i<(N+k); i++) {
			for(j=i; j<(N+k); j++) {
				if (i != j) {
					fprintf(fp,"-%d -%d 0\n", i, j);
					nbClause++;
				}
			}
		}
	}
	
	/* COLUMN */
	for(k=1; k<=N; k++) {
		for(tmp=k; tmp<=nbVar; tmp=tmp+N) {
			fprintf(fp,"%d ", tmp);
		}
		fprintf(fp,"0\n");
		nbClause++;
		for (i=k; i<=nbVar; i=i+N) {
			for (j=i; j<=nbVar; j=j+N) {
				if (i != j) {
					fprintf(fp,"-%d -%d 0\n", i, j);
					nbClause++;
				}
			}
		}
	}

	/* DIAGONAL */
	/* Example : N = 4
	 * 
	 *  1  2  3  4
	 *  5  6  7  8
	 *  9  10 11 12
	 *  13 14 15 16
	 *
	 * First Loop    Second Loop
	 * 1 6 11 16     5 10 15
	 * 2 7 12        9 14
	 * 3 8
	 *
	 * Third Loop    Fourth Loop
	 * 13 10 7 4     14 11 8
	 * 9 6 3         15 12
	 * 5 2
	 */

	tmp = nbVar;
	for(k=1; k<N; k++) {
		if (k!=1)
			tmp=tmp-N;
		for(i=k; i<=tmp; i=i+N+1) {
			for(j=i; j<=tmp; j=j+N+1) {
				if (i != j) {
					fprintf(fp,"-%d -%d 0\n", i, j);
					nbClause++;
				}
			}
		}
	}
  
	for(k=N+1; k<(nbVar-N); k=k+N) {
		for(i=k; i<=nbVar; i=i+N+1) {
			for(j=i; j<=nbVar; j=j+N+1) {
				if (i != j) {
					fprintf(fp,"-%d -%d 0\n", i, j);
					nbClause++;
				}
			}
		}
	}
  
	for(k=(nbVar-N+1); k>1; k=k-N) {
		for(i=k; i>1; i=i-N+1) {
			for(j=i; j>1; j=j-N+1) {
				if (i != j) {
					fprintf(fp,"-%d -%d 0\n", i, j);
					nbClause++;
				}
			}
		}
	}

	tmp = 2 * N;
	for(k=(nbVar-N+2); k<nbVar; k++) {
		if (k!=(nbVar-N+2))
			tmp=tmp+N;
		for(i=k; i>=tmp; i=i-(N-1)) {
			for(j=i; j>=tmp; j=j-(N-1)) {
				if (i != j) {
					fprintf(fp,"-%d -%d 0\n", i, j);
					nbClause++;
				}
			}
		}
	}

	fseek(fp, 0, SEEK_SET);
	fprintf(fp,"p cnf %d %d \n", nbVar, nbClause);
	fclose(fp);

	printf("[NBCLOSE] %d\n",nbClause);
	
	return 0;
}
