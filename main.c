#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define couleur(param) printf("\033[%sm",param)

#include "fichiers_h/accountGestionClient.h"
#include "fichiers_h/lastBuysDisplay.h"
#include "fichiers_h/buying_phase.h"



/*
    exit(0) -> exit normal voulu

*/


int main(void){

    //MENU DU DEBUT DE PROGRAMME
    
    char nom[100];
    char prenom[100];
    int boolHasAccount = 0;    //identifier si un compte en premier lieu 
    int secondBoolHasAccount = 0; // apres avoir creer ou non un compte
    int user_choice = 0;
    char tmp_name[100];
    int error_gestion =0;

    //on met le panier de l'user d'avant à 0
    FILE* total_price = fopen("fichiers_h/total_price.txt","w");if(total_price==NULL){exit(1);}
    fputs("0",total_price);fclose(total_price);
    int menu_user_choice = 0;//1 achat, 2 gestion
    couleur("36");


                printf("            WELCOME TO \n");
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
        printf("\n3)je veux absoluement quitter ce magasin\n");
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
        printf("\nmode gestion");
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
        searchArticle(tmp_name, prenom,5);
    }
    else{   
        exit(0);
    }
    couleur("0");
 

    return 0;
}