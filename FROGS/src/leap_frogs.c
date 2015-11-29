#include<stdlib.h>
#include<stdio.h>

#define empty 0
#define full 1
#define TRUE 0
#define FALSE 1

#define dbg printf("[%s] %d\n",__FUNCTION__,__LINE__)

struct config_t{
	int *white_frogs;
	int *black_frogs;
	int time_step;
	int nbFrog;
};

typedef struct config_t *config;

config config_create(int nbFrog)
{
	config c = (config)malloc(sizeof(struct config_t));
	
	c->white_frogs = malloc(sizeof(int)*(nbFrog*2+1));
	c->black_frogs = malloc(sizeof(int)*(nbFrog*2+1));
	c->time_step=0;
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

void free_config(config config_frogs)
{
	free(config_frogs->white_frogs);
	free(config_frogs->black_frogs);
	free(config_frogs);
}

void print_config(config config_frogs)
{
	int i=0;

	for (i=0;i<2*config_frogs->nbFrog+1;i++) {
		if(config_frogs->white_frogs[i]){
			printf("W");
		}
		else {
			if(config_frogs->black_frogs[i]){
				printf("B");
			}
			else {
				printf("-");
			}
		}
	}
	printf("\n");
}


int compare_config(config configA, config configB)
{
	int i;

	if (configA->nbFrog == configB->nbFrog) {
		
		for (i=0;i<2*configA->nbFrog+1; i++) {
			if (configA->white_frogs[i] != configB->white_frogs[i] &&
			    configA->black_frogs[i] != configB->black_frogs[i])
				return FALSE;
		}
		return TRUE;
	}
	
	return FALSE;
}

config start_config(config config_frogs, int nbFrog)
{
	int i=0;
	int nbStone;
	nbStone = nbFrog*2+1;
  
	for (i=0;i<nbStone;i++) {
		if (i<nbFrog) {
			config_frogs->white_frogs[i] = full;
			config_frogs->black_frogs[i+1] = empty;
		}
		else {
			config_frogs->white_frogs[i] = empty;
			config_frogs->black_frogs[i+1] = full;
		}
	}
  
	config_frogs->time_step=0;
	config_frogs->nbFrog = nbFrog;
  
	return config_frogs;
}

config win_config(config config_frogs, int nbFrog)
{
	int i=0;
	int nbStone;
	nbStone = nbFrog*2+1;

	for (i=0;i<nbStone;i++) {
		if (i<nbFrog) {
			config_frogs->black_frogs[i] = full;
			config_frogs->white_frogs[i+1] = empty;
		}
		else {
			config_frogs->black_frogs[i] = empty;
			config_frogs->white_frogs[i+1] = full;
		}
	}
	config_frogs->nbFrog = nbFrog;

	return config_frogs;
}

config white_frog_slide(config config_frogs)
{
	int i=0;
	int nbStone;
	nbStone = (config_frogs->nbFrog)*2+1;
  
	for (i=0;i<nbStone-1;i++) {
		if((config_frogs->white_frogs[i] == full ) &
		   (config_frogs->white_frogs[i+1] == empty) &
		   (config_frogs->black_frogs[i+1] == empty)) {
			config_frogs->white_frogs[i+1] = full;
			config_frogs->white_frogs[i] = empty;
			config_frogs->time_step=config_frogs->time_step+1;
			break;
		}
	}
  
	return config_frogs;
}

config black_frog_slide(config config_frogs)
{
	int i=0;
	int nbStone;
	nbStone = (config_frogs->nbFrog)*2+1;
  
	for (i=nbStone-1;i>0;i--) {
		if((config_frogs->black_frogs[i] == full) &
		   (config_frogs->black_frogs[i-1] == empty) &
		   (config_frogs->white_frogs[i-1] == empty)) {
			config_frogs->black_frogs[i-1] = full;
			config_frogs->black_frogs[i] = empty;
			config_frogs->time_step=config_frogs->time_step+1;
			break;
		}
	}
  
	return config_frogs;
}

config white_frog_jump(config config_frogs)
{
	int i=0;
	int nbStone;
	nbStone = (config_frogs->nbFrog)*2+1;
  
	for (i=0;i<nbStone-2;i++) {
		if((config_frogs->white_frogs[i] == full) &
		   (config_frogs->black_frogs[i+1] == full) &
		   (config_frogs->black_frogs[i+2] == empty) &
		   (config_frogs->white_frogs[i+2] == empty)) {
			config_frogs->white_frogs[i+2] = full;
			config_frogs->white_frogs[i] = empty;
			config_frogs->time_step=config_frogs->time_step+1;
			break;
		}
	}
	
	return config_frogs;
}

config black_frog_jump(config config_frogs)
{
	int i=0;
	int nbStone;
	nbStone = (config_frogs->nbFrog)*2+1;

	for (i=nbStone-1;i>1;i--) {
		if((config_frogs->white_frogs[i] == full) &
		   (config_frogs->black_frogs[i+1] == full) &
		   (config_frogs->black_frogs[i-1] == empty) &
		   (config_frogs->white_frogs[i-1] == empty)) {
			config_frogs->black_frogs[i-1] = full;
			config_frogs->black_frogs[i+1] = empty;
			config_frogs->time_step=config_frogs->time_step+1;
			break;
		}
	}
	return config_frogs;
}

config good_config(config config_frogs)
{
	config_frogs = black_frog_slide(config_frogs);
	print_config(config_frogs);
	config_frogs = white_frog_jump(config_frogs);
	print_config(config_frogs);
	config_frogs = white_frog_slide(config_frogs);
	print_config(config_frogs);
	config_frogs = black_frog_jump(config_frogs);
	print_config(config_frogs);
	config_frogs = black_frog_jump(config_frogs);
	print_config(config_frogs);
	config_frogs = black_frog_slide(config_frogs);
	print_config(config_frogs);
	config_frogs = white_frog_jump(config_frogs);
	print_config(config_frogs);
	config_frogs = white_frog_jump(config_frogs);
	print_config(config_frogs);
	config_frogs = white_frog_jump(config_frogs);
	print_config(config_frogs);
	config_frogs = black_frog_slide(config_frogs);
	print_config(config_frogs);
	config_frogs = black_frog_jump(config_frogs);
	print_config(config_frogs);
	config_frogs = black_frog_jump(config_frogs);
	print_config(config_frogs);
	config_frogs = white_frog_slide(config_frogs);
	print_config(config_frogs);
	config_frogs = white_frog_jump(config_frogs);
	print_config(config_frogs);
	config_frogs = black_frog_slide(config_frogs);
	print_config(config_frogs);

	return config_frogs;
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("ERROR SIZE\n");
		return EXIT_FAILURE;
	}
	
	int size = atoi(argv[1]);
	config config_frogs = config_null(size);
	config test = config_null(size);

	printf("INIT\n");
	print_config(config_frogs);
	
	printf("START\n");
	config_frogs = start_config(config_frogs,size);
	print_config(config_frogs);

	printf("WIN\n");
	print_config(test);
	test = win_config(test,size);
	print_config(test);
	
	printf("[CONFIG] nbStep : %d\n",config_frogs->time_step);

	printf("GOOD\n");
	config_frogs = good_config(config_frogs);
	printf("[CONFIG] nbStep : %d\n",config_frogs->time_step);

	free_config(config_frogs);
	
	return EXIT_SUCCESS;
}
