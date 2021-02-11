#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"plik.h"
#include"struct.h"
#include"obsluga_struktur.h"

char *wczytaj(char * tab, int ile);
int wybor_menu(Szkolenie *** tab_szkolenie, int * liczba_szkolen, int * granica_szkolen, Lista*wlista, int * liczba_typow,FILE *f, char*nazwa_pliku);
void wczytaj_liczbe(double * liczba);
char *wczytaj2(char * tab, int ile);
void wczytaj_liczbe_int(int * liczba2);