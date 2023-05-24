#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "prototype.h"


//GESTION DES ERREURS
/*
    exit(1) --> erreur lors de l'ouverture d'un fichier
*/

/* solutions aux erreurs :
    "double free aborted core dumped" -> ca veut dire que vous avez fermer un fichier
        deux fois sans le reouvrir entre deux, donc confusion avec le pointeur *FILE (stackoverflow)


*/
 

int lenFile(FILE* file){
    int acc = 0;
    //on compte le nombre de ligne presentes dans le fichier texte
    for(int c = getc(file); c!=EOF; c = getc(file)){
        if(c == '\n'){  //si on incremente alors on a une ligne presente
            acc++;
        }
    }

    return acc+1;//compenser le decalage
}

void getContentLine(FILE* file, int line, char returned[]){
    //fonction qui une fois que on a rentrer une ligne, va stoker dans returned
    //le contenu de celle-ci
    int acc_ligne= 0;
    char ligne_courante[100];
                                                        //gerer erreur au cas ou plus grand
    while(fgets(ligne_courante,sizeof(ligne_courante), file) != NULL ){//null si fin fichier
        acc_ligne ++;
        if(acc_ligne == line){
            strcpy(returned, ligne_courante);
        }
    } 
}

void displayLastBuys(char nom[], char prenom[]){

    //on veut afficher les trois derniers lignes du fichiers du client
    // ce qui correspond aux 3 derniers achats, ceux-ci s'accumulant
    
    //on fait une concatenation du nom et du prenom pour acceder au fichier du client
    char adresse[100] = "../dossier_client/";
    strcat(nom, ".txt"); //lehech.txt
    //on stock le nom qui est concatener 
    strcat(adresse, prenom);
    //on a donc l'adresse du fichier 
    strcpy(adresse,strcat(adresse,nom));

    //printf("\nADRESSE : %s", adresse);
    //creation et verification de l'etat du fichier + gestion erreurs
    FILE* client_file = fopen(adresse, "r");
    if(client_file == NULL){
        printf("\nerreur d'ouverture fichier client 'displayLastBuys'1");
        exit(1);
    }
    int lenClientFile = lenFile(client_file);
    fclose(client_file);


    client_file = fopen(adresse, "r");
    if(client_file == NULL){
        printf("\nerreur d'ouverture fichier client 'displayLastBuys'2");
        exit(1);
    }

    char achat1[100];
    char achat2[100];
    char achat3[100];

    //printf("\nlenClientFile : %d", lenClientFile);
    
    
    
    int acc_ligne = 0;
    
    //on stock
    getContentLine(client_file, lenClientFile, achat1);
    fclose(client_file);                
    client_file = fopen(adresse, "r"); if(client_file == NULL){exit(1);}
    getContentLine(client_file, lenClientFile-1, achat2);
    fclose(client_file);
    client_file = fopen(adresse, "r");
    getContentLine(client_file, lenClientFile-2, achat3);

    switch(lenClientFile){
        case 1:
            strcpy(achat1, "pas d'achat"); //n (dernier)
            strcpy(achat2, "pas d'achat");  //n-1
            strcpy(achat3, "pas d'achat");  //n-2
            break;
        case 2:
            strcpy(achat2, "pas d'achat");  //n-1
            strcpy(achat3, "pas d'achat");  //n-2
            break;
        case 3:
            strcpy(achat3, "pas d'achat");//n-2
            break;
    }
    printf("\nVos 3 derniers achats ont été : \n-%s\n-%s\n-%s", achat1, achat2, achat3);

    fclose(client_file);

}