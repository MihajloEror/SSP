#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cvor {
    char naziv [50];
    char sifra [50];
    float prosek_ocena;
    struct cvor* levi;
    struct cvor* desni;
}cvor;

cvor* ucitaj(char* ime_fajla) {
    FILE *f = fopen(ime_fajla,"r");
    int i, broj_cvorova;
    fscanf(f, "%i\n",&broj_cvorova);
    cvor* stablo = NULL;
    for(int i=0;i<broj_cvorova;i++) {
        cvor *tek= (cvor*) malloc(sizeof(cvor));
        fgets(tek->naziv, 50, f);
        fgets(tek->sifra, 50, f);
        fscanf(f, "%f\n", &tek->prosek_ocena);
        dodaj(tek,stablo); 
    }
    return stablo;
}

void dodaj(cvor *novi, cvor **pkoren) {
    if(*pkoren == NULL) {
        *pkoren == novi;
        novi->levi=NULL;
        novi->desni=NULL;
    }
    else {
        if(novi ->prosek_ocena < (*pkoren) -> prosek_ocena)
            dodaj(novi, &(*pkoren)->levi);
        else   
            dodaj(novi, &(*pkoren)->desni);
    }
}


void stampaj_cvor(cvor *c) {
    printf("Naziv: %s, ", c->naziv);
    fflush(stdout);
    printf("sifra: %s, ", c->sifra);
    fflush(stdout);
    printf("prosecna ocena: %.2f\n", c->prosek_ocena);
    fflush(stdout);

}

void stampaj(cvor *koren){
    if (koren != NULL) {
        stampaj_cvor(koren);
		fflush(stdout);
        stampaj(koren->levi);
        stampaj(koren->desni);
    }
}

float zbir_proseka(cvor *koren, int *broj_cvorova) {
    if (koren == NULL) return 0;
    (*broj_cvorova)++;
    flaot zbir_levog = zbir_proseka(koren->levi, broj_cvorova);
    flaot zbir_desnog = zbir_proseka(koren->desni, broj_cvorova);
    return zbir_levog + zbir_desnog + koren->prosek_ocena;
}

float ukupan_prosek(cvor *koren) {
    int broj_cvorova = 0;
    float zbir = zbir_proseka(koren, &broj_cvorova);
    if (broj_cvorova == 0)
        return 0;
    else
        return zbir / broj_cvorova;
}


void iznad_proseka(cvor *koren, float prosek) {
    if(koren == NULL) return;

    if(koren->prosek_ocena > prosek) {
        stampaj_cvor(koren);
        if(koren->levi != NULL && koren->levi->prosek_ocena > prosek)
            iznad_proseka(koren->levi, prosek);
    }

    iznad_proseka(koren->desni,prosek);
}

void oslobodi_memoriju(cvor *koren) {
    if (koren != NULL) {
        oslobodi_memoriju(koren->levi);
        oslobodi_memoriju(koren->desni);
        free(koren);
    }
}


int main() {
    cvor *stablo = ucitaj("predmeti.txt");
    float prosek = ukupan_prosek(stablo);
    printf("Prosek svih predmeta zajedno je: %f.\n", prosek);
    fflush(stdout);
    printf("Predmeti iznad proseka:\n");
    fflush(stdout);
    iznad_proseka(stablo, prosek);
    printf("Svi predmeti:\n");
    fflush(stdout);
    stampaj(stablo);
    oslobodi_memoriju(stablo);
    return 0;
}