#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NBR_ARTICLE 5

/*
    exit(1) => erreur ouverture de fichier
    exit(2) => erreur pointeur sur tableau

*/

//structure du produit
typedef struct Article{
    //structure complete d'un produit
    char categorie[32];
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
        return 1;
    }
}



void displayArticle(int ref_number, char product_name[], Article tab[], int index){
    printf("\n-----Produit-----");
    printf("\n Nom du produit : [%s]", tab[index].name);
    printf("\n Prix TTC : [%.1f€]", tab[index].price);
    printf("\nla quantité restante est : <%d>", tab[index].qte);
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
        fscanf(product_file, "%s %d %s %f %d %d", tab[i].categorie, &tab[i].ref_number, tab[i].name, &tab[i].price,&tab[i].size, &tab[i].qte);
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
            fprintf(fichier_tmp, "%s %d %s %.1f %d %d\n",tab[acc].categorie, tab[acc].ref_number, tab[acc].name, tab[acc].price,tab[acc].size,tab[acc].qte-decrement);
        }
        else{
            fprintf(fichier_tmp, "%s %d %s %.1f %d %d\n",tab[acc].categorie, tab[acc].ref_number, tab[acc].name, tab[acc].price, tab[acc].size,tab[acc].qte);
        }
        acc++;
    }   

    fclose(fichier_tmp);
    fclose(product_file);
    free(tab);
}



void searchArticle(int n){ //n le nombre d'articles dans le magasin (nombre de ligne)
    
    //on creer le tableau de structures contenant tous les produits du .txt
    Article* tab = malloc(n*sizeof(Article));//allocation dynamique du tableau de structure en fonction du nombre d'article (n)
    if(tab==NULL || n<=0){printf("\nerrorTab");exit(2);}//Verif
    FILE* product_file = fopen("fichiers_h/produits.txt", "r");
    if(product_file==NULL){printf("\nerrorFile");exit(1);}//Verif
            
    //on a maintenant recuperer tout dans le tableau      
            //car premiere ligne ne compte pas
    for(int i = 0; i<n;i++){
        fscanf(product_file, "%s %d %s %f %d %d", tab[i].categorie, &tab[i].ref_number, tab[i].name, &tab[i].price,&tab[i].size, &tab[i].qte);
    }
    //printf("\nle prix du premier produit est <%f>",tab[1].price);
    //printf("\ntous les numeros de reference : ");
    fclose(product_file);
    

    //on a maintenant recuperer les donnees
    //des produits dans tout dans le tableau
    int number;
    //partie recherche
    int wantDelAccount = 0;
    int isIn = 0;
    int search_mode = 0;
    int wantToBuy = 0;
    //3 modes de recherche
    char articleName[32];
    char articleCat[32];
    int ref_number = 0;
    printf("\nrecherche par \n1)référence\n2)nom\n3)categorie\n->");
    scanf("%d", &search_mode);
    int j = 0;

    switch(search_mode){
        case 1:
            //par numero de reference
            do{  
                //par numero de reference
                printf("\nrentrez ici un numero de référence : ");
                scanf("%d", &ref_number);
                //on verifie qu'il est bien dans la liste
                for(j = 0; j<n;j++){
                    if(ref_number == tab[j].ref_number){
                        if(tab[j].qte == 0){
                            printf("\nnous sommes désolé mais nous n'avons plus ce produit en stock...");
                            isIn = -1;
                            break;
                        }
                    isIn =j; //isIn prend la valeur de l'index (pour eviter de declarer une autre variable)
                    }
                    else{
                        do{
                            printf("\nVoulez vous acheter ce produit ?\n->");
                            scanf("%d", &wantToBuy);
                            if(wantToBuy==1){
                                //passage achat
                                printf("achat en cours");
                                decrementArticleQuantity(2, 2);
                            }
                            //on continue de chercher
                            searchArticle(NBR_ARTICLE);
                            scanf("%*s");
                        }while(wantToBuy!=1 ||wantToBuy!=0||verifierScanF(wantToBuy) !=1);
                    }
                    //scanf("%*s"); //pour éviter que la saisie invalide ne soit répétée indéfiniment
                }

            }while(isIn==0);
            //si c'est ok on passe a la suite
            //on affiche les infos du produit
            
            //si l'article n'est plus disponible
            if(isIn == -1){

                do{//desinscription ask
                    printf("\nvoulez vous ? \n1)vous désinscrire\n2)continuez mes achats\n->");
                    scanf("%d", &wantDelAccount);
                    if(wantDelAccount == 1){
                        //on supprime le compte tout ca
                        printf("procedure de desincription");
                    }
                    else if(wantDelAccount == 2){
                        printf("\nTrès bien, on continue la recherche :)");
                        searchArticle(NBR_ARTICLE);//on se remet dans la recherche
                    }
                    scanf("%*s"); //pour éviter que la saisie invalide ne soit répétée indéfiniment
                }while(wantDelAccount !=1 || wantDelAccount!=2 || verifierScanF(wantDelAccount) !=1);
                
            }
            else{
                displayArticle(ref_number,"none",tab,isIn);
            }
            
                    

            break;
        case 2:
            //par nom de produit
            isIn = 0;
            do{ 
                //par numero de reference
                printf("\nrentrez ici le nom du produit ");
                scanf("%s", articleName);
                //on verifie qu'il est bien dans la liste
                for(j = 0; j<n;j++){
                    if(strcmp(articleName,tab[j].name) == 0){
                    isIn =j;//isIn prend la valeur de l'index
                    if(tab[j].qte == 0){
                            printf("\nnous sommes désolé mais nous n'avons plus ce produit en stock...");
                            isIn = -1;
                            break;
                        } 
                    }
                }
            }while(isIn==0);
            //si c'est ok on passe a la suite
            //si l'article n'est plus disponible
            if(isIn == -1){//desinscription ask
                    do{
                    printf("\nvoulez vous ? \n1)vous désinscrire\n2)continuez mes achats\n->");
                    scanf("%d", &wantDelAccount);
                    if(wantDelAccount == 1){
                        //on supprime le compte tout ca
                        printf("procedure de desincription");
                    }
                    else if(wantDelAccount == 2){
                        printf("\nTrès bien, on continue la recherche :)");
                        searchArticle(NBR_ARTICLE);//on se remet dans la recherche
                    }
                    scanf("%*s"); //pour éviter que la saisie invalide ne soit répétée indéfiniment
                }while(wantDelAccount !=1 || wantDelAccount!=2 || verifierScanF(wantDelAccount) !=1);
            }
            else{
                displayArticle(0,articleName,tab,isIn);
            }
            break;
        case 3:
            //par categorie de produit
            isIn = 0;
            do{ 
                //par categorie
                printf("\nrentrez ici la categorie de produit");
                scanf("%s", articleCat);
                //on verifie qu'il est bien dans la liste
                for(j = 0; j<n;j++){
                    if(strcmp(articleCat,tab[j].categorie) == 0){
                    isIn =j;//isIn prend la valeur de l'index
                     if(tab[j].qte == 0){
                            printf("\nnous sommes désolé mais nous n'avons plus ce produit en stock...");
                            isIn = -1;
                            break;
                        } 
                    }
                    else{
                        
                    }
                }
            }while(isIn==0);
            //si c'est ok on passe a la suite
            //si l'article n'est plus disponible
            if(isIn == -1){//desinscription ask
                     do{
                    printf("\nvoulez vous ? \n1)vous désinscrire\n2)continuez mes achats\n->");
                    scanf("%d", &wantDelAccount);
                    if(wantDelAccount == 1){
                        //on supprime le compte tout ca
                        printf("procedure de desincription");
                    }
                    else if(wantDelAccount == 2){
                        printf("\nTrès bien, on continue la recherche :)");
                        searchArticle(NBR_ARTICLE);//on se remet dans la recherche
                    }
                    scanf("%*s"); //pour éviter que la saisie invalide ne soit répétée indéfiniment
                }while(wantDelAccount !=1 || wantDelAccount!=2 || verifierScanF(wantDelAccount) !=1);
            }
            else{
                displayArticle(000,articleCat,tab,isIn);
            }
            break;
    }



    //on libere la memoire
    free(tab);
}

