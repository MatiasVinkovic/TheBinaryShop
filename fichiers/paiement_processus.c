#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "prototype.h"



float returnTotalPrice(){
    FILE* total_price = fopen("total_price.txt","r");
    if(total_price == NULL){exit(1);}
    float lastBuyPrice;
    fscanf(total_price,"%f", &lastBuyPrice);
    fclose(total_price);
    return lastBuyPrice;
}

void deliveryMode(float lastBuyPrice){
    int delivery_mode = 0;
    int error_gestion = 0;
    char client_adress[50];
    char client_city[50];

    printf("\nComment voulez vous vous faire livrer votre colis ? ");
    printf("\n1) Livraison à domicile [gratuite dès 350 euros d'achats]");
    printf("\n2) Livraison en point relais [à l'école d'ingénieur CY-Tech]");
    do{error_gestion = 0;
        if(scanf("%d", &delivery_mode) != 1){
            couleur("31");printf("\nInvalid input ->Please enter a correct number\n");couleur("0");
            scanf("%*[^\n]");
            scanf("%*c");
            error_gestion = -1;
        }
        if(delivery_mode != 1 && delivery_mode != 2){error_gestion = -1;}
    }while(error_gestion == -1);

    switch(delivery_mode){
        case 1:
            if(lastBuyPrice >= 350){
                printf("\nVous bénéficiez de la livraison gratuite : votre total d'achat est de %.1f€", lastBuyPrice);
                printf("\nVeuillez nous fournir votre adresse : ->  ");
                scanf("%s", client_adress);
                printf("\nVotre ville : ->  ");scanf("%s", client_city);
                printf("Très bien, nous livrerons votre commande sous 15 jours ouvrés !");
                exit(1);
            }
            else{
                printf("\nVotre total d'achat est de %.1f€, dont 15€ de frais de livraisons", lastBuyPrice);
                sleep(1);printf("\nSoit un total de %.1f€", lastBuyPrice+15);
                printf("\nVeuillez nous fournir votre adresse : ->  ");
                scanf("%s", client_adress);
                printf("\nVotre ville : ->  ");scanf("%s", client_city);
                printf("Très bien, nous livrerons votre commande sous 15 jours ouvrés !");
                exit(1);
            }break;
        case 2:
                printf("\nVous bénéficiez de la livraison gratuite : votre total d'achat est de %.1f€", lastBuyPrice);
                printf("\nVeuillez nous fournir votre adresse : ->  ");
                scanf("%s", client_adress);
                printf("\nVotre ville : ->  ");scanf("%s", client_city);
                printf("Très bien, nous livrerons votre commande sous 15 jours ouvrés !");
                exit(1);
                break;
    }

    exit(0);
}


int getIntLen(long long number){
    char tmp[30];
    sprintf(tmp, "%lld", number);
    return strlen(tmp);
}

void paiement(){

    int paiement_mode = 0;
    int error_gestion = 0;
    long long card_number = 0;
    int crypto;
    int hasGiftCard = 0;
    int code = 0;
    int tmp;
    float total_price = returnTotalPrice();
                        //10% reduc, 20% reduc....50% reduc
    int code_list[5] = {184585, 195735, 1974741, 8585937, 359575};

    printf("\n\nVeuilez choisir un moyen de paiement :  \n");
    printf("\n1) Carte bleu [VISA,CB,MASTERCARD]");
    printf("\n2) Bitcoin (bientôt disponible) \n  ->");
    do{error_gestion = 0;
        if(scanf("%d", &paiement_mode) != 1){
            couleur("31");printf("\nInvalid input ->Please enter a correct number\n");couleur("0");
            scanf("%*[^\n]");
            scanf("%*c");
            error_gestion = -1;
        }
        if(paiement_mode != 1 && paiement_mode != 2){error_gestion = -1;}
    }while(error_gestion == -1);

    switch(paiement_mode){
        case 1: 
            printf("\nVeuillez à l'abri des regards, saisir votre numéro de carte bancaire (sans espaces): ");
            printf(" \n                ex :    4000 1234 5678 5355\n       ->");
            do{error_gestion = 0;
                if(scanf("%lld", &card_number) != 1){
                    couleur("31");printf("\nInvalid input ->Please enter a correct number\n");couleur("0");scanf("%*[^\n]");scanf("%*c");
                    error_gestion = -1;
                }
                if(getIntLen(card_number) != 1){error_gestion = -1;couleur("31");printf("\nVeuiilez renter un numéro de carte valide\n");couleur("0");}
            }while(error_gestion == -1);
            //printf("la longueur du chiffre est de %d", getIntLen(card_number));
            
            printf("\nVeuillez saisir votre cryptogramme : (ex 569;190;666(évitez celui-ci)) : ");
            do{error_gestion = 0;
                if(scanf("%d", &crypto) != 1){couleur("31");printf("\nInvalid input ->Please enter a correct number\n");couleur("0");scanf("%*[^\n]");scanf("%*c");
                    error_gestion = -1;
                }
                if(getIntLen(crypto)!=3){error_gestion = -1;couleur("31");printf("\nVeuiilez renter un numéro de carte valide\n");couleur("0");}
            }while(error_gestion == -1);
            
            do{error_gestion = 0;
                printf("\nAvez vous une carte cadeau/Code promotionnel ? (1/0) : ");
                if(scanf("%d", &hasGiftCard) != 1){couleur("31");printf("\nInvalid input ->Please enter a correct number\n");couleur("0");scanf("%*[^\n]");scanf("%*c");
                    error_gestion = -1;
                }
                if(hasGiftCard!=1 && hasGiftCard!= 0){error_gestion = -1;}
            }while(error_gestion == -1);


            //dans le cas où il a une carte
            if(hasGiftCard == 1){
                printf("\nVeuillez rentrer votre code promotionnel (tapez 1111 si vous n'en avez pas) : ");
                do{error_gestion = 0;
                    if(scanf("%d", &code) != 1){couleur("31");printf("\nInvalid input ->Please enter a correct \n");couleur("0");scanf("%*[^\n]");scanf("%*c");
                        error_gestion = -1;
                    }
                    for(int i = 0; i<5;i++){
                        if(code_list[i] == code){
                            hasGiftCard = -1;
                        }
                        else if(code == 1111){
                            printf("\n\nRecommencez alors la procédure :)");
                            paiement();
                            break;
                        }
                        else{
                            error_gestion = -1;
                        }
                    }
                }while(error_gestion == -1 && hasGiftCard != -1);                
                
                //on fait les reductions
                for(int j = 0; j<5;j++){
                    if(code == code_list[j]){
                        tmp = j;
                        printf("\nAvec cette carte, vous bénéficiez de %d0 pourcents de réduction",j+1);
                        total_price = total_price - ( ((j+1)*0.1) *total_price); //j+1*10 le tout divise par 100 donc *0.1
                        printf("\nLe prix total est alors maintenant %.1f€", total_price);
                        deliveryMode(total_price);      
                    }
                }

            }
            deliveryMode(total_price);
        
            break;
        case 2:
            printf("\nNous sommes désolés, mais ce moyen de paiement n'est pas encore disponile ...");
            paiement();break;
     }



}