#include<string.h>
#include <stdio.h>
#include<stdlib.h>
#include"wczytaj.h"
#include"tekst.h"
int otwarcia = 0;
char *wczytaj(char * tab, int ile) {
	char *wynik;
	char *tutaj;
	wynik = fgets(tab, ile, stdin);
	if (wynik) {
		tutaj = strchr(tab, '\n');
		if (tutaj)
			*tutaj = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return wynik;
}
int wczytaj_plik_() {

}
int wybor_menu(Szkolenie *** tab_szkolenie, int * liczba_szkolen, int * granica_szkolen, Lista*wlista, int * liczba_typow,FILE *f,char *nazwa_pliku) {
	int a=0;
	otwarcia++;
	wyswietl_menu();
	if (otwarcia==1) {
		otworz_z_pliku(tab_szkolenie, liczba_szkolen, granica_szkolen, wlista, f, liczba_typow, nazwa_pliku);
	}
	scanf("%d", &a);
	while (getchar() != '\n')
		continue;
	
	if (a) {
		
		switch (a) {
		
		case 1:
			//printf("wybrales 1\n");
			if (*liczba_szkolen == 0) {
				printf("Baza jest pusta\n");
			}
			else {
				sortuj_szkolenia(tab_szkolenie, liczba_szkolen);
				wyswietl_baze(tab_szkolenie, liczba_szkolen);
				zapisz_do_pliku(*tab_szkolenie, liczba_szkolen, granica_szkolen, wlista, f, liczba_typow, nazwa_pliku);
			}
			break;
		case 2: 
			
			if (*liczba_typow == 0) {
				printf("Aby dodac rekord dodaj najpierw typy szkolen\n");
				Dodaj_Typ(wlista, liczba_typow);

			}
			dodaj_szkolenie(tab_szkolenie, liczba_szkolen, granica_szkolen, wlista, liczba_typow);
			zapisz_do_pliku(*tab_szkolenie, liczba_szkolen, granica_szkolen, wlista, f, liczba_typow, nazwa_pliku);
			break;
	
		case 3:
			usun_wszystko(*tab_szkolenie, wlista, liczba_szkolen, liczba_typow,f,nazwa_pliku);
			break;
		case 4:
			if (*liczba_szkolen == 0) {
				fprintf(stderr, "W pliku nie ma szkolen wiec nie ma czego edytowac\n");
			}
			else {
				edytuj_szkolenie(tab_szkolenie, liczba_szkolen, granica_szkolen, wlista, liczba_typow);
				zapisz_do_pliku(*tab_szkolenie, liczba_szkolen, granica_szkolen, wlista, f, liczba_typow, nazwa_pliku);
			}
			break;
		case 5:
			if (*liczba_szkolen == 0) {
				printf("Baza jest pusta\n");
			}
			else {
				sortuj_szkolenia(tab_szkolenie, liczba_szkolen);
				zapisz_do_pliku(*tab_szkolenie, liczba_szkolen, granica_szkolen, wlista, f, liczba_typow, nazwa_pliku);
			}
		default:
			break;
		}
	}
	return a;
}
void wczytaj_liczbe(double * liczba) {
	while (scanf("%lf", liczba) != 1) {
		while (getchar() != '\n')
			continue;
		puts("Podaj liczbe calkowita dodatnia");
	}

	while (getchar() != '\n')
		continue;

}
void wczytaj_liczbe_int(int * liczba2) {
	while (scanf("%d", liczba2) != 1) {
		while (getchar() != '\n')
			continue;
		puts("Podaj liczbe calkowita dodatnia");
	}

	while (getchar() != '\n')
		continue;

}
char *wczytaj2(char * tab, int ile) {//pierwsza litera jest duza
	char *wynik;
	char *tutaj;
	wynik = fgets(tab, ile, stdin);
	if (wynik) {
		tutaj = strchr(tab, '\n');
		if (tutaj)
			*tutaj = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	tab[0] = toupper(tab[0]);
	//printf("%s", tab);
	return wynik;
}