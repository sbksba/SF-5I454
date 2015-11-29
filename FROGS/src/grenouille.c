#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int var = 0;

int transformeVar(int indice, int nbPierre){
	if (var < nbPierre){
		var++;
	}else if ( var == nbPierre){
		var = 1;
	}
	return var;
}

void afficheBlanche(int nbPierre, int *tab, int step){
	//printf("formule :");
	int i = 0;
	for(i = 0 ; i < nbPierre; i++){
		if(tab[i] == 1){
			printf(" w_%d%d",i,step);
		}else{
			printf(" !w_%d%d",i,step);
		}
		if( i != nbPierre-1){
			printf(" & ");
		}
	}
}

void afficheNoir(int nbPierre, int *tab, int step){
	//printf("formule :");
	int i = 0;
	for(i = 0 ; i < nbPierre; i++){
		if(tab[i] == 1){
			printf(" b_%d%d",i,step);
		}else{
			printf(" !b_%d%d",i,step);
		}
		if( i != nbPierre-1){
			printf(" & ");
		}
	}
}

void formule(int nbPierre, int *tab){
	//printf("formule :");
	int i = 0;
	for(i = 0 ; i < nbPierre; i++){
		if(tab[i] == 1){
			printf(" p%d",transformeVar(i,nbPierre));
		}else{
			printf(" !p%d",transformeVar(i,nbPierre));
		}
		printf(" & ");
	}
}

void mouvementSimple(int *grenouilleBlanche, int *grenouilleNoire, int nbPierre, int step){
	//Mouvement deplacement simple
	int i = 0;
	int pierreLibre = 0;
	int myVar = 0;
	int myVarBis = 0;

	int indicePierre = 0;
  
	int grenouilleTest[nbPierre];
	grenouilleTest[0]=1;
	for( i = 1; i < nbPierre; i++){
		grenouilleTest[i] = 0;
	}

	for(indicePierre = 0; indicePierre < nbPierre-1; indicePierre++){
		printf("(");
		for(i=0;i<nbPierre;i++){
			if(i+1 < nbPierre && grenouilleTest[i] == 1 && grenouilleTest[i+1] != 1){
				printf("!w_%d%d",i,step+1);
				printf(" & ");
				printf("w_%d%d",i+1,step+1);
				printf(" & ");
				printf("w_%d%d",i,step);
				printf(" & ");
				printf("!w_%d%d",i+1,step);
				grenouilleTest[i]=0;
				grenouilleTest[i+1]=1;
				i++;
			}else{
				printf("( w_%d%d = w_%d%d )",i,step+1,i,step);
			}
			printf(" & ");
		}
		//printf(" \n");
		//Meme chose pour grenouille noir
		for(i=0; i < nbPierre; i++){
			printf("(b_%d%d = b_%d%d)",i,step+1,i,step);
			if( i != nbPierre-1){
				printf(" & ");
			}
		}
		if( indicePierre < nbPierre-2 ){
			printf(" ) | ");
//printf("\n");
		}else{
			printf(" ) "); }
		//printf(")  | ");
//printf("\n");
	}

	printf("| "); 
	for(indicePierre = indicePierre; indicePierre > 0; indicePierre -- ){
		printf("(");
		//Meme chose pour grenouille blanche
		for(i=0; i < nbPierre; i++){
			printf("(w_%d%d = w_%d%d)",i,step+1,i,step);
			if( i != nbPierre-1){
				printf(" & ");
			}
		}
		printf(" & ");
		for(i=nbPierre-1;i> 0;i--){
			if(i > 0 && grenouilleTest[i] == 1 && grenouilleTest[i-1] != 1){
				printf("!b_%d%d",i,step+1);
				printf(" & ");
				printf("b_%d%d",i-1,step+1);
				printf(" & ");
				printf("b_%d%d",i,step);
				printf(" & ");
				printf("!b_%d%d",i-1,step);
				grenouilleTest[i]=0;
				grenouilleTest[i-1]=1;
				i--;
			}else{
				printf("( b_%d%d = b_%d%d )",i,step+1,i,step);
			}
			if( i > 1){
				printf(" & ");
			}
		}
		printf(" \n");
		//printf("] |\n");
		if( indicePierre > 1){
			printf(" ) | ");
//printf("\n");
		}else{
			printf(" ) ");
//printf("\n");
		}
	}
	//printf("\nFin\n");
}

void mouvementSaut(int *grenouilleBlanche, int *grenouilleNoire, int nbPierre, int step){
	//Init tableau test
	int grenouilleGrenouilleClair[nbPierre];
	int grenouilleGrenouilleFonce[nbPierre];
	int i = 0;
	for( i = 1; i < nbPierre; i++){
		grenouilleGrenouilleClair[i] = 0;
		grenouilleGrenouilleFonce[i] = 0;
  	}
	//printf("\nMouvement Saut -------------------\n");
	//Boucle saut de la grenouille clair
	int gc,gf = 0;
	for(gc = 0; gc < nbPierre-2; gc++){
		grenouilleGrenouilleClair[gc]=1;
		/*grenouilleGrenouilleFonce[gc]=1;
		  grenouilleGrenouilleFonce[gc+2]=1;*/
		printf("(");
		for(gf = 0; gf< nbPierre; gf++){
			
			grenouilleGrenouilleFonce[gf]=1;
			//grenouilleGrenouilleFonce[gf+2]=1;
			if(gc != gf){
				//printf(" gc : %d , gf : %d, i : %d ",grenouilleGrenouilleClair[gc],grenouilleGrenouilleFonce[gc+1], gf);
				if(grenouilleGrenouilleClair[gc] == 1 && 
				   grenouilleGrenouilleFonce[gc+1] && 
				   grenouilleGrenouilleFonce[gc+2] == 0 && 
				   grenouilleGrenouilleClair[gc+2] == 0){
					//printf("ici gc : %d ", gc);
					if(gc+2<nbPierre){
						printf("!w_%d%d",gc,step+1);
			  			printf(" & ");
			  			printf("w_%d%d",gc+2,step+1);
			  			printf(" & ");
			  			printf("w_%d%d",gc,step);
			  			printf(" & ");
			  			printf("!w_%d%d",gc+2,step);
			  			printf(" & ");
					}else{
						//printf("a cinq");
						printf("!w_%d%d",gc,step+1);
			  			printf(" & ");
						printf("w_%d%d",gc,step);
			  			printf(" & ");
					}
		  			for(i=0; i < gc; i++){
						printf("( w_%d%d = w_%d%d )",i,step+1,i,step);
						printf(" & ");
					}
					for(i=gc+3; i < nbPierre; i++){
						printf("( w_%d%d = w_%d%d )",i,step+1,i,step);
						printf(" & ");
					}
					printf("( w_%d%d = w_%d%d )",gc+1,step+1,gc+1,step);
					printf(" & ");
					for(i=0; i < nbPierre; i++){
				  		printf("(b_%d%d = b_%d%d )",i,step+1,i,step);
				  		if( i != nbPierre-1){
				  			printf(" & ");
					  	}
				  	}
				}
			}
			//printf(" gf %d \n", gf);
			grenouilleGrenouilleFonce[gf]=0;		
		} 
			
		printf(")  |");
//printf("\n");
	}
	for( i = 1; i < nbPierre; i++){
		grenouilleGrenouilleClair[i] = 0;
		grenouilleGrenouilleFonce[i] = 0;
  	}
	/* Mouvement saut pour les grenouille noir */
	//printf("\n Saut grenouille fonce\n");
	for(gf = nbPierre-1; gf > 1; gf -- ){
		grenouilleGrenouilleFonce[gf]=1;
		printf("(");
		for(gc = gf; gc >= 0; gc--){
			grenouilleGrenouilleClair[gc]=1;
			if(gc != gf){
				//printf(" gc : %d , gf : %d, i : %d ",grenouilleGrenouilleClair[gf-1],grenouilleGrenouilleFonce[gf], gc);
				if(grenouilleGrenouilleClair[gf-1] == 1 && grenouilleGrenouilleFonce[gf] == 1 && grenouilleGrenouilleFonce[gf-2] == 0 && grenouilleGrenouilleClair[gf-2] == 0){
					if(gf-2 >= 0){
						printf("!b_%d%d ",gf,step+1);
			  			printf(" & ");
			  			printf("b_%d%d ",gf-2,step+1);
			  			printf(" & ");
			  			printf("b_%d%d ",gf,step);
			  			printf(" & ");
			  			printf("!b_%d%d ",gf-2,step);
			  			printf(" & ");
					}else{
						//printf(" a zero");
						printf("!b_%d%d ",gf,step+1);
			  			printf(" & ");
						printf("b_%d%d ",gf,step);
			  			printf(" & ");
					}
					for(i=nbPierre-1; i >  gf; i--){
						printf("( b_%d%d = b_%d%d )",i,step+1,i,step);
						printf(" & ");
					}
					for(i=gf-3; i >= 0; i--){
						printf("( b_%d%d = b_%d%d )",i,step+1,i,step);
						printf(" & ");
					}
					printf("( b_%d%d = b_%d%d )",gc,step+1,gc,step);
					printf(" & ");
					for(i=0; i < nbPierre; i++){
				  		printf("(w_%d%d = w_%d%d )",i,step+1,i,step);
				  		if( i != nbPierre-1){
				  			printf(" & ");
					  	}
				  	}
				}else{
					//printf(" Test pas bon, ");
				}
			}
			grenouilleGrenouilleClair[gc]=0;
		}
		if( gf > 2){
			printf(" ) | ");
//printf("\n");
		}else{
			printf(" ) ");
//printf("\n");
		}
	}
}
/*
  void negationPropriete(int *grenouilleBlanche, int *grenouilleNoire, int nbPierre, int step){
  int i;
  for(i=0;i< nbPierre;i++){
  if(grenouilleBlanche[i] == 0){
  printf("w_%%
  }
  }
  }*/
int main(int argc, char **argv)
{
	if (argc != 3) {
		printf("USAGE: ./Grenouille <Grid Size>\n");
		return 1;
	}
	
	int nbPierre = atoi(argv[1]);  
	int grenouilleBlanche[nbPierre];
	int grenouilleNoire[nbPierre];
	int nbGrenouille = atoi(argv[1]) / 2;
	int step = atoi(argv[2]);
	int i = 0;
  
	/* Initilisation des tableaux */
	//printf("nbGrenouille %d\n", nbGrenouille);
	//printf("tab grenouille blanche : \n");
	for( i = 0; i < nbPierre; i++){
		if(i < nbGrenouille){
			grenouilleBlanche[i] = 1;
		}else{
			grenouilleBlanche[i] = 0;
		}
		//printf("%d",grenouilleBlanche[i]);
	}
	//printf(" \ntab grenouille noire : \n");
	for( i = 0; i < nbPierre; i++){
		if(i >= (nbPierre - nbGrenouille)){
			grenouilleNoire[i] = 1;
		}else{
			grenouilleNoire[i] = 0;
		}
		//printf("%d",grenouilleNoire[i]);
	}
  
	//printf(" \ntab init : \n");

	//printf("\nFormule init : \n");
	/*
	  for(i = 0 ; i < nbPierre; i++){
	  if(grenouilleBlanche[i] == 1){
	  printf(" e%d",transformeVar(i,nbPierre));
	  }else{
	  printf(" !e%d",transformeVar(i,nbPierre));
	  }
	  printf(" & ");
	  } &  !p2_1(0) &  !p2_2(0) &  !p2_3(0) &  !p2_4(0) &  p2_5(0) &  p2_6(0) &  p2_7(0)
	*/
	printf("(");
	afficheBlanche(nbPierre, grenouilleBlanche,0);
	printf(" &");
	afficheNoir(nbPierre, grenouilleNoire,0);
	printf(") &");
	//printf("\nfin formule init : \n");
	/* Test transition*/
  
	/* Transition simple */ 
	printf("\n");
	for( i = 0; i< step ; i++){
		mouvementSimple(grenouilleBlanche,grenouilleNoire,nbPierre,i);
		printf(" & \n");
		mouvementSaut(grenouilleBlanche,grenouilleNoire,nbPierre,i);

	}
	return 0;
}
