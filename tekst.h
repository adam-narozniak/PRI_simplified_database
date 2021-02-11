#include"struct.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"wczytaj.h"
#include"plik.h"
#include"struct.h"
#include"obsluga_struktur.h"
void powitanie(void);
void wyswietl_menu(void);
void wyswietl_typy(Lista *wlista);
void menu_typy(void);
void wyswietl_baze(Szkolenie *** tab_szkolenie, int * liczba_szkolen);
void wyswietl_pola_szkolen(void);