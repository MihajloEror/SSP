#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct farba{
    char naziv[50];
    float cKomp;
    float mKomp;
    float yKomp;
    float kKomp;
    struct farba* Veza;

}farba;

void dodajFarbu(farba* novi, farba** koren ){
       novi->Veza = *koren;
       *koren = novi;
}

farba* ucitaj(char* imeFajla) {

    FILE* f = fopen(imeFajla, "r");
    int br =0;
    fscanf(f,"%d\n",&br);
    farba* lista = NULL;

    for(int i=0; i<br; i++){

        farba* tekuci = (farba*) malloc(sizeof(farba));
        tekuci->Veza = NULL;
       // fgets(tekuci->naziv,50,"%s");
        fscanf(f,"%s ", tekuci->naziv);
        fscanf(f,"%f ",&tekuci->cKomp);
        fscanf(f,"%f ",&tekuci->mKomp);
        fscanf(f,"%f ",&tekuci->kKomp);
        fscanf(f,"%f ",&tekuci->yKomp);
        dodajFarbu(tekuci, &lista);
    }return lista;
    fclose(f);
}


void stampajFarbu(farba* farba) {
    if(farba!=NULL){
        printf("Naziv: %s\n", farba->naziv);
        fflush(stdout);
        printf("C komp: %.2f\n", farba->cKomp);
        fflush(stdout);
        printf("M komp: %.2f\n", farba->mKomp);
        fflush(stdout);
        printf("Y komp: %.2f\n", farba->yKomp);
        fflush(stdout);
        printf("K komp: %.2f\n", farba->kKomp);
        fflush(stdout);
        stampajFarbu(farba->Veza);
    }
}

void satroOsnovnaKorak(farba* farba, int* brOsnovnih){
    if(farba!=NULL){
        if((farba->cKomp == 100.0 && farba->mKomp==0.0 && farba->kKomp==0.0 && farba->yKomp==0.0)||(farba->mKomp == 100.0 && farba->cKomp==0.0 && farba->kKomp==0.0 && farba->yKomp==0.0)||(farba->kKomp == 100.0 && farba->mKomp==0.0 && farba->cKomp==0.0 && farba->yKomp==0.0)||(farba->yKomp == 100.0 && farba->mKomp==0.0 && farba->kKomp==0.0 && farba->cKomp==0.0) ){
            (*brOsnovnih)++;
            farba=farba->Veza;
    }satroOsnovnaKorak(farba->Veza, brOsnovnih);
    }
}

int osnovna(farba* f){

    int brOsnovna =0;

    
    satroOsnovnaKorak(f,&brOsnovna);
    
    return brOsnovna;

}

void nijansePlaveKorak(farba* farba){

    if(farba!=NULL){
        if(farba->cKomp == 100.0 && farba->mKomp ==100.0){
           printf("%s\t", farba->naziv);
            
        }
        nijansePlaveKorak(farba->Veza);
    }

}






void oslobodiMem(farba* farba){
    if(farba!=NULL){
        oslobodiMem(farba->Veza);
        free(farba);
    }
}

int main(){

    farba* lista = ucitaj("boje.txt");
    // printf("ucitao\n");
    // fflush(stdout);
    stampajFarbu(lista);
    // printf("zavrsio stampu\n");
    // fflush(stdout);

     
    printf("\nPlave nijanse su: ");
    fflush(stdout);
    nijansePlaveKorak(lista);
    printf("\n");
    fflush(stdout);
    printf("\nOsnovnih je bilo: %d",osnovna(lista));
    fflush(stdout);

    oslobodiMem(lista);
}