#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct Szemely {
    char nev[31];
    int eletkor;
};

struct Szemely* foglal(int meret){
    struct Szemely* tomb =(struct Szemely*)malloc(sizeof(struct Szemely)*meret);
    return tomb;
}

void kiir(int meret, struct Szemely* tomb){
    printf("%d\n",meret);
    int i;
    for(i=0;i<meret;i++){
        printf("%s %d\n",tomb[i].nev,tomb[i].eletkor);
    }
}


int main() { 
    int meret;
    scanf("%d", &meret);
    struct Szemely* arr = foglal(meret);
    int i;
    for(i=0;i<meret;i++) {
        scanf("%s %d", arr[i].nev,&arr[i].eletkor);
    }
    kiir(meret,arr);
        
    

    return 0; 
    }
