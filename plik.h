#include<stdio.h>
#include<string.h>
#include"obsluga_struktur.h"
#include "struct.h"
char* otworz_plik(FILE **f);
int zamknij_plik(FILE **f);
void zapisz_do_pliku(Szkolenie ** tab_szkolenie, int * liczba_szkolen, int * granica_szkolen, Lista * wlista, FILE * f, int * liczba_typow, char* nazwa_pliku);
void otworz_z_pliku(Szkolenie *** tab_szkolenie, int * liczba_szkolen, int * granica_szkolen, Lista * wlista, FILE * f, int * liczba_typow, char* nazwa_pliku);
