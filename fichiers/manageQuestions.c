#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define couleur(param) printf("\033[%sm",param)

#define Shop 300
#define nbarticles 7
#include "prototype.h"


int questions(){

char answer1[32];
  do{
  printf("Que souhaitez-vous faire ? Entrer 'Rechercher' pour rechercher un article ou sur 'Sortir' pour sortir du mode gestion\n");
  int check=scanf("%s", answer1);
  if(check!=1){
    exit(25);
  }
  if(strcmp(answer1,"Rechercher")!=0 && strcmp(answer1,"Sortir")!=0){
    printf("Veuillez reessayer\n");
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
  do{
    printf("Que voulez-vous faire maintenant ? Entrer 'Restockage' pour augmenter le stock de ce produit ou 'Sortir' pour quitter le mode gestion\n");
  scanf("%s",answer3);
  if(strcmp(answer3,"Restockage")!=0 && strcmp(answer3,"Sortir")!=0){
    printf("Veuillez reessayer");
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
  do{
  printf("Entrer 'Nom' pour rechercher l'article par son nom ou 'Numero' pour le rechercher par son numero de reference. 'Sortir' pour revenir en arriere \n ");
  scanf("%s",answer2);
  if(strcmp(answer2,"Nom")!=0 && strcmp(answer2,"Numero")!=0 && strcmp(answer2,"Sortir")!=0){
    printf("Veuillez reessayer\n");
    sleep(1);
  }

}while(strcmp(answer2,"Nom")!=0 && strcmp(answer2,"Numero")!=0 && strcmp(answer2,"Sortir")!=0);
if(strcmp(answer2,"Nom")==0){
  return 1;
}
else if(strcmp(answer2,"Numero")==0){
  return 2;
}
else if(strcmp(answer2,"Sortir")==0){
  return 0;
}
else{
  printf("Une erreur est survenue");
  exit(37);
}
}
