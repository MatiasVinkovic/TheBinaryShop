#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define couleur(param) printf("\033[%sm",param)
#define SHOP 300
#define NBR_ARTICLE 13

#include "prototype.h"

int refill(Article* tab,int N, int ref_numberofref, char articlename[32],int SO){
  int error_gestion = 0;
  int i,j,l,k=0;
  FILE*Tmp=NULL;
  int A,f;
  if(tab==NULL || N<=0){
    printf("Erreur avec le tableau\n");
    exit(35);
  }

  do{
    error_gestion = 0;
    printf("De combien voulez-vous augmenter le stockage ?\n[666] pour sortir du programme\n");
    if(scanf("%d",&A) != 1){scanf("%*[^\n]");scanf("%*c");error_gestion=-1;}
    //while (getchar() != '\n');
    if(A <= 0){error_gestion = -1;}
    if(A==666){
      printf("Passez une bonne journee !");
      exit(0);
    }
  }while(error_gestion == -1);
  //On ouvre le nouveau fichier texte qui contiendra la quantité ajoutée
  Tmp=fopen("tmp.txt","w");
  if(Tmp==NULL){
    printf("Erreur d'ouverture\n");
    exit(38);
  }
  //Si on a recherché l'article par le numéro de référence, donc pas par le nom
  if(strcmp(articlename,"")==0){
   for( j=0;j<N;j++){
  if(ref_numberofref==tab[j].ref_number){
    SO+=tab[j].size*A;
    k=j;//on retient l'indice du produit pour pouvoir utiliser sa taille plus tard
  }
}
if(SO>SHOP){
  fclose(Tmp);
  return 0;
}
else{
  tab[k].qte+=A;
}
}
  //Même principe en effectuant une recherche par le nom
else if(ref_numberofref==0){
for( j=0;j<N;j++){
  if(strcmp(articlename,tab[j].name)==0){
    SO+=tab[j].size*A;
    k=j;
  }
}
if(SO>SHOP){
  fclose(Tmp);
  return 0;
}
else{
  tab[k].qte+=A;
}
}
  //on affiche donc dans le fichier les données de chaque article y compris la nouvelle quantité de l'article en question
for(i=0;i<N;i++){
  fprintf(Tmp,"%d %s %.2f %d %d\n", tab[i].ref_number, tab[i].name, tab[i].price,tab[i].size, tab[i].qte);
}

fclose(Tmp);

return 1;

}


/*
    exit(0) -> exit normal voulu

*/


int main(){

    //MENU DU DEBUT DE PROGRAMME

    char nom[100];
    char prenom[100];
    int boolHasAccount = 0;    //identifier si un compte en premier lieu
    int secondBoolHasAccount = 0; // apres avoir creer ou non un compte
    int user_choice = 0;
    char tmp_name[100];
    int error_gestion =0;
    int want_to_reboot = 0;

    //on met le panier de l'user d'avant à 0
    FILE* total_price = fopen("total_price.txt","w");if(total_price==NULL){exit(1);}
    fputs("0",total_price);fclose(total_price);
    int menu_user_choice = 0;//1 achat, 2 gestion

    //gros do while pour revenir au menu principal à la fin du programme
    do{



    couleur("36");


                printf("            WELCOME TO THE\n");
                        printf("\n  __   ___   __            ___  _   _  _____  ____   ");
                        printf("\n /. | / _ \\ /. |    ___   / __)( )_( )(  _  )(  _ \\ ");
                        printf("\n(_  _| (_) |_  _)  (___)  \\__ \\ ) _ (  )(_)(  )___/  ");
                        printf("\n  (_) \\___/  (_)          (___/(_) (_)(_____)(__)\n\n");couleur("0");

    couleur("33");
    do{
        error_gestion = 0;
        printf("=========MENU==========");
        printf("\nBienvenue dans le magasin !");
        printf("\nQue voulez vous faire ? [1,2,3]");

        printf("\n\n1) Mode achat ");
        printf("\n2) Mode gestion");
        printf("\n3)je veux absoluement quitter ce magasin\n    ->");
        couleur("0");
        if(scanf("%d", &menu_user_choice) != 1){
            couleur("31");printf("\nInvalid input ->Please enter a correct number\n");couleur("0");
            scanf("%*[^\n]"); //on vide le buffer
            scanf("%*c");
            error_gestion = -1;
        }
        else if(menu_user_choice != 1 && menu_user_choice!=2 && menu_user_choice!=3){
            error_gestion = -1;
        }
    }while(error_gestion ==-1);


    if(menu_user_choice == 1){
        //MODE ACHAT
        do{
        error_gestion = 0;
        printf("\n\n avez vous déjà un compte ?\n1) oui j'ai un compte \n0) non je n'en ai pas\n ->");
            if(scanf("%d", &boolHasAccount) !=1){
                couleur("31");printf("\nInvalid input ->Please enter a correct number\n");couleur("0");
                scanf("%*[^\n]");
                scanf("%*c");
                error_gestion = -1;}if(boolHasAccount != 1 && boolHasAccount!= 0){error_gestion = -1;}
        }while(error_gestion == -1);


        switch(boolHasAccount){
            case 1:


                //le client a un compte
                printf("\nvotre nom : ");
                scanf("%s", nom);
                strcpy(tmp_name, nom);
                printf("\nvotre prenom : ");
                scanf("%s", prenom);



                if(hasAccount(nom, prenom)){
                    //le client a bel et bien un compte :
                    secondBoolHasAccount = 1;
                    break;
                }
                else{
                    //si il dit qu'il a un compte alors que non : on lui en fait creer un
                    do{
                    error_gestion = 0;
                    printf("\nVoulez vous en créer un ? \n1) oui \n0) non j'en ai aucune envie, laissez moi partir d'ici !\n   -->");
                    if(scanf("%d", &user_choice)!=1){
                        couleur("31");printf("\nInvalid input ->Please enter a correct number\n");couleur("0");
                        scanf("%*[^\n]");
                        scanf("%*c");
                        error_gestion = -1;
                        }if(user_choice!=1 && user_choice !=0){error_gestion = -1;}
                    }while(error_gestion == -1);

                    switch(user_choice){
                        case 1://veut creer un compte
                        //le client n'a pas de compte
                            printf("\nvotre nom : ");
                            scanf("%s", nom);
                            printf("\nvotre prenom : ");
                            scanf("%s", prenom);
                            creationCompteClient(tmp_name, prenom);
                            secondBoolHasAccount = 1;
                            break;
                        case 0://ne veut pas creer un compte
                            printf("\nmerci de votre visite, à bientot !");
                            exit(0);
                            break;
                    }
                }
                break;
            case 0:
                //le client n'a pas de compte
                printf("\nvotre nom : ");
                scanf("%s", nom);
                strcpy(tmp_name, nom);
                printf("\nvotre prenom : ");
                scanf("%s", prenom);
                creationCompteClient(tmp_name, prenom);
                secondBoolHasAccount = 1;
                break;
        }
    }
    else if(menu_user_choice == 2){
        //mode gestion

        Article* tabarticles;
        int i,j,k,lowstock=5,count=0,occupiedplace=0,remainingplace=0;
        int a,b,c/*,d,e*/;
        char searchname[32]="";
        int searchref_number=0;
        char try[40];
        int isIn = 0;
        int error_gestion = 0;


    do{
      printf("\nVeuillez entrer le mot de passe \n   ->");
      scanf("%s",try);
      if(strcmp("bonne_note_svp", try)!=0){
          couleur("31");printf("Acces refuse\n");couleur("0");
          sleep(1);
      }
      else{
          couleur("32");printf("Acces autorise\n\n");couleur("0");
          sleep(1);break;
      }
    }while(strcmp("bonne_note_svp",try)!=0);
// on remplit le tableau à l'aide de la fonction correspondante
    tabarticles = creationtableau(NBR_ARTICLE);
// on calcule l'espace occupé dans le magasin
    for(k=0;k<NBR_ARTICLE;k++){
        occupiedplace+=(tabarticles[k].qte*tabarticles[k].size);
    }
    remainingplace=SHOP-occupiedplace;
      if(remainingplace<0){
        printf("Nous sommes désolés, mais le magasin est saturé. Nous allons donc vous faire sortir du programme. Cependant, vous pouvez toujours nous aider en achetant des articles. ;)");
        exit(1);

    quantitiessort(tabarticles,NBR_ARTICLE);

    for(i=0;i<NBR_ARTICLE;i++){
    if(tabarticles[i].qte==0){
        couleur("31");printf("\nLe stock de %s est epuise ! \n",tabarticles[i].name);couleur("0");
        count++;
    }
    }
    for(j=0+count;j<lowstock+count;j++){
      couleur("33");printf("Il ne reste que %d de %s \n",tabarticles[j].qte,tabarticles[j].name);couleur("0");

    }
    couleur("32");printf("Il reste %d de place dans le magasin\n",remainingplace);couleur("0");
    sleep(1);
    numsort(tabarticles,NBR_ARTICLE);
    a=questions();
    if(a==0){
    printf("Passez une bonne journée !");
    exit(0);
    }
    else{
    b=numOrName();

// on cherche par le nom de l'article
    if(b==1){
    do{
        error_gestion = 0;isIn = 0;
        printf("\nRentrez ici le nom du produit : \n('Sortir' pour quitter)\n   ->");
        scanf("%s",searchname);

        if(error_gestion == 0){
            for(int x = 0; x<NBR_ARTICLE;x++){
                if(strcmp(searchname,tabarticles[x].name) == 0){
                    isIn = -1;
                }
            }
            }
            if(isIn !=-1){error_gestion=-1;}

        if(strcmp(searchname,"Sortir")==0){
          printf("\nPassez une bonne journée");
        exit(0);
        }
    }while(error_gestion==-1);

    if(isArticleIn(tabarticles,NBR_ARTICLE,searchname,searchref_number)==1){
    displaysearchedarticle(tabarticles,NBR_ARTICLE,searchname,searchref_number);
    }
    }
// on cherche par le numéro de référence
    else if(b==2){
    do{
            error_gestion = 0;
            isIn = 0;
            printf("\nRentrez le numéro de reférence : \n'666 pour sortir'\n  ->");
            if(scanf("%d",&searchref_number) != 1){scanf("%*[^\n]");scanf("%*c");error_gestion=-1;}

            if(error_gestion == 0){
            for(int w = 0; w<NBR_ARTICLE;w++){
                if(tabarticles[w].ref_number == searchref_number){
                    isIn = -1;
                }
            }
            }
            if(searchref_number == 666){printf("\npassez une bonne journée !\n");exit(0);}

            if(isIn !=-1){error_gestion=-1;}

        }while(error_gestion == -1);

        if(isArticleIn(tabarticles,NBR_ARTICLE,searchname,searchref_number)==1){
        displaysearchedarticle(tabarticles,NBR_ARTICLE,searchname,searchref_number);
        }
        }
        else if(b==0){
        printf("\nPassez une bonne journee\n");
        exit(0);
        }
        }
        if(question2()==0){
        printf("\nPassez une bonne journee !\n");
        exit(0);
        }
        else{
        do{
            c=refill(tabarticles,NBR_ARTICLE,searchref_number,searchname,occupiedplace);
            if(c==0){
                couleur("31");printf("\nRestockage impossible. Il n'y a pas assez de place dans le magasin\n");couleur("0");
            }
          if(c==1){
            printf("\nLe produit sera arrivé à 404-Shop dans quelques heures...");
          }
        }while(c!=1);
                


        }
      // on libère l'espace alloué par la fonction malloc
      // on supprime le premier fichier produits et on le remplace donc par le nouveau avec la nouvelle quantité si le restockage s'est bien passé
        remove("produits.txt");
        rename("tmp.txt", "produits.txt");
        
        
  
      temporalAspect(searchref_number,searchname);

      couleur("32");printf("\nLe restockage s'est bien passe");couleur("0");
      free(tabarticles);


      //fin du mode gestion
    }
    else if(menu_user_choice == 3){
          exit(0);
      }
          




    //passage dans la phase mode achat
    if(secondBoolHasAccount){
        //on peut proceder a la phase d'achat
        //le client a MAINTENANT bel et bien un compte :
        couleur("35");printf("\n\n            Bienvenue %s ! Ca roule ? ^^",prenom);couleur("0");
        strcpy(tmp_name, nom);
        displayLastBuys(nom, prenom);
        searchArticle(tmp_name, prenom,NBR_ARTICLE);
    }
    couleur("0");



  do{
    error_gestion = 0;
    printf("\n\nQue voulez vous faire ?\n1)Revenir au menu principal\n2)Quitter 404-Shop :( \n   -> ");
    if(scanf("%d",&want_to_reboot) != 1){scanf("%*[^\n]");scanf("%*c");error_gestion=-1;}
  }while(error_gestion == -1);

}while(want_to_reboot == 1);

couleur("32");printf("\n\nPassez une agréable journée :) ");couleur("0");


    return 0;
}
