#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define empty 0
#define full 1
#define T 1
#define F 0
#define INFINITY 42

#define DBG printf("[%s] %d\n",__FUNCTION__,__LINE__)

struct config_t{
	int *white_frogs;
	int *black_frogs;
	int step;
	int nbFrog;
};

typedef struct config_t *config;
int step=0;

config config_create(int nbFrog)
{
	config c = (config)malloc(sizeof(struct config_t));

	c->white_frogs = malloc(sizeof(int)*(nbFrog*2+1));
	c->black_frogs = malloc(sizeof(int)*(nbFrog*2+1));
	c->step = 0;
	c->nbFrog = nbFrog;

	return c;
}

config config_null(int nbFrog)
{
	int i;
	config c = config_create(nbFrog);

	for (i=0; i<(nbFrog*2+1); i++) {
		c->white_frogs[i] = empty;
		c->black_frogs[i] = empty;
	}

	return c;
}

void free_config(config c)
{
	free(c->white_frogs);
	free(c->black_frogs);
	free(c);
}

void print_config(config c)
{
	int i=0;

	for (i=0;i<2*c->nbFrog+1;i++) {
		if(c->white_frogs[i]){
			printf("W");
		}
		else {
			if(c->black_frogs[i]){
				printf("B");
			}
			else {
				printf("-");
			}
		}
	}
	printf("\n");
}

void print_bool(config c)
{
	int i;
	int nbStone = 2*c->nbFrog+1;

	printf("(");
	for (i=0; i<nbStone; i++) {
		if (c->white_frogs[i] == full)
			printf("w%d_%d",i,c->step);
		else
			printf("!w%d_%d",i,c->step);
		printf(" & ");
	}
	
	for (i=0; i<nbStone; i++) {
		if (c->black_frogs[i] == full)
			printf("b%d_%d",i,c->step);
		else
			printf("!b%d_%d",i,c->step);
		if (i < nbStone-1)
			printf(" & ");
	}
	printf(")");
}

config start_config(config c)
{
	int i=0;
	int nbStone;
	nbStone = c->nbFrog*2+1;

	for (i=0;i<nbStone;i++) {
		if (i<c->nbFrog) {
			c->white_frogs[i] = full;
			c->black_frogs[i+1] = empty;
		}
		else {
			c->white_frogs[i] = empty;
			c->black_frogs[i+1] = full;
		}
	}

	return c;
}

config win_config(config c)
{
	int i=0;
	int nbStone;
	nbStone = c->nbFrog*2+1;

	for (i=0;i<nbStone;i++) {
		if (i<c->nbFrog) {
			c->black_frogs[i] = full;
			c->white_frogs[i+1] = empty;
		}
		else {
			c->black_frogs[i] = empty;
			c->white_frogs[i+1] = full;
		}
	}
	
	return c;
}

void W_frog_slide(config c, int pres, int next)
{
	int i=0;
	int nbStone;
	int ind;
	nbStone = (c->nbFrog)*2+1;

	for (ind=0; ind<nbStone; ind++) {
		printf("(");
		for (i=0; i<nbStone; i++) {
			if ((c->white_frogs[i] == full) &
			    (c->white_frogs[i+1] == empty) &
			    (i+1 < nbStone)) {
				printf("!w%d_%d & w%d_%d & w%d_%d & !w%d_%d",i,next,i+1,next,i,pres,i+1,pres);
				i++;
			}
			else
				printf("(w%d_%d = w%d_%d) & (b%d_%d = b%d_%d)",i,next,i,pres,i,next,i,pres);
			if (i < nbStone-1)
				printf(" & ");
		}
		if (ind < nbStone-2)
			printf(") |\n");
		else {
			printf(")");
			break;
		}
		c->white_frogs[ind+1] = full;
	}
}

void B_frog_slide(config c, int pres, int next)
{
	int i=0;
	int nbStone;
	int ind;
	nbStone = (c->nbFrog)*2+1;

	for (ind=nbStone-1; ind>0; ind--) {
		printf("(");
		for (i=nbStone-1; i>=0; i--) {
			if ((c->black_frogs[i] == full) &
			    (c->black_frogs[i-1] == empty) &
			    (i >= 0)) {
				printf("!b%d_%d & b%d_%d & b%d_%d & !b%d_%d",i,next,i-1,next,i,pres,i-1,pres);
				i--;
			}
			else {
				printf("(b%d_%d = b%d_%d) & (w%d_%d = w%d_%d)",i,next,i,pres,i,next,i,pres);
			}
			if (i >= 1)
				printf(" & ");
		}
		if (ind > 1)
			printf(") |\n");
		else
			printf(")");
		c->black_frogs[ind-1] = full;
	}
}

