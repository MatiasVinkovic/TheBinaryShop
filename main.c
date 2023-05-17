#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "fichiers_h/accountGestionClient.h"
#include "fichiers_h/lastBuysDisplay.h"
#include "fichiers_h/buying_phase.h"

/*
    exit(0) -> exit normal voulu

*/

	
void videBuffer()
{
  int c;
  while((c=getchar()) != EOF && c != '\n');
 
}




int main(void){

    //MENU DU DEBUT DE PROGRAMME
    int menu_user_choice = 0;//1 achat, 2 gestion
    char nom[100];
    char prenom[100];
    int boolHasAccount = 0;    //identifier si un compte en premier lieu 
    int secondBoolHasAccount = 0; // apres avoir creer ou non un compte
    int user_choice = 0;
    char tmp_name[100];

    
    printf("=========MENU==========");
    printf("\nBienvenue dans le magasin !");
    printf("\nQue voulez vous faire ? [1,2,3]");

    printf("\n\n1) Mode achat ");
    printf("\n2) Mode gestion");
    printf("\n3)je veux absoluement quitter ce magasin\n");
    scanf("%d", &menu_user_choice);

    if(menu_user_choice == 1){
        //MODE ACHAT
        
        printf("\n\n avez vous déjà un compte ?");
        scanf("%d", &boolHasAccount);
        switch(boolHasAccount){
            case 1:
                //le client a un compte
                printf("\nvotre nom : ");
                scanf("%s", nom);
                //strcpy(tmp_name, nom);
                printf("\nvotre prenom : ");
                scanf("%s", prenom);

                
                
                if(hasAccount(tmp_name, prenom)){
                    //le client a bel et bien un compte : 
                    secondBoolHasAccount = 1;
                    break;
                }
                else{
                    //si il dit qu'il a un compte alors que non : on lui en fait creer un 
                    printf("\nvoulez vous en créer un ?");
                    scanf("%d", &user_choice);
                    switch(user_choice){
                        case 1://veut creer un compte
                        //le client n'a pas de compte
                            printf("\nvotre nom : ");
                            scanf("%s", nom);
                            strcpy(tmp_name, nom);
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
        printf("\nmode gestion");
    }
    else if(menu_user_choice == 3){
        exit(0);
    }
    else{
        printf("erreur erreur ");
    }

    
    
    //passage dans la phase mode achat
    if(secondBoolHasAccount){
        //on peut proceder a la phase d'achat
        //le client a MAINTENANT bel et bien un compte : 
        printf("\n\n            Bienvenue %s ! Ca roule ? ^^",prenom);
        displayLastBuys(nom, prenom);
        searchArticle(5);
    }
    else{   
        exit(0);
    }
    
 

    return 0;
}