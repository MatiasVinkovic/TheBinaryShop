#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define couleur(param) printf("\033[%sm",param)


#include "prototype.h"



void displaysearchedarticle(Article* tab, int N, char name[6], int L){
  if(tab == NULL || N <= 0){
        exit(72);
    }
  int i;
  if(L==0){
  for(i=0;i<N;i++){
    if(strcmp(name,tab[i].name)==0){
      couleur("32");printf("\nNous avons trouve l'article ! \n "); couleur("0");
      couleur("33");printf("nom : %s \n numero de reference : %03d \n prix : %f \n quantite : %d \n taille : %d \n",tab[i].name,tab[i].ref_number,tab[i].price,tab[i].qte,tab[i].size);couleur("0");
    }

  }
  }
  else if(strcmp(name,"")==0){
    for(i=0;i<N;i++){
      if(L==tab[i].ref_number){
        couleur("32");printf("\nNous avons trouve l'article ! \n "); couleur("0");
        couleur("33");printf("nom : %s \n numero de reference : %03d \n prix : %.1f€ \n quantité restante : %d \n taille : %d \n",tab[i].name,tab[i].ref_number,tab[i].price,tab[i].qte,tab[i].size);couleur("0");      }
    }
  }
  else{
    couleur("31");printf("Une erreur s'est produite");couleur("0");
    exit(20);
  }

}


int isArticleIn(Article* tab, int N, char name[32], int L){
  if(tab == NULL || N <= 0){
        exit(70);
    }

  int i;
  if(L==0){
    for(i=0;i<N;i++){
      if(strcmp(name,tab[i].name)==0){
        // printf("Nous avons trouve l'article ! \n nom : %s \n numero de reference : %03d \n prix : %f \n quantite : %d \n taille : %d \n",tab[i].nom,tab[i].numero,tab[i].prix,tab[i].qtite,tab[i].taille);
        return 1;
      }
      }
  }
  else if(strcmp(name,"")==0){
    for(i=0;i<N;i++){
      if(L==tab[i].ref_number){
        return 1;
      }
  }
  }  
else{
  printf("Une erreur est survenue");
  return 0;
}
}