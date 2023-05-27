#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prototype.h"


                        //nom.txt
void removeAccount(char nom[], char prenom[]){
    //fonction qui supprime le compte du client qui souhaite se desinscrire
    
    printf("\nNous sommes navré de vous voir partir %s...adieu très cher ami", prenom);

    char adresse[100] = "../dossier_client/";
    char tmp_name[100];
    char tmp_prenom[100];
    //on creer l'adresse
    strcpy(tmp_name, nom); ///pour ne pas modifier le nom en general
    strcpy(tmp_prenom, prenom); //same
    strcat(tmp_name, ".txt");  //nom = vinkovic.txt
    strcat(adresse,tmp_prenom); //chemin/vinkovic.txt
    strcat(adresse, tmp_name); //chemin/matiasvinkovic.txt

    remove(adresse);
}


void removeFromClientList(char nom[], char prenom[]){
    
    /*pour supprimer un client de la liste des clients
    nous allons procéder de la meme maniere que pour soutirer une quantité
    à un produit dans le fichier les contenant 
    */
   //on creer la chaine de caractere qu'on doit supprimer
    
    char tmp_name[100];
    char tmp_prenom[100];
    strcpy(tmp_name, nom); //pour ne pas modifier le nom en general
    //printf("\n\ntmp name vaut %s", tmp_name);
    strcpy(tmp_prenom, prenom);
    strcat(tmp_name, tmp_prenom);
    //printf("l'element a supprimer est donc %s",tmp_name);
    //fichier temporaire et fichier_source
    FILE* client_list_file = fopen("../dossier_client/liste_client.txt", "r");
    
    if(client_list_file == NULL){exit(1);}
    
    //on creer le tableau contenant tout le fichier source
    Client* client_list_array = malloc(max_client*sizeof(Client));
    if(client_list_array == NULL || max_client <= 0){exit(1);}
    
    //on remplit le tableau
    int index = 0;
    for(int k = 0; k<max_client; k++){
        fscanf(client_list_file,"%s", client_list_array[k].userID);
        if(strcmp(client_list_array[k].userID, tmp_name)==0){
            //printf("LIGNE : %d",k);
            index = k;
        }
    }

    //printf("\nle premier element est %s", client_list_array[0].userID);
    
    
    fclose(client_list_file);
    client_list_file = fopen("../dossier_client/liste_client.txt", "r");if(client_list_file==NULL){exit(1);}

    //on commence à copier  
    char ligne_courante[100];
    int acc = 0;
    FILE* fichier_tempo = fopen("../dossier_client/tempo.txt","w");
    while(fgets(ligne_courante, sizeof(ligne_courante), client_list_file) !=NULL){
        if(acc == index){
            fputs("", fichier_tempo);
            //printf("ok");
        }   
        else{
            fputs(ligne_courante, fichier_tempo);
        }
        acc++;
    }
    fclose(client_list_file);
    fclose(fichier_tempo);

    remove("../dossier_client/liste_client.txt");
    rename("../dossier_client/tempo.txt", "../dossier_client/liste_client.txt");
    
}

