#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void viderBuffer()
{
  int c;
  while((c=getchar()) != EOF && c != '\n');
 
}

int hasAccount(char nom[], char prenom[]){

    //dans le cas ou le client a deja un compte
        // on commence par verifier si il en a vraiment un

    //on ne veut pas toucher au nom, on le preserve avec une variable temporaire
    //etant donne qu'on a un pointeur
    char tmp_name[100];
    strcpy(tmp_name, nom);
    char ligne[100];
    FILE* client_list_file = fopen("dossier_client/liste_client.txt", "r");

    //recherche si un compte existant

    strcat(tmp_name, prenom);

    //au debut je ne pouvais pas utiliser strstr avec une concatenation
    // avec strcat, j'ai fais des recherches et j'ai vu que la cause était
    // le caractere de fin de ligne ajouté par fgets, j'ai donc du supprimer
    // ce dernier caractere a l'aide d'une variable temporaire pour pouvoir faire
    // ce que je voulais
    char tmp[101];
    strcpy(tmp, tmp_name);
    tmp[strlen(tmp) -1] = '\0';

    //on regarde si 'nomprenom' est bien dans la liste
    while(fgets(ligne, sizeof(ligne), client_list_file) !=NULL){
        if(strstr(ligne,tmp) != NULL){
            printf("\n vous avez en effet un compte");
            return 1;
        }
    }
    printf("\nvous n'avez pas de compte");
    return 0;
    fclose(client_list_file);
    return 0;
}

void creationCompteClient(char nom[], char prenom[]){
    //dans le cas ou le client n'a pas de compte, on lui en
    //creer un 
    
    //enregistrement du nom et prenom + concatenation
    char adresse[100] = "dossier_client/";
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
    FILE* client_list_file = fopen("dossier_client/liste_client.txt", "a");
    if (client_list_file == NULL) {
        printf("Erreur dans l'ouverture de la liste de client.\n");
        exit(1);
    }
    fprintf(client_list_file,"\n%s%s", tmp_name, prenom);
    fclose(client_list_file);
}




