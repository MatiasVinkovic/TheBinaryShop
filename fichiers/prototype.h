#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define couleur(param) printf("\033[%sm",param)
#define NBR_ARTICLE 5
#define ACHAT_MAX 10
#define Shop 300
#define nbarticles 7
#define max_client 30




//structure du produit
typedef struct Article{
    //structure complete d'un produit
    int ref_number;
    char name[32];
    float price;
    int size;
    int qte;
}Article;

typedef struct{
    char userID[32];
}Client;


//accountGestionClient
void viderBuffer();
int hasAccount(char nom[], char prenom[]);
void creationCompteClient(char nom[], char prenom[]);

//buying_phase
void searchArticle(char name[], char first_name[],int n); 
void buyArticle(char nom[],char prenom[], int ref_number, int target_line, char articleName[]);
void decrementArticleQuantity(int target_line, int decrement);
void displayArticle(int ref_number, char product_name[], Article tab[], int index);
int verifierScanF(int number);

//lastBuysDisplay
int lenFile(FILE* file);
void getContentLine(FILE* file, int line, char returned[]);
void displayLastBuys(char nom[], char prenom[]);

//manage articles
void displaysearchedarticle(Article* tab, int N, char name[6], int L);
int isArticleIn(Article* tab, int N, char name[32], int L);

//mange questions
int questions();
int question2();
int numOrName();

//paiement_processus
float returnTotalPrice();
void deliveryMode(float lastBuyPrice);
int getIntLen(long long number);
void paiement();

//product sort
void quantitiessort(Article* tab, int N);
void numsort(Article* tab, int N);

//unsubscribe
void removeAccount(char nom[], char prenom[]);
void removeFromClientList(char nom[], char prenom[]);


#endif