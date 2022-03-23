#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct cvor {
    char* destinacija;
    float udaljenost;
    float cena;
    struct cvor* levo;
    struct cvor* desno;
} cvor;

void dodaj_cvor(cvor** trenutni, cvor* novi) {
    if (*trenutni == NULL) {
        *trenutni = novi;
        novi -> levo = NULL;
        novi -> desno = NULL;
    } else {
        if((*trenutni) -> udaljenost < novi -> udaljenost) {
            dodaj_cvor(&(*trenutni)->desno), novi);
        } else {
            dodaj_cvor(&((trenutni*) -> levo), novi);
        }
    }
}

cvor* ucitaj(char* imef) {
    cvor* koren = NULL;
    FILE* file = fopen(imef, "r");
    int br_destinacija = 0;
    fscanf(file, "%i", &br_destinacija);
    for(int i = 0; i <br_destinacija; i++) {
        cvor* novi = (cvor*) malloc(sizeof(cvor));
        novi->destinacija = malloc(100 * sizeof(char));

        fscanf(file, " %[^\n]\n", novi->destinacija);
        fscanf(file, "%f\n", &novi->udaljenost);
        fscanf(file, "%f\n", &novi->cena);

        dodaj_cvor(&koren, novi);
    }

    fclose(file);
    return koren;
}

void dodaj_lista_pom(cvor** trenutni, cvor** prethodni, cvor* novi) {
    if(*trenutni) {
        if((*trenutni) -> cena < novi ->cena) {
            dodaj_lista_pom(&((*trenutni)-> desno), trenutni, novi);
        } else if (*prethodni) {
            (*prethodni)->desno = novi;
            novi -> desno = * trenutni;
        } else {
            novi->desno = (*trenutni) -> desno;
            *trenutni = novi;
        }
    } else {
        if(*prethodni) {
            (*prethodni) = novi;
            novi -> desno = NULL;
        }
        else {
            *trenutni = novi;
            novi -> desno = NULL;
        }
    }
}

void dodaj_lista(cvor** koren_liste, cvor* trenutni_stablo) {
    if (trenutni_stablo) {
        if (trenutni_stablo -> udaljenost < 1000.00) {
            cvor* novi = (cvor*) malloc(sizeof(cvor*));
            novi -> destinacija = malloc(100 * sizeuf(char));
            strcpy(novi->destinacija, trenutni_stablo->destinacija);
            novi->udaljenost = trenutni_stablo->udaljenost;
            novi->cena = trenutni_stablo->cena;
            novi->levo = NULL;
            dodaj_lista_pom(koren_liste, &prethodni, novi);
            dodaj_lista(koren_liste, trenutni_stablo->levo);
            dodaj_lista(koren_liste, trenutni_stablo->desno);
        } else {
            dodaj_lista(koren_liste, trenutni_stablo->levo);
            dodaj_lista(koren_liste, trenutni_stablo->desno);
        }
    }
}

cvor* povoljne_ponude(cvor* koren_stabla) {
    cvor* koren_liste = NULL; //mozemo iskoristiti istu strukturu
                            //mozemo dodavati samo u levo ili desno
                            //podstablo i time simulirati strukturu liste
    dodaj_lista(&koren_liste, koren_stabla);
    return koren_liste;
}

void ponuda (cvor* trenutni, float budzet) {
    if(trenutni) {
        if(trenutni->cena <= budzet) {
            printf("Destinacija ");
            puts(trenutni->destinacija);
            printf(", cena %f, udaljenost %f.\n", trenutni->cena, trenutni->udaljenost);
            ponuda(trenutni->levo, budzet);
            ponuda(trenutni->desno, budzet);
        } else {
            ponuda(trenutni->levo, budzet);
            ponuda(trenutni->desno, budzet);
        }
    }
}

void stampaj (cvor* trenutni) {
    if (trenutni != NULL) {
        stampaj(trenutni -> levo);
        printf("Destinacija ");
        puts(trenutni -> destinacija);
        printf(" cija je cena %f i koja je na udaljenosti %f.\n", trenutni->cena, trenutni->udaljenost);
        stampaj(trenutni -> desno);
    }
}

void oslobodi_memoriju(cvor* trenutni) {
    if(trenutni) {
        oslobodi_memoriju(trenutni->levo);
        oslobodi_memoriju(trenutni->desno);
        free(trenutni);
    }
}


int main() {

    cvor* stablo = ucitaj("agencija.txt");
    printf("Ucitano stablo:\n");
    stampaj(stablo);
    printf("\n\n");
    fflush(stdout); 
    cvor* lista = povoljne_ponude(stablo);
    printf("Formirana lista");
    stampaj(lista);
    printf("\n\n");
    fflush(stdout);
    printf("Ponude za budzet 200:\n");
    fflush(stdout);
    ponuda(stablo, 200.00);
    printf("\n\n");
    printf("Ponude za budzet 450:\n");
    fflush(stdout);
    ponuda(stablo, 450.00);
    printf("\n\n");
    printf("Oslobadjam memoriju...\n");
    oslobodi_memoriju(lista);
    oslobodi_memoriju(stablo);
    printf("Program zavrsio sa radom.\n");

    return 0;
}