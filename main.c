#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tekst.h"
#include"wczytaj.h"
#include"plik.h"
#include"struct.h"
#include"obsluga_struktur.h"
int main(void) {
	Lista typ; //wlista w deklaracji funkcji
	FILE *f=NULL;
	Szkolenie** tab_szkolenie=NULL;
	int granica_szkolen = MIN;
	int liczba_szkolen = 0;
	int liczba_typow = 0;
	int menu;
	char*nazwa_pliku;
	powitanie();
	nazwa_pliku= otworz_plik(&f);
	inicjuj_liste_typ(&typ);
	pamiec_tablica_do_szkolen(&tab_szkolenie, &granica_szkolen);
	while (menu = wybor_menu(&tab_szkolenie, &liczba_szkolen, &granica_szkolen, &typ, &liczba_typow,f,nazwa_pliku));
	usun_pamiec_tablca_szkolen(tab_szkolenie);
	zamknij_plik(&f);
	return 0;
}