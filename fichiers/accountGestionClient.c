#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define couleur(param) printf("\033[%sm",param)

#include "prototype.h"

void viderBuffer()
{
  int c;
  while((c=getchar()) != EOF && c != '\n');
 
}

int hasAccount(char nom[], char prenom[]){
    //on veut voir si le client possede un compte ou non [renvoie 1 ou 0 respectivement]

    //on va stocker dans un tableau les donnnes du fichier liste client
    FILE* client_list_file = fopen("../dossier_client/liste_client.txt","r");
    if(client_list_file == NULL){exit(1);}
    
    Client* client_list_array = malloc(max_client*sizeof(Client));
    if(client_list_array == NULL || max_client <= 0){exit(1);}
    
    //on remplit le tableau
    for(int k = 0; k<max_client; k++){
        fscanf(client_list_file,"%s", client_list_array[k].userID);
    }
    char tmp_name[32]; //on passe par une variable temporaire car j'ai une erreur 'stack smashing'
                                                //impossible de s'en débarasser autrement
                                                //meme apres recherches
                                            
    strcpy(tmp_name, nom);
    strcat(tmp_name, prenom);
    

    for(int i = 0; i<max_client; i++){
        if(strcmp(tmp_name, client_list_array[i].userID) == 0){return 1;break;}
    }
    couleur("31");
    printf("\nVous n'avez pas de compte");couleur("0");
    free(client_list_array);
    fclose(client_list_file);
    
}

void creationCompteClient(char nom[], char prenom[]){
    //dans le cas ou le client n'a pas de compte, on lui en
    //creer un 
    
    //enregistrement du nom et prenom + concatenation
    char adresse[100] = "../dossier_client/";
    char tmp_name[100];
    
    //on stock le nom qui est concatener 
    strcpy(tmp_name, nom); //tmp_name = vinkovic
    strcat(nom, ".txt");  //nom = vinkovic.txt

    //on fait en sorte de mettre le nom du dossier avant 
    
    //on verifie si le client n'a pas deja un compte
    if(hasAccount(tmp_name, prenom)){
        printf("\nvous perdez la mémoire !");
        return ;
    }
    strcat(adresse,prenom); //chemin/vinkovic.txt
    

    //on creer la fiche client
    FILE *client_file = fopen(strcat(adresse,nom), "w");
    if (client_file == NULL) {
        printf("Erreur dans la création du fichier client.\n");
        exit(1);
    }
    printf("\nfiche client créer avec succès !");
    fprintf(client_file,"%s %s", tmp_name, prenom);
    fclose(client_file);

    //on le met sur la liste des clients
    FILE* client_list_file = fopen("../dossier_client/liste_client.txt", "a");
    if (client_list_file == NULL) {
        printf("Erreur dans l'ouverture de la liste de client.\n");
        exit(1);
    }
    fprintf(client_list_file,"\n%s%s", tmp_name, prenom);
    fclose(client_list_file);
}




