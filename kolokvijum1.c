#include <stdio.h>
#include <stdlib.h>
#define GRANICA 30

int duzina = 0;

void ucitaj_matricu(int* matrica, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("Unesite tezinu %d. papagaja kod %d. uzgajivaca: ", j + 1, i + 1);
            scanf("%d", &matrica[i * m + j]);
        }
    }
}

int paran(int broj) {
    return !(broj%2);
}

int neparan(int broj) {
    return broj % 2;
}

int* izdvoj(int* matrica, int n, int m, int (*funkcija) (int)) {
    duzina = 0;
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (funkcija(matrica[i * m + j])) {
                duzina++;
            }
        }
    }

    int* niz = malloc(duzina * sizeof(int));
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (funkcija(matrica[i * m + j])) {
                niz[k] = matrica[i * m +j];
                k++;
            }
        }
    }
    return niz;
}

int* izdvoj_male(int* matrica, int n, int m, int (*funkcija) (int)) {
    duzina = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (funkcija(matrica[i*m+j]) && matrica[i * m + j] < GRANICA) {
                duzina++;
            }
        }
    }

    int* niz = malloc(duzina * sizeof(int));
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (funkcija(matrica[i * m + j]) && matrica[i * m + j] < GRANICA) {
                niz[k] = matrica[i * m + j];
                k++;
            }
        }
    }
    return niz;
}

int suma(int* matrica, int n, int m, int*(*funIzdvoj) (int*, int, int, int(*) (int)), int(*funParnost) (int)) {
    int* niz = funIzdvoj(matrica, n, m, funParnost);
    int suma = 0;
    for(int i = 0; i < duzina; i++) {
        suma += niz[i];
    }
    free(niz);
    return suma;
}

int main() {
    int n, m;
    printf("Unesite broj uzgajivaca: ");
    scanf("%d", &n);
    printf("Unesite broj papagaja: ");
    scanf("%d", &m);

    int* matrica = malloc(n * m * sizeof(int));

    ucitaj_matricu(matrica, n, m);

    char c ='o';
    do {
        getchar();
        printf("Unesite m za proveru muskih, a z za proveru zenskih: ");
        scanf("%c", &c);
    } while(c != 'm' && c != 'z');

    int sumaUkupno;
    int sumaMalih;
    if (c == 'z') {
        sumaMalih = suma(matrica, n, m, izdvoj_male, paran);
        sumaUkupno = suma(matrica, n, m, izdvoj, paran);
    } else {
        sumaMalih = suma(matrica, n, m, izdvoj_male, neparan);
        sumaUkupno = suma(matrica, n, m, izdvoj, neparan);
    }

    printf("Ukupna tezina %c. papagaja je %d, dok je ", c, sumaUkupno);
    printf("Ukupna tezina svih malih %c. papagaja %d\n", c, sumaMalih);

    float procenat = (sumaUkupno / sumaMalih) * 100.0;
    printf("Ukupna tezina je %.2f posto veca od ukupno veca od tezine malih papagaja\n", procenat);

    free(matrica);
    return 0;
}
