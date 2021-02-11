#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"plik.h"
#include"obsluga_struktur.h"
#include "struct.h"
#include <assert.h>
#define MAX_PLIK 50
char* otworz_plik(FILE **f) {
	char* i, *j;
	char *plik;
	plik = (char*)malloc(MAX_PLIK * sizeof(char));
	char txt[5] = ".txt";
	i = wczytaj(plik, MAX_PLIK - 5);
	if (i == NULL) {
		puts("Blad zczytania");
		exit(1);
	}
	if (strstr(plik, txt) == NULL) {
		j = strchr(plik, '\0');
		strcpy(j, txt);

	}
	//printf("%s", i);
	*f = fopen(i, "a+");
	if (*f == NULL) {
		fprintf(stderr, "Nie mozna otworzyc pliku\n");
		exit(1);
	}
	return plik;//zwaracam nazwe pliku
}
int zamknij_plik(FILE **f) {
	fclose(*f);
}
void zapisz_do_pliku(Szkolenie ** tab_szkolenie, int * liczba_szkolen, int * granica_szkolen, Lista * wlista, FILE * f, int * liczba_typow, char* nazwa_pliku) {
	int i;
	if (freopen(nazwa_pliku, "w", f) == NULL) {
		fprintf(stderr, "Nie mozna otworzyc pliku\n");
		exit(1);
	};
	fprintf(f, "%d %d\n", *liczba_typow, *liczba_szkolen);
	Typ *temp1 = *wlista;
	for (i = 0; temp1 != NULL; temp1 = temp1->next, i++) {
		fputs(temp1->typ_szkolenia, f);
		fputs("\n", f);
	}
	//printf()
	for (i = 0; i < *liczba_szkolen; i++) {
		//fprintf(f, "%s", tab_szkolenie[i]->nazwa);
		fputs(tab_szkolenie[i]->nazwa, f);
		fputs("\n", f);
		fputs(tab_szkolenie[i]->typ_szkolenia, f);
		fputs("\n", f);
		fprintf(f, "%lf\n", tab_szkolenie[i]->cena);
		fprintf(f, "%d\n", tab_szkolenie[i]->czas);
		fputs(tab_szkolenie[i]->szkoleniowiec_imie, f);
		fputs("\n", f);
		fputs(tab_szkolenie[i]->szkoleniowiec_nazwisko, f);
		fputs("\n", f);
		fprintf(f, "%d\n", tab_szkolenie[i]->liczba_uczestnikow);
	}
}

void otworz_z_pliku(Szkolenie *** tab_szkolenie, int * liczba_szkolen, int * granica_szkolen, Lista * wlista, FILE * f, int * liczba_typow, char* nazwa_pliku) {
	int i = 0;
	char typ_szkolenia[DL], temp[DL];
	char *spr;
	if (freopen(nazwa_pliku, "r", f) == NULL) {
		fprintf(stderr, "Nie mozna otworzyc pliku\n");
		exit(1);
	}
	rewind(f);
	if (fscanf(f, "%d %d", liczba_typow, liczba_szkolen) != 2) {
		if (feof(f)) {
			printf("W pliku nie ma danych\n");
		}
		else if (ferror(f)) {
			printf("Error\n");
		}
		else {
			fprintf(stderr, "Bledny format zapisu");
			exit(1);
		}
	}
	//printf("%d %d\n", *liczba_typow, *liczba_szkolen);
	getc(f);
	for (i = 0; i < *liczba_typow; i++) {
		//fscanf(f, "%s", typ_szkolenia);
		spr = fgets(typ_szkolenia, DL, f);
		assert(spr);
		char *tutaj = strchr(typ_szkolenia, '\n');
		if (tutaj)
			*tutaj = '\0';
		//printf("%s\n", typ_szkolenia);

		if (Dodaj_Typ_Pamiec(typ_szkolenia, wlista) == 0) {
			fprintf(stderr, "Blad alokacji pamieci\n");
			break;
		}
	}
	Szkolenie * szkolenie;
	double cena;
	int liczba;
	char *tutaj;
	for (i = 0; i < *liczba_szkolen; i++) {
		if (i >= *granica_szkolen) {
			//(*tab_szkolenie) = 
				pamiec_tablica_do_szkolen(tab_szkolenie, granica_szkolen);
		}
		if (((szkolenie) = (Szkolenie *)malloc(sizeof(Szkolenie))) == NULL) {
			fprintf(stderr, "Blad przydzielenia pamieci dla (rekorudu)szkolenia\n");
			exit(0);
		}
		//zczytanie nazwy
		spr = fgets(temp, DL, f);
		assert(spr);
		tutaj = strchr(temp, '\n');
		if (tutaj)
			*tutaj = '\0';
		strcpy((szkolenie)->nazwa, temp);
		//zczytanie typ
		spr = fgets(temp, DL, f);
		assert(spr);
		tutaj = strchr(temp, '\n');
		if (tutaj)
			*tutaj = '\0';
		strcpy((szkolenie)->typ_szkolenia, temp);
		//zczytanie cena
		/*if (fscanf(f, "%lf", &cena) == NULL) {
			fprintf(stderr, "Blad zczytania\n");
		};
		(szkolenie)->cena = cena;
		getc(f);*/
		spr = fgets(temp, DL, f);
		assert(spr);
		tutaj = strchr(temp, '\n');
		if (tutaj)
			*tutaj = '\0';
		szkolenie->cena = atof(spr);
		//zczytanie czas
		if (fscanf(f, "%d", &liczba) == NULL) {
			fprintf(stderr, "Blad zczytania\n");
		};
		(szkolenie)->czas = liczba;
		getc(f);
		//zczytanie imie 
		spr = fgets(temp, DL, f);
		assert(spr);
		tutaj = strchr(temp, '\n');
		if (tutaj)
			*tutaj = '\0';
		strcpy((szkolenie)->szkoleniowiec_imie, temp);
		//zczytanie nazwisko
		spr = fgets(temp, DL, f);
		assert(spr);
		tutaj = strchr(temp, '\n');
		if (tutaj)
			*tutaj = '\0';
		strcpy((szkolenie)->szkoleniowiec_nazwisko, temp);
		//zczytanie liczba uczestnikow
		if (fscanf(f, "%d", &liczba) == NULL) {
			fprintf(stderr, "Blad zczytania\n");
		};
		(szkolenie)->liczba_uczestnikow = liczba;
		getc(f);
		
		(*tab_szkolenie)[i] = szkolenie;
	}
}
