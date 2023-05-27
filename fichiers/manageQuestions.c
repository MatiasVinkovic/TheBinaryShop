#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define couleur(param) printf("\033[%sm",param)

#include "prototype.h"

// retourne 0 si l'utilisateur veut sortir du mode gestion et 1 s'il veut poursuivre sa recherche
int questions(){

char answer1[32];
  //on recommence tant qu'un des deux n'a pas été choisi
  do{
  printf("\nQue souhaitez-vous faire ? \n[Rechercher]\n[Sortir] \n     ->");
  int check=scanf("%s", answer1);
  if(check!=1){
    printf("erreur detectée");exit(25);
  }
  if(strcmp(answer1,"Rechercher")!=0 && strcmp(answer1,"Sortir")!=0){
    couleur("31");printf("Veuillez reessayer\n"); couleur("0");
    sleep(1);
  }
  

}while(strcmp(answer1,"Rechercher")!=0 && strcmp(answer1,"Sortir")!=0);
sleep(1);
if(strcmp(answer1,"Sortir")==0){
  return 0;
}
else{return 1;}
}


int question2(){
  char answer3[32];
  // on recommence tant que la réponse n'est pas valide
  do{
    printf("\nQue voulez-vous faire maintenant ? \n[Restockage]\n[Sortir]\n      ->");
  if(scanf("%s",answer3)!=1){printf("erreur detectee");exit(10);}
  if(strcmp(answer3,"Restockage")!=0 && strcmp(answer3,"Sortir")!=0){
    couleur("31");printf("Veuillez reessayer");couleur("0");
    sleep(1);
  }
  }while(strcmp(answer3,"Restockage")!=0 && strcmp(answer3,"Sortir")!=0);
  if(strcmp(answer3,"Sortir")==0){
    return 0;
  }
  else{
    return 1;
  }
}

int numOrName(){
char answer2[32];
  // on demande tant que la réponse n'est pas l'une des deux attendues
  do{
  printf("\n\n      ------Recherche un produit par------ \n\n - [Nom]\n - [Numero]\n - [Sortir]\n     ->");
  scanf("%s",answer2);
  if(strcmp(answer2,"Nom")!=0 && strcmp(answer2,"Numero")!=0 && strcmp(answer2,"Sortir")!=0){
    couleur("31");printf("Veuillez reessayer\n");couleur("0");
    sleep(1);
  }

}while(strcmp(answer2,"Nom")!=0 && strcmp(answer2,"Numero")!=0 && strcmp(answer2,"Sortir")!=0);
  //retourne 1 si l'utilisateur a choisi d'effectuer une recherche par le nom
if(strcmp(answer2,"Nom")==0){
  return 1;
}
  // retourne 2 si l'utilisateur a choisi le numéro de référence
else if(strcmp(answer2,"Numero")==0){
  return 2;
}
  // retourne 0 si l'utilisateur a choisi de sortir du mode gestion 
else if(strcmp(answer2,"Sortir")==0){
  return 0;
}
  // on quitte le programme si il y a un problème
else{
  printf("Une erreur est survenue");
  exit(37);
}
}
