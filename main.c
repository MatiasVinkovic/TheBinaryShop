#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define couleur(param) printf("\033[%sm",param)

#define Shop 300
#define nbarticles 7


#include "fichiers_h/accountGestionClient.h"
#include "fichiers_h/lastBuysDisplay.h"
#include "fichiers_h/buying_phase.h"



/*
    exit(0) -> exit normal voulu

*/

Article* creationtableau(int N){
  int i=0;
  FILE *products=NULL;
  products=fopen("fichiers_h/produits.txt","r");
if(products==NULL){
  exit(2);
}
  Article* tab=NULL;
  if(N<=0){
    exit(10);
  }
  tab=malloc(N*(sizeof(Article)));
  if(tab==NULL){
    exit(11);
  }
  for( i=0;i<N;i++){
fscanf(products,"%d %s %f %d %d", &tab[i].ref_number, tab[i].name, &tab[i].price,&tab[i].size, &tab[i].qte);

}

fclose(products);
 return tab;
}

void quantitiessort(Article* tab, int N){
  if(tab == NULL || N <= 0){
        exit(50);
    }
    for(int i=0;i<N-1;i++){
        int indexMin = i;
        for(int j=i+1;j<N;j++){
            if(tab[j].qte < tab[indexMin].qte){
                Article tmp = tab[indexMin];
                tab[indexMin] = tab[j];
                tab[j] = tmp;
            }
        }
    }

}

void numsort(Article* tab, int N){
  if(tab == NULL || N <= 0){
        exit(50);
    }
    for(int i=0;i<N-1;i++){
        int indexMin = i;
        for(int j=i+1;j<N;j++){
            if(tab[j].ref_number < tab[indexMin].ref_number){
                Article tmp = tab[indexMin];
                tab[indexMin] = tab[j];
                tab[j] = tmp;
            }
        }
    }

}

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

int numorname(){
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

int searcharticle(Article* tab, int N, char name[32], int L){
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


void displaysearchedarticle(Article* tab, int N, char name[6], int L){
  if(tab == NULL || N <= 0){
        exit(72);
    }
  int i;
  if(L==0){
  for(i=0;i<N;i++){
    if(strcmp(name,tab[i].name)==0){
      printf("Nous avons trouve l'article ! \n nom : %s \n numero de reference : %03d \n prix : %f \n quantite : %d \n taille : %d \n",tab[i].name,tab[i].ref_number,tab[i].price,tab[i].qte,tab[i].size);
    }

  }
  }
  else if(strcmp(name,"")==0){
    for(i=0;i<N;i++){
      if(L==tab[i].ref_number){
        printf("Nous avons trouve l'article ! \n nom : %s \n numero de reference : %03d \n prix : %f \n quantite : %d \n taille : %d \n",tab[i].name,tab[i].ref_number,tab[i].price,tab[i].qte,tab[i].size);
      }
    }
  }
  else{
    printf("Une erreur s'est produite");
    exit(20);
  }

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

int refill(Article* tab,int N, int ref_numberofref, char articlename[32],int SO){
  int i,j,l,k=0;
  FILE*Tmp=NULL;
  int A,f;
  if(tab==NULL || N<=0){
    exit(35);
  }
  do{
    printf("De combien voulez-vous augmenter le stockage ? Entrer '99' pour sortir du programme\n");
    f=scanf("%d",&A);
    while (getchar() != '\n');
    if(f!=1){
      printf("Veuillez reessayer");
      sleep(1);
    }
    if(A==99){
      printf("Passez une bonne journee !");
      exit(52);
    }
  }while(f!=1 && A<=0);
  Tmp=fopen("fichiers_h/tmp.txt","w");
  if(Tmp==NULL){
    printf("Erreur");
    exit(38);
  }
  if(strcmp(articlename,"")==0){
  
SO+=tab[ref_numberofref-1].size*A;
if(SO>Shop){
  fclose(Tmp);
  return 0;
}
else{
  tab[ref_numberofref-1].qte+=A;
}
}
else if(ref_numberofref==0){
for( j=0;j<N;j++){
  if(strcmp(articlename,tab[j].name)==0){
    SO+=tab[j].size*A;
    k=j;
  }
}
if(SO>Shop){
  fclose(Tmp);
  return 0;
}
else{
  tab[k].qte+=A;
}
}
for(i=0;i<N;i++){
  fprintf(Tmp,"%d %s %.2f %d %d\n", tab[i].ref_number, tab[i].name, tab[i].price,tab[i].size, tab[i].qte);
}

fclose(Tmp);

return 1;


}


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
        Article* tabarticles;
        int i,j,k,lowstock=5,count=0,occupiedplace=0,remainingplace=0;
        int a,b,c,d,e;
        char searchname[32]="";
        int searchref_number=0; 
        char try[10];
        int isIn = 0;
        int error_gestion = 0;


    do{
    printf("Veuillez entrer le mot de passe \n");
    scanf("%s",try);
    if(strcmp("pomme", try)!=0){
        printf("Acces refuse\n");
        sleep(1);
    }
    else{
        printf("Acces autorise\n");
        sleep(1);break;
    }
    }while(strcmp("pomme",try)!=0);

    tabarticles = creationtableau(nbarticles);

    for(k=1;k<nbarticles;k++){
        occupiedplace+=(tabarticles[k].qte*tabarticles[k].size);
    }
    remainingplace=Shop-occupiedplace;

    quantitiessort(tabarticles,nbarticles);

    for(i=0;i<nbarticles;i++){
    if(tabarticles[i].qte==0){
        printf("Le stock de %s est epuise ! \n",tabarticles[i].name);
        count++;
    }
    }
    for(j=0+count;j<lowstock+count;j++){
    printf("Il ne reste que %d de %s \n",tabarticles[j].qte,tabarticles[j].name);

    }
    printf("Il reste %d de place dans le magasin\n",remainingplace);
    sleep(1);
    numsort(tabarticles,nbarticles);
    a=questions();
    if(a==0){
    printf("Passez une bonne journée !");
    exit(26);
    }
    else{
    b=numorname();


    if(b==1){
    do{
        error_gestion = 0;isIn = 0;
        printf("Veuillez entrer le nom de l'article. 'Sortir' pour sortir du mode gestion \n");
        scanf("%s",searchname);
        
        if(error_gestion == 0){
            for(int x = 0; x<nbarticles;x++){
                if(strcmp(searchname,tabarticles[x].name) == 0){
                    isIn = -1;
                }
            }
            }
            if(isIn !=-1){error_gestion=-1;}

        if(strcmp(searchname,"Sortir")==0){
        exit(22);
        }
    }while(error_gestion==-1);

    if(searcharticle(tabarticles,nbarticles,searchname,searchref_number)==1){
    displaysearchedarticle(tabarticles,nbarticles,searchname,searchref_number);
    }
    }

    else if(b==2){
    do{
            error_gestion = 0;
            isIn = 0;
            printf("Veuillez entrer le numero de reference. '20' pour sortir du mode gestion\n");
            if(scanf("%d",&searchref_number) != 1){scanf("%*[^\n]");scanf("%*c");error_gestion=-1;}

            if(error_gestion == 0){
            for(int w = 0; w<nbarticles;w++){
                if(tabarticles[w].ref_number == searchref_number){
                    isIn = -1;
                }
            }
            }
            if(isIn !=-1){error_gestion=-1;}
            
        }while(error_gestion == -1);

        if(searcharticle(tabarticles,nbarticles,searchname,searchref_number)==1){
        displaysearchedarticle(tabarticles,nbarticles,searchname,searchref_number);
        }
        }
        else if(b==0){
        printf("Passez une bonne journee\n");
        exit(25);
        }
        }
        if(question2()==0){
        printf("Passez une bonne journee !\n");
        exit(51);
        }
        else{
        do{
            c=refill(tabarticles,nbarticles,searchref_number,searchname,occupiedplace);
        if(c==0){
            printf("Restockage impossible. Il n'y a pas assez de place dans le magasin\n");
        }
        }while(c!=1);
        if(c==1){
        printf("Le restockage s'est bien passe. Passez une bonne journee !\n");
        }
        }
        free(tabarticles);
        remove("fichiers_h/produits.txt");
        rename("fichiers_h/tmp.txt", "fichiers_h/produits.txt");

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