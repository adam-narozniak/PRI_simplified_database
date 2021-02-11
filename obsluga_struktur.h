#include"struct.h"
#define MIN 5
int Dodaj_Typ_Pamiec(char *typ_szkolenia, Lista *wlista);
int Dodaj_Typ(Lista *wlista,int* liczba_typow);
int PelnaLista(const Lista *wlista);
void inicjuj_liste_typ(Lista *wlista);
int Usun_Typ(Lista *wlista,int* liczba_typow);
int Edytuj_Typy(Lista *wlista, int *liczba_typow);
Szkolenie ** pamiec_tablica_do_szkolen(Szkolenie *** tab_szkolenie, int *liczba_szkolen);
Szkolenie ** dodaj_szkolenie(Szkolenie *** tab_szkolenie, int * liczba_szkolen, int * granica_szkolen, Lista*wlista,int * liczba_typow);
void wypelnij_szkolenie(Szkolenie ** szkolenie, Lista *wlista,int *liczba_typow);
int wybierz_typ(Szkolenie ** szkolenie, Lista *wlista, int *liczba_typow);
void usun_wszystko(Szkolenie ** szkolenie, Lista *wlista, int * liczba_szkolen, int * liczba_typow, FILE *f, char* nazwa_pliku);
int sortuj_szkolenia(Szkolenie *** tab_szkolenie, int * liczba_szkolen);
void usun_pamiec_szkolenia(Szkolenie ** tab_szkolen, int * liczba_szkolen);
void usun_pamiec_tablca_szkolen(Szkolenie ** tab_szkolen);
void usun_pamiec_typy(Lista *wlista, int * liczba_typow);
void edytuj_szkolenie(Szkolenie *** szkolenie, int * liczba_szkolen, int * granica_szkolen, Lista*wlista, int *liczba_typow);