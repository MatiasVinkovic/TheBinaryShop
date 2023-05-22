#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "unsubscribe.h"
#include "paiement_processus.h"

#define NBR_ARTICLE 5
#define ACHAT_MAX 10

/*
    exit(1) => erreur ouverture de fichier
    exit(2) => erreur pointeur sur tableau

*/

//structure du produit
typedef struct Article{
    //structure complete d'un produit
    int ref_number;
    char name[32];
    float price;
    int size;
    int qte;
}Article;

int verifierScanF(int number){
    if (scanf("%d", &number) != 1) {
        printf("Erreur : la saisie n'est pas un nombre entier.\n");
        return 0;
    }
    else{
        //c'est ok on continue
        return 1;
    }
}



void displayArticle(int ref_number, char product_name[], Article tab[], int index){
    printf("\n          -----Produit-----");
    printf("\n\n          Nom du produit : [%s]", tab[index].name);
    printf("\n          Prix TTC : [%.1f€]", tab[index].price);
    printf("\n          la quantité restante est : <%d>\n\n", tab[index].qte);
}


void decrementArticleQuantity(int target_line, int decrement){
    /*Pour modifier la quantité d'un produit, il faut modifier le fichier texte
    actuel. 
    
    Pour cela, on creer un fichier temporaire 'fichier_tmp'. On va copier 
    les lignes du fichier d'origine dans 'fichier_tmp' jusqu'a atteindre la ligne
    que l'on veut modifier : celle-ci on écrit ce qu'on veut dedans
    par la suite on copie le reste du fichier
    */

    //fichier temporaire et fichier_source
    FILE* product_file = fopen("fichiers_h/produits.txt", "r");
    FILE* fichier_tmp = fopen("fichiers_h/tmp.txt", "w");
    if((fichier_tmp == NULL) || (product_file == NULL)){exit(1);}//verif

    //tableau de produits
    Article* tab = malloc(NBR_ARTICLE*sizeof(Article));//allocation dynamique du tableau de structure en fonction du nombre d'article (n)
    if(tab==NULL || NBR_ARTICLE<=0){printf("\nerrorTab");exit(2);}//verif
    //on a maintenant recuperer tout dans le tableau      
            //car premiere ligne ne compte pas
    for(int i = 0; i<NBR_ARTICLE;i++){
        fscanf(product_file, "%d %s %f %d %d", &tab[i].ref_number, tab[i].name, &tab[i].price,&tab[i].size, &tab[i].qte);
    }

    //on ferme et on réouvre le fichier produit
    fclose(product_file);
    product_file = fopen("fichiers_h/produits.txt", "r");
    if((product_file == NULL)){exit(1);}//verif

    char ligne_courante[100];
    int acc = 0;

    //on parcourt le fichier ligne par ligne
    while(fgets(ligne_courante, sizeof(ligne_courante),product_file) != NULL){
        if(acc == target_line){
            fprintf(fichier_tmp, "%d %s %.1f %d %d\n",tab[acc].ref_number, tab[acc].name, tab[acc].price,tab[acc].size,(tab[acc].qte-decrement));
        }
        else{
            fprintf(fichier_tmp, "%d %s %.1f %d %d\n",tab[acc].ref_number, tab[acc].name, tab[acc].price, tab[acc].size,tab[acc].qte);
        }
        acc++;
    }   

    fclose(fichier_tmp);
    fclose(product_file);
    free(tab);

    //maintenant, on supprime le fichier source original pour renommer
    //le tmp avec le meme nom que le fichier source
               //ICI ICI ICI     
    remove("fichiers_h/produits.txt");
    rename("fichiers_h/tmp.txt", "fichiers_h/produits.txt");
}


void buyArticle(char nom[],char prenom[], int ref_number, int target_line, char articleName[]){
    //fonction pour acheter un article precis
    //fichier de sauvegarde total_price
    //fichier de produits
    FILE* total_price = fopen("fichiers_h/total_price.txt","r");
    FILE* product_file = fopen("fichiers_h/produits.txt", "r");
    if(product_file==NULL || total_price==NULL){exit(1);}

    
    float lastBuyPrice;
    fscanf(total_price,"%f", &lastBuyPrice);
    fclose(total_price); //on ferme le fichier pour le ré-ouvrir dans un autre mode de lecture
    total_price = fopen("fichiers_h/total_price.txt","w");
    if(product_file==NULL || total_price==NULL){exit(1);}

    //on creer l'adresse du fichier texte du client
    char adresse[100] = "dossier_client/";
    //on stock le nom qui est concatener 

    //sachant que le nom rentré est deja en .txt
    char tmp_prenom[100];strcpy(tmp_prenom, prenom);
    char tmp_nom[100];strcpy(tmp_nom, nom);
    strcat(tmp_nom,".txt");
    strcat(tmp_prenom, tmp_nom);
    strcat(adresse,tmp_prenom);
    //printf("ADRESSE AVANT ACHAT : %s", adresse);
    
    //l'adresse s'obtient par la concatenation de adresse et nom
   
    //tableau de produits
    Article* tab = malloc(NBR_ARTICLE*sizeof(Article));//allocation dynamique du tableau de structure en fonction du nombre d'article (n)
    if(tab==NULL || NBR_ARTICLE<=0){printf("\nerrorTab");exit(2);}//verif
    //on a maintenant recuperer tout dans leref_number, isIn+1 tableau      
            //car premiere ligne ne compte pas
    for(int i = 0; i<NBR_ARTICLE;i++){
        fscanf(product_file, "%d %s %f %d %d", &tab[i].ref_number, tab[i].name, &tab[i].price,&tab[i].size, &tab[i].qte);
    }//on a bien recuperer les produits (deja testé)
    fclose(product_file);

    //on ajoute le prix de l'objet
    for(int k=0; k<NBR_ARTICLE;k++){
        if(ref_number == tab[k].ref_number){
            //on enleve une quantité dans le fichier des produits
            decrementArticleQuantity(target_line, 1);
            //on met a jour le prix total d'achat dans le fichier qui permet de le stocker en temps reel
            fprintf(total_price,"%f",lastBuyPrice+tab[k].price);
            fclose(total_price);
            //on ajoute l'achat effectué dans le fichier du client
             //on ouvre le fichier du client en question
            FILE* client_file = fopen(adresse, "a");
            if(client_file == NULL){exit(1);}
            fprintf(client_file, "\n%s", tab[k].name);
            fclose(client_file);
        }
        else if(strcmp(articleName, tab[k].name) == 0){
            //on enleve une quantité dans le fichier des produits
            decrementArticleQuantity(target_line, 1);
            //on met a jour le prix total d'achat dans le fichier qui permet de le stocker en temps reel
            fprintf(total_price,"%f",lastBuyPrice+tab[k].price);
            fclose(total_price);
            //on ajoute l'achat effectué dans le fichier du client
             //on ouvre le fichier du client en question
            FILE* client_file = fopen(adresse, "a");
            if(client_file == NULL){exit(1);}
            fprintf(client_file, "\n%s", tab[k].name);
            fclose(client_file);
        }
        
    }

    

    //fclose(client_file);
     //on ferme le fichier produits
    free(tab);//on libere la memoire allouée
}

                    //nom.txt
void searchArticle(char name[], char first_name[],int n){ //n le nombre d'articles dans le magasin (nombre de ligne)
    //on creer le tableau de structures contenant tous les produits du .txt
    Article* tab = malloc(n*sizeof(Article));//allocation dynamique du tableau de structure en fonction du nombre d'article (n)
    if(tab==NULL || n<=0){printf("\nerrorTab");exit(2);}//Verif
    FILE* product_file = fopen("fichiers_h/produits.txt", "r");
    FILE* total_price = fopen("fichiers_h/total_price.txt","r");
    if(product_file==NULL || total_price == NULL){printf("\nerrorFile");exit(1);}//Verif
            
    //on a maintenant recuperer tout dans le tableau      
            //car premiere ligne ne compte pas
    for(int i = 0; i<n;i++){
        fscanf(product_file, "%d %s %f %d %d", &tab[i].ref_number, tab[i].name, &tab[i].price,&tab[i].size, &tab[i].qte);
    }
    //printf("\nle prix du premier produit est <%f>",tab[1].price);
    //printf("\ntous les numeros de reference : ");
    fclose(product_file);
    

    //on a maintenant recuperer les donnees
    //des produits dans tout dans le tableau
    int number;
    //partie recherche - variables utilitaires
    int wantDelAccount = 0;
    int isIn = 0;
    int search_mode = 0;
    int wantToBuy = 0;
    int index = 0;
    //3 modes de recherche
    char articleName[32];
    char articleCat[32];
    int ref_number = 0;

    int error_gestion = 0;

    //achat du client
    do{
        error_gestion = 0;
        printf("\n\n      ------Recherche un produit par------ \n\n1).  Référence\n2).  Nom\n3).  Finir mes achats\n     ->");
        //on fait la verification du scanf si c'est pas un entier qui est rentré
        if(scanf("%d", &search_mode) != 1){scanf("%*[^\n]");scanf("%*c");error_gestion = -1;couleur("31");printf("\nInvalid input ->Please enter a correct number\n");couleur("0");}
        if(search_mode != 1 && search_mode != 2 && search_mode != 3){error_gestion = -1;}
    }while(error_gestion == -1);
    int j = 0;

    switch(search_mode){
        case 1:
            //par numero de reference
            do{  
                //par numero de reference
                error_gestion = 0;isIn = 0;
                printf("\nrentrez ici un numero de référence : ");
                //verification du scanf
                if(scanf("%d", &ref_number) != 1){scanf("%*[^\n]");scanf("%*c");error_gestion = -1;couleur("31");printf("\nInvalid input ->Please enter a correct number\n");couleur("0");}
                //on verifie qu'il est bien dans la liste
                if(error_gestion == 0){
                    for(j = 0; j<NBR_ARTICLE;j++){
                        if(ref_number == tab[j].ref_number){
                            //printf("\nle produit existe bien");
                            index = j;//on a récuperéla ligne du produit car ligneProduit = j+1
                            isIn = 1; //donc le produit existee
                            if(tab[j].qte == 0){
                                printf("\nnous sommes désolé mais nous n'avons plus ce produit en stock...");
                                isIn = -1;
                            }
                        }
                    }
                }
                if(isIn !=1 && isIn != -1){error_gestion = -1;}

            }while(error_gestion == -1);

                //si l'article n'est plus disponible                
                if(isIn == -1){
                    do{
                        //demande de desincription
                        error_gestion = 0;
                        printf("\nVoulez vous ? \n1)Vous désinscrire\n2)Continuez mes achats\n->");
                        if(scanf("%d", &wantDelAccount) != 1){scanf("%*[^\n]");scanf("%*c");error_gestion = -1;couleur("31");printf("\nInvalid input ->Please enter a correct number\n");couleur("0");}
                        if(wantDelAccount != 1 && wantDelAccount != 2){error_gestion = -1;}
                    }while(error_gestion == -1);
                   
                    if(wantDelAccount == 1){
                        //on desinscris la personne
                        //removeAccount(name, first_name);
                        removeAccount(name, first_name);
                        removeFromClientList(name, first_name);
                        printf("\nProcedure de desincription en cours...");
                        exit(0);
                    }       
                    else if(wantDelAccount == 2){
                        //on continue la recherche normale
                        printf("\nTrès bien, on continue la recherche :)");
                        searchArticle(name, first_name,NBR_ARTICLE);//on se remet dans la recherche
                    }
            }
            
            //on affiche le descriptif
            displayArticle(ref_number,"none",tab,index);
            //sinon on continue tout va bien :)
                do{//on demande si il veut acheter le produit
                error_gestion = 0;
                printf("\nVoulez vous acheter ce produit ?\n1) Oui \n0)Non\n   ->");
                if(scanf("%d", &wantToBuy) != 1){scanf("%*[^\n]");scanf("%*c");error_gestion = -1;couleur("31");printf("\nInvalid input ->Please enter a correct number\n");couleur("0");}
                if(wantToBuy != 1 && wantToBuy != 0){error_gestion = -1;}
                }while(error_gestion == -1);

                if(wantToBuy==1){
                    //passage achat
                    buyArticle(name, first_name, ref_number, index, "none");
                }
                //on continue de chercher
                searchArticle(name, first_name,NBR_ARTICLE);
 
            break;
        
        
        
        
        
        
        case 2:
            //par nom de produit
            isIn = 0;
            do{ //demander de rentrer le nom du produit
                //par numero de reference
                printf("\nrentrez ici le nom du produit ");
                scanf("%s", articleName);
                //on verifie qu'il est bien dans la liste
                for(j = 0; j<n;j++){
                    if(strcmp(articleName,tab[j].name) == 0){
                    index =j;
                    isIn = 1;
                    if(tab[j].qte == 0){
                            printf("\nnous sommes désolé mais nous n'avons plus ce produit en stock...");
                            isIn = -1;
                            break;
                        } 
                    }
                }
            }while(isIn==0);
            //si l'article n'est plus disponible
            if(isIn == -1){//desinscription ask
                do{
                    //demande de desincription
                    error_gestion = 0;
                    printf("\nVoulez vous ? \n1)Vous désinscrire\n2)Continuez mes achats\n->");
                    if(scanf("%d", &wantDelAccount) != 1){scanf("%*[^\n]");scanf("%*c");error_gestion = -1;couleur("31");printf("\nInvalid input ->Please enter a correct number\n");couleur("0");}
                    if(wantDelAccount != 1 && wantDelAccount != 2){error_gestion = -1;}
                }while(error_gestion == -1);
                   
                if(wantDelAccount == 1){
                    //on desinscris la personne
                    //removeAccount(name, first_name);
                    removeAccount(name, first_name);
                    removeFromClientList(name, first_name);
                    printf("\nProcedure de desincription en cours...");
                    exit(0);
                }       
                else if(wantDelAccount == 2){
                    //on continue la recherche normale
                    printf("\nTrès bien, on continue la recherche :)");
                    searchArticle(name, first_name,NBR_ARTICLE);//on se remet dans la recherche
                }                 
            }
            //si c'est ok on passe a la suite
            //on affiche le descriptif
            displayArticle(404,articleName,tab,index);
            
                do{//on demande si il veut acheter le produit
                    error_gestion = 0;
                    printf("\nVoulez vous acheter ce produit ?\n1) Oui \n0)Non\n   ->");
                    if(scanf("%d", &wantToBuy) != 1){scanf("%*[^\n]");scanf("%*c");error_gestion = -1;couleur("31");printf("\nInvalid input ->Please enter a correct number\n");couleur("0");}
                    if(wantToBuy != 1 && wantToBuy != 0){error_gestion = -1;}
                }while(error_gestion == -1);
                    //si il veut
                if(wantToBuy==1){
                    //passage achat
                    couleur("32");
                    printf("\nVous avez ajouté [%s] à votre panier !", tab[index].name);
                    couleur("0");
                    buyArticle(name, first_name, 404, index, articleName);
                }
                //on continue de chercher
                searchArticle(name, first_name,NBR_ARTICLE);
                scanf("%*s");
            break;
        case 3:
            printf("\nFIN DES ACHATS");

            FILE* total_price = fopen("fichiers_h/total_price.txt","r");
            if(total_price == NULL){exit(1);}
            float lastBuyPrice;
            fscanf(total_price,"%f", &lastBuyPrice);
            fclose(total_price);
            printf("\nTrès bien, le prix final de vos achats est de %.1f€",lastBuyPrice);
            paiement();
            exit(0);
            break;

    //on libere la memoire
    free(tab);
    }
}