void W_frog_jump(config c, int pres, int next)
{
	int i=0,j;
	int nbStone;
	int ind;
	nbStone = (c->nbFrog)*2+1;

	for (ind=0; ind<nbStone; ind++) {
		printf("(");
		for (i=0; i<nbStone; i++) {
			if ((c->white_frogs[i] == full) &
			    (c->white_frogs[i+2] == empty) &
			    (c->black_frogs[i+1] == full) &
			    (c->black_frogs[i+2] == empty) &
			    (i+1 < nbStone)) {
				j=i+2;
				printf("!w%d_%d & w%d_%d & w%d_%d & !w%d_%d & (b%d_%d = b%d_%d) & (w%d_%d = w%d_%d) & (b%d_%d = b%d_%d)",i,next,j,next,i,pres,j,pres,i,next,i,pres,i+1,next,i+1,pres,i+1,next,i+1,pres);
				i++;
			}
			else {
				if (i != j)
					printf("(w%d_%d = w%d_%d) & ",i,next,i,pres);
				printf("(b%d_%d = b%d_%d)",i,next,i,pres);
			}
			if (i < nbStone-1)
				printf(" & ");
		}
		if (ind < nbStone-3)
			printf(") |\n");
		else {
			printf(")");
			break;
		}
		c->white_frogs[ind] = empty;
		c->black_frogs[ind+1] = empty;
		c->white_frogs[ind+1] = full;
		c->black_frogs[ind+2] = full;
	}
}

void B_frog_jump(config c, int pres, int next)
{
	int i=0,j;
	int nbStone;
	int ind;
	nbStone = (c->nbFrog)*2+1;

	for (ind=nbStone-1; ind>0; ind--) {
		printf("(");
		for (i=nbStone-1; i>=0; i--) {
			if ((c->black_frogs[i] == full) &
			    (c->black_frogs[i-2] == empty) &
			    (c->white_frogs[i-1] == full) &
			    (c->white_frogs[i-2] == empty) &
			    (i-1 >= 0)) {
				j=i-2;
				printf("!b%d_%d & b%d_%d & b%d_%d & !b%d_%d & (w%d_%d = w%d_%d) & (w%d_%d = w%d_%d) & (b%d_%d = b%d_%d)",i,next,
				       j,next,
				       i,pres,
				       j,pres,
				       i,next,
				       i,pres,
				       i-1,next,
				       i-1,pres,
				       i-1,next,
				       i-1,pres);
				i--;
			}
			else {
				if (i != j)
					printf("(b%d_%d = b%d_%d) & ",i,next,i,pres);
				printf("(w%d_%d = w%d_%d)",i,next,i,pres);
			}
			if (i > 0)
				printf(" & ");
		}
		if (ind > 2)
			printf(") |\n");
		else {
			printf(")");
			break;
		}
		c->black_frogs[ind] = empty;
		c->white_frogs[ind-1] = empty;
		c->black_frogs[ind-1] = full;
		c->white_frogs[ind-2] = full;
	}
}

void leap (config c, int size, int step)
{
	int i;

	start_config(c);
	print_bool(c);
	printf(" &\n");
	for (i=0; i<step; i++) {
		c = config_null(size);
		/* printf("WHITE SLIDE\n"); */
		c->white_frogs[0] = full;
		W_frog_slide(c, i, i+1);
		printf(" &\n");

		/* printf("\nBLACK SLIDE\n"); */
		c = config_null(size);
		c->black_frogs[size*2] = full;
		B_frog_slide(c, i, i+1);
		printf(" &\n");

		/* printf("\nWHITE JUMP\n"); */
		c = config_null(size);
		c->white_frogs[0] = full;
		c->black_frogs[1] = full;
		W_frog_jump(c, i, i+1);
		printf(" &\n");

		/* printf("\nBLACK JUMP\n"); */
		c = config_null(size);
		c->white_frogs[(size*2)-1] = full;
		c->black_frogs[size*2] = full;
		B_frog_jump(c, i, i+1);
		/* if (i != step && i != 0) */
			printf(" &\n");
		/* else */
		/* 	printf("\n"); */
	}
	win_config(c);
	print_bool(c);
	printf("\n");
}

int main(int argc, char **argv)
{	
	if (argc != 3) {
		printf("USAGE: %s <Number of frogs> <Number of step>\n",argv[0]);
		return 1;
	}

	int size = atoi(argv[1])/2;
	config c = config_null(size);

	leap(c,size,atoi(argv[2]));
		
	free_config(c);

     	return EXIT_SUCCESS;
}
