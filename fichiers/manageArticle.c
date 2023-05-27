#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define couleur(param) printf("\033[%sm",param)


#include "prototype.h"

Article* creationtableau(int N){
  int i=0;
  FILE *products=NULL;
  products=fopen("produits.txt","r");
if(products==NULL){
  printf("Erreur d'ouverture\n");
  exit(2);
}
  // on déclare le tableau qui contiendra tous les articles
  Article* tab=NULL;
  if(N<=0){
    printf("Erreur avec le nombre d'articles");
    exit(10);
  }
  // on alloue l'espace nécéssaire au pointeur pour qu'il contienne tous les articles
  tab=malloc(N*(sizeof(Article)));
  if(tab==NULL){
    printf("Erreur avec le tableau");
    exit(11);
  }
  // on récupère les informations dans le fichier produit pour les attribuer à chaque article du tableau
  for( i=0;i<N;i++){
fscanf(products,"%d %s %f %d %d", &tab[i].ref_number, tab[i].name, &tab[i].price,&tab[i].size, &tab[i].qte);

}

fclose(products);
 return tab;
}





void displaysearchedarticle(Article* tab, int N, char name[6], int L){
  if(tab == NULL || N <= 0){
    printf("Erreur de tableau ou de nombre d'article");
        exit(72);
    }
  int i;
  //si on cherche par le nom alors le numéro de référence (L) sera nul.
  if(L==0){
  for(i=0;i<N;i++){
    if(strcmp(name,tab[i].name)==0){
      couleur("32");printf("\nNous avons trouve l'article ! \n "); couleur("0");
      couleur("33");printf("nom : %s \n numero de reference : %03d \n prix : %.2f€ \n quantite : %d \n taille : %d \n",tab[i].name,tab[i].ref_number,tab[i].price,tab[i].qte,tab[i].size);couleur("0");
    }

  }
  }
  //si on cherche par le numéro de référence alors le nom sera nul.
  else if(strcmp(name,"")==0){
    for(i=0;i<N;i++){
      if(L==tab[i].ref_number){
        couleur("32");printf("\nNous avons trouve l'article ! \n "); couleur("0");
        couleur("33");printf("nom : %s \n numero de reference : %03d \n prix : %.2f€ \n quantité restante : %d \n taille : %d \n",tab[i].name,tab[i].ref_number,tab[i].price,tab[i].qte,tab[i].size);couleur("0");      }
    }
  }
  else{
    couleur("31");printf("Une erreur s'est produite");couleur("0");
    exit(20);
  }

}

// retourne 1 si l'article a bien été trouvé, 0 sinon
int isArticleIn(Article* tab, int N, char name[32], int L){
  if(tab == NULL || N <= 0){
    printf("Erreur de tableau ou de nombre d'article");
        exit(70);
    }

  int i;
  // si on cherche par le nom
  if(L==0){
    for(i=0;i<N;i++){
      if(strcmp(name,tab[i].name)==0){
        // printf("Nous avons trouve l'article ! \n nom : %s \n numero de reference : %03d \n prix : %f \n quantite : %d \n taille : %d \n",tab[i].nom,tab[i].numero,tab[i].prix,tab[i].qtite,tab[i].taille);
        return 1;
      }
      }
  }
  // si on cherche par le numéro de référence
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

void temporalAspect(int number_search,char name_search[32]){
    FILE* file = fopen("produits.txt", "r");
    if(file == NULL){exit(1);}
    Article* tab = malloc(NBR_ARTICLE*sizeof(Article));
    for(int i = 0; i<NBR_ARTICLE;i++){
        fscanf(file, "%d %s %f %d %d", &tab[i].ref_number, tab[i].name, &tab[i].price,&tab[i].size, &tab[i].qte);
    }
    fclose(file);

    if(tab == NULL){exit(1);} //verif du tableau
    int cooldown = 0;
    
    //si on recherche par numero de reference 
    if(number_search == 0){
      for(int i = 0; i<NBR_ARTICLE; i++){
        if(strcmp(name_search, tab[i].name) == 0){
          cooldown = tab[i].size*1.5;
          sleep(cooldown);
        }
      }
    }
  // si on chercher par nom
    else if(strcmp(name_search,"") == 0){
      for(int i = 0; i<NBR_ARTICLE; i++){
        if(tab[i].ref_number == number_search){
          cooldown = tab[i].size*1.5;
          sleep(cooldown);
        }
      }
    }
// on libère l'espace alloué par la fonction malloc
  free(tab);
}
