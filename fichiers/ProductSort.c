#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define couleur(param) printf("\033[%sm",param)

#include "prototype.h"



// la fonction sert à trier les articles en fonction de leur quantité
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
// la fonction trie en fonction du numéro de référence
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
