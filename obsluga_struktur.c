#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"tekst.h"
#include"wczytaj.h"
#include"plik.h"
#include"struct.h"
#include"obsluga_struktur.h"

void inicjuj_liste_typ(Lista *wlista) {
	*wlista = NULL;
}
int PelnaLista(const Lista *wlista) {
	Typ * wsk;
	int full;
	wsk = (Typ*)malloc(sizeof(Typ));
	if (wsk == NULL)
		full = 1;
	else
		full = 0;
	free(wsk);
	return full;

}
int Dodaj_Typ(Lista *wlista, int * liczba_typow) {
	char typ_szkolenia[DL];
	/*char c;
	c = getchar();
	if (c != '\n') {
		ungetc(c,stdin);
	}*/
	Typ* typ_nowy;
	Typ *szuk = *wlista;
	puts("Podaj typ");
	while (wczytaj2(typ_szkolenia, DL) != NULL && typ_szkolenia[0] != '\0') {
		if (Dodaj_Typ_Pamiec(typ_szkolenia, wlista) == 0) {
			fprintf(stderr, "Blad alokacji pamieci\n");
			break;
		}
		(*liczba_typow)++;
		puts("Podaj typ (aby zakonczyc wcisnij ENTER)");
	}

}
int Dodaj_Typ_Pamiec(char *typ_szkolenia, Lista *wlista) {//przydzielanie pamieci oraz przepinanie adresow
	Typ * n_typ; //nowe pole
	Typ * szuk = *wlista;
	n_typ = (Typ*)malloc(sizeof(Typ));
	if (n_typ == NULL) {
		return 0;
	}
	strcpy(n_typ->typ_szkolenia, typ_szkolenia);
	n_typ->next = NULL;
	if (szuk == NULL)
		*wlista = n_typ;
	else {
		while (szuk->next != NULL)
			szuk = szuk->next;
		szuk->next = n_typ;
	}
	return 1;
}
int Usun_Typ(Lista *wlista, int *liczba_typow) {
	puts("Podaj numer ktory chesz usunan");
	int numer;
	while ((scanf("%d", &numer) != 1) || numer > *liczba_typow) {
		while (getchar() != '\n')
			continue;
		printf("Podaj liczbe calkowita nie wieksza od %d\n", *liczba_typow);
	}
	numer = numer - 1;
	Typ *n_typ, *usun;
	Typ *szuk = *wlista;

	if (numer == 0) {

		*wlista = (*wlista)->next;
	}
	if (numer == 1) {//powtorzenie
		szuk = *wlista;
	}
	int i;
	for (i = 1; i < numer; i++) {
		szuk = szuk->next;
	}
	usun = szuk->next;
	szuk->next = usun->next;
	free(usun);

	(*liczba_typow)--;
}
int Edytuj_Typy(Lista *wlista, int *liczba_typow) {
	char typ_szkolenia[DL];
	puts("Podaj numer ktory chesz edytowac");
	int numer;
	while ((scanf("%d", &numer) != 1) || numer > *liczba_typow) {
		while (getchar() != '\n')
			continue;
		printf("Podaj liczbe calkowita nie wieksza od %d\n", *liczba_typow);
	}
	while (getchar() != '\n')
		continue;
	numer = numer - 1;
	puts("Podaj nowa nazwe");
	wczytaj(typ_szkolenia, DL);
	Typ *szuk = *wlista;
	if (numer == 0) {

		szuk = *wlista;
	}
	int i;
	for (i = 1; i <= numer; i++) {
		szuk = szuk->next;
	}
	typ_szkolenia[0] = toupper(typ_szkolenia[0]);
	char*spr = strcpy(szuk->typ_szkolenia, typ_szkolenia);
	if (spr == NULL) {
		fprintf(stderr, "Blad alokacji pamieci\n");
		exit(0);

	}


}
Szkolenie** pamiec_tablica_do_szkolen(Szkolenie *** tab_szkolenie, int *granica_szkolen) {
	if ((*tab_szkolenie) == NULL) {
		if (((*tab_szkolenie) = (Szkolenie **)malloc(MIN * sizeof(Szkolenie*))) == NULL) {
			fprintf(stderr, "Blad przydzielenia pamieci dla tablicy wskaznikow\n");
			exit(0);
		}
	}
	else {
		(*granica_szkolen) = 2 * (*granica_szkolen);
		if ((*tab_szkolenie = (Szkolenie**)realloc(*tab_szkolenie, (*granica_szkolen) * sizeof(Szkolenie*))) == NULL) {
			fprintf(stderr, "Blad przydzielenia pamieci dla tablicy wskaznikow\n");
			exit(0);
		}
	}
	return *tab_szkolenie;
}
Szkolenie ** dodaj_szkolenie(Szkolenie *** tab_szkolenie, int * liczba_szkolen, int * granica_szkolen, Lista*wlista, int *liczba_typow) {
	Szkolenie * szkolenie;
	if ((szkolenie = (Szkolenie *)malloc(sizeof(Szkolenie))) == NULL) {
		fprintf(stderr, "Blad przydzielenia pamieci dla (rekorudu)szkolenia\n");
		exit(0);
	}
	wypelnij_szkolenie(&szkolenie, wlista, liczba_typow);
	(*liczba_szkolen)++;
	//printf("liczba szkolen %d\n", *liczba_szkolen);
	if (*liczba_szkolen > *granica_szkolen) {
		(*tab_szkolenie) = pamiec_tablica_do_szkolen(tab_szkolenie, granica_szkolen);
	}
	(*tab_szkolenie)[*liczba_szkolen - 1] = szkolenie;
	//printf("%lf\n", (*tab_szkolenie)[0]->cena);
	return *tab_szkolenie;
}
void wypelnij_szkolenie(Szkolenie ** szkolenie, Lista *wlista, int * liczba_typow) {
	char temp[DL];
	double liczba;
	int liczba2;
	puts("Podaj nazwe szkolenia");
	if (wczytaj2(temp, DL) == NULL) {
		fprintf(stderr, "Blad przy zapisie\n");
	}
	strcpy((*szkolenie)->nazwa, temp);
	puts("Wybierz typ szkolenia");
	wybierz_typ(szkolenie, wlista, liczba_typow);

	puts("Podaj cene szkolenia");
	wczytaj_liczbe(&liczba);
	(*szkolenie)->cena = liczba;
	puts("Podaj czas szkolenia(w minutach)");
	wczytaj_liczbe_int(&liczba2);
	(*szkolenie)->czas = liczba2;
	puts("Podaj imie szkoleniowca");
	if (wczytaj2(temp, DL) == NULL) {
		fprintf(stderr, "Blad przy zapisie\n");
	}
	strcpy((*szkolenie)->szkoleniowiec_imie, temp);
	puts("Podaj nazwisko szkoleniowca");
	if (wczytaj2(temp, DL) == NULL) {
		fprintf(stderr, "Blad przy zapisie\n");
	}
	strcpy((*szkolenie)->szkoleniowiec_nazwisko, temp);
	puts("Podaj liczbe uczestnikow");
	wczytaj_liczbe_int(&liczba2);
	(*szkolenie)->liczba_uczestnikow = liczba2;
}
int wybierz_typ(Szkolenie ** szkolenie, Lista *wlista, int *liczba_typow) {
	int wybor = 0;

	while (wybor != 1) {
		wyswietl_typy(wlista);
		menu_typy();
		while ((scanf("%d", &wybor) != 1) && wybor < 5) {
			puts("Podaj liczbe calkowita dodatnia");
			while (getchar() != '\n')
				continue;
		}
		while (getchar() != '\n')
			continue;
		switch (wybor) {
		case 1:
			printf("Podaj typ szkolenia\n");
			int numer;
			while ((scanf("%d", &numer) != 1) || numer > *liczba_typow) {
				while (getchar() != '\n')
					continue;
				printf("Podaj liczbe calkowita nie wieksza od %d\n", *liczba_typow);
			}

			numer = numer - 1;
			Typ *szuk = *wlista;
			Typ *wybor;
			if (numer == 0) {

			}
			int i;
			for (i = 1; i < numer; i++) {
				szuk = szuk->next;
			}
			wybor = szuk->next;
			strcpy((*szkolenie)->typ_szkolenia, wybor->typ_szkolenia);


			break;
		case 2:
			Dodaj_Typ(wlista, liczba_typow);
			break;
		case 3:
			Edytuj_Typy(wlista, liczba_typow);
			break;
		case 4:
			Usun_Typ(wlista, liczba_typow);
			break;

		}
	}
	return wybor;
}
int sortuj_szkolenia(Szkolenie *** tab_szkolenie, int * liczba_szkolen) {
	int liczba, rosnacy;
	printf("Podaj pole wzgledem ktorego chcesz sortowac baze danych\n");
	wyswietl_pola_szkolen();
	while (scanf("%d", &liczba) != 1 || liczba > 7 || liczba < 0) {
		printf("Podaj liczbe dodatnia nie wieksza niz 7\n");
		while (getchar() != '\n')
			continue;
	}
	if (liczba != 0) {
		printf("Podaj typ sortowania\n1)roznaco\n2)malejaco\n");
		while (scanf("%d", &rosnacy) != 1 || rosnacy > 2 || rosnacy < 1) {
			printf("Podaj liczbe dodatnia nie wieksza niz 2\n");
			while (getchar() != '\n')
				continue;
		}
	}
	int i, j, i_min;
	Szkolenie *szkolenie;
	switch (liczba) {
	case 0:
		break;
	case 1:
		if (rosnacy == 1) {
			for (i = 0; i < *liczba_szkolen - 1; i++) {
				i_min = i;
				for (j = i + 1; j < *liczba_szkolen; j++) {
					if (strcmp((*tab_szkolenie)[i]->nazwa, (*tab_szkolenie)[j]->nazwa) > 0) {
						i_min = j;
					}
					szkolenie = (*tab_szkolenie)[i];
					(*tab_szkolenie)[i] = (*tab_szkolenie)[i_min];
					(*tab_szkolenie)[i_min] = szkolenie;
				}
			}
		}
		else {
			for (i = 0; i < *liczba_szkolen - 1; i++) {
				i_min = i;
				for (j = i + 1; j < *liczba_szkolen; j++) {
					if (strcmp((*tab_szkolenie)[i]->nazwa, (*tab_szkolenie)[j]->nazwa) < 0) {
						i_min = j;
					}
					szkolenie = (*tab_szkolenie)[i];
					(*tab_szkolenie)[i] = (*tab_szkolenie)[i_min];
					(*tab_szkolenie)[i_min] = szkolenie;
				}
			}

		}
		break;
	case 2:
		if (rosnacy == 1) {
			for (i = 0; i < *liczba_szkolen - 1; i++) {
				i_min = i;
				for (j = i + 1; j < *liczba_szkolen; j++) {
					if (strcmp((*tab_szkolenie)[i]->typ_szkolenia, (*tab_szkolenie)[j]->typ_szkolenia) > 0) {
						i_min = j;
					}
					szkolenie = (*tab_szkolenie)[i];
					(*tab_szkolenie)[i] = (*tab_szkolenie)[i_min];
					(*tab_szkolenie)[i_min] = szkolenie;
				}
			}
		}
		else {
			for (i = 0; i < *liczba_szkolen - 1; i++) {
				i_min = i;
				for (j = i + 1; j < *liczba_szkolen; j++) {
					if (strcmp((*tab_szkolenie)[i]->typ_szkolenia, (*tab_szkolenie)[j]->typ_szkolenia) < 0) {
						i_min = j;
					}
					szkolenie = (*tab_szkolenie)[i];
					(*tab_szkolenie)[i] = (*tab_szkolenie)[i_min];
					(*tab_szkolenie)[i_min] = szkolenie;
				}
			}

		}
		break;
	case 3:
		if (rosnacy == 1) {
			for (i = 0; i < *liczba_szkolen - 1; i++) {
				i_min = i;
				for (j = i + 1; j < *liczba_szkolen; j++) {
					if ((*tab_szkolenie)[i]->cena > (*tab_szkolenie)[j]->cena) {
						i_min = j;
					}
					szkolenie = (*tab_szkolenie)[i];
					(*tab_szkolenie)[i] = (*tab_szkolenie)[i_min];
					(*tab_szkolenie)[i_min] = szkolenie;
				}
			}
		}
		else {
			for (i = 0; i < *liczba_szkolen - 1; i++) {
				i_min = i;
				for (j = i + 1; j < *liczba_szkolen; j++) {
					if ((*tab_szkolenie)[i]->cena < (*tab_szkolenie)[j]->cena) {
						i_min = j;
					}
					szkolenie = (*tab_szkolenie)[i];
					(*tab_szkolenie)[i] = (*tab_szkolenie)[i_min];
					(*tab_szkolenie)[i_min] = szkolenie;
				}
			}

		}
	case 4:
		if (rosnacy == 1) {
			for (i = 0; i < *liczba_szkolen - 1; i++) {
				i_min = i;
				for (j = i + 1; j < *liczba_szkolen; j++) {
					if ((*tab_szkolenie)[i]->czas > (*tab_szkolenie)[j]->czas) {
						i_min = j;
					}
					szkolenie = (*tab_szkolenie)[i];
					(*tab_szkolenie)[i] = (*tab_szkolenie)[i_min];
					(*tab_szkolenie)[i_min] = szkolenie;
				}
			}
		}
		else {
			for (i = 0; i < *liczba_szkolen - 1; i++) {
				i_min = i;
				for (j = i + 1; j < *liczba_szkolen; j++) {
					if ((*tab_szkolenie)[i]->czas < (*tab_szkolenie)[j]->czas) {
						i_min = j;
					}
					szkolenie = (*tab_szkolenie)[i];
					(*tab_szkolenie)[i] = (*tab_szkolenie)[i_min];
					(*tab_szkolenie)[i_min] = szkolenie;
				}
			}

		}
	case 5:
		if (rosnacy == 1) {
			for (i = 0; i < *liczba_szkolen - 1; i++) {
				i_min = i;
				for (j = i + 1; j < *liczba_szkolen; j++) {
					if (strcmp((*tab_szkolenie)[i]->szkoleniowiec_imie, (*tab_szkolenie)[j]->szkoleniowiec_imie) > 0) {
						i_min = j;
					}
					szkolenie = (*tab_szkolenie)[i];
					(*tab_szkolenie)[i] = (*tab_szkolenie)[i_min];
					(*tab_szkolenie)[i_min] = szkolenie;
				}
			}
		}
		else {
			for (i = 0; i < *liczba_szkolen - 1; i++) {
				i_min = i;
				for (j = i + 1; j < *liczba_szkolen; j++) {
					if (strcmp((*tab_szkolenie)[i]->szkoleniowiec_imie, (*tab_szkolenie)[j]->szkoleniowiec_imie) < 0) {
						i_min = j;
					}
					szkolenie = (*tab_szkolenie)[i];
					(*tab_szkolenie)[i] = (*tab_szkolenie)[i_min];
					(*tab_szkolenie)[i_min] = szkolenie;
				}
			}

		}
		break;

	case 6:
		if (rosnacy == 1) {
			for (i = 0; i < *liczba_szkolen - 1; i++) {
				i_min = i;
				for (j = i + 1; j < *liczba_szkolen; j++) {
					if (strcmp((*tab_szkolenie)[i]->szkoleniowiec_nazwisko, (*tab_szkolenie)[j]->szkoleniowiec_nazwisko) > 0) {
						i_min = j;
					}
					szkolenie = (*tab_szkolenie)[i];
					(*tab_szkolenie)[i] = (*tab_szkolenie)[i_min];
					(*tab_szkolenie)[i_min] = szkolenie;
				}
			}
		}
		else {
			for (i = 0; i < *liczba_szkolen - 1; i++) {
				i_min = i;
				for (j = i + 1; j < *liczba_szkolen; j++) {
					if (strcmp((*tab_szkolenie)[i]->szkoleniowiec_nazwisko, (*tab_szkolenie)[j]->szkoleniowiec_nazwisko) < 0) {
						i_min = j;
					}
					szkolenie = (*tab_szkolenie)[i];
					(*tab_szkolenie)[i] = (*tab_szkolenie)[i_min];
					(*tab_szkolenie)[i_min] = szkolenie;
				}
			}

		}
		break;


	case 7:
		if (rosnacy == 1) {
			for (i = 0; i < *liczba_szkolen - 1; i++) {
				i_min = i;
				for (j = i + 1; j < *liczba_szkolen; j++) {
					if ((*tab_szkolenie)[i]->liczba_uczestnikow > (*tab_szkolenie)[j]->liczba_uczestnikow) {
						i_min = j;
					}
					szkolenie = (*tab_szkolenie)[i];
					(*tab_szkolenie)[i] = (*tab_szkolenie)[i_min];
					(*tab_szkolenie)[i_min] = szkolenie;
				}
			}
		}
		else {
			for (i = 0; i < *liczba_szkolen - 1; i++) {
				i_min = i;
				for (j = i + 1; j < *liczba_szkolen; j++) {
					if ((*tab_szkolenie)[i]->liczba_uczestnikow < (*tab_szkolenie)[j]->liczba_uczestnikow) {
						i_min = j;
					}
					szkolenie = (*tab_szkolenie)[i];
					(*tab_szkolenie)[i] = (*tab_szkolenie)[i_min];
					(*tab_szkolenie)[i_min] = szkolenie;
				}
			}

		}
	}
}

/*void sortowanie(Szkolenie *** tab_szkolenie, int * liczba_szkolen,int rosnacy) {

	for (i = 0; i < *liczba_szkolen-1; i++) {
		i_min = i;
		for (j = i + 1; j < *liczba_szkolen;j++) {
			//if(porownaj(tab_szkolenie,liczba_szkolen,porzadek)
			//if (strcmp((**tab_szkolenie)->nazwa,(**tab_szkolenie)->"nazwa" ));
		}
	}
}*/
void usun_wszystko(Szkolenie ** tab_szkolen, Lista *wlista, int * liczba_szkolen, int * liczba_typow, FILE *f, char* nazwa_pliku) {
	usun_pamiec_typy(wlista, liczba_typow);
	usun_pamiec_szkolenia(tab_szkolen, liczba_szkolen);
	freopen(nazwa_pliku, "w", f);
}

void usun_pamiec_szkolenia(Szkolenie ** tab_szkolen, int * liczba_szkolen) {
	if (tab_szkolen == NULL) {
		fprintf(stderr, "Operacja nie jest mozliwa\n");
		return ;
	}
	int i = 0;
	for (i = 0; i < *liczba_szkolen - 1; i++) {
		assert(tab_szkolen[i]);
		free(tab_szkolen[i]);
		tab_szkolen[i] = NULL;
	}
	*liczba_szkolen = 0;
}
void usun_pamiec_tablca_szkolen(Szkolenie ** tab_szkolen) {
	if (tab_szkolen == NULL) {
		fprintf(stderr, "Operacja nie jest mozliwa\n");
		return ;
	}
	assert(tab_szkolen);
	free(tab_szkolen);
	tab_szkolen = NULL;
}

void usun_pamiec_typy(Lista *wlista, int * liczba_typow) {
	if (*wlista == NULL) {
		fprintf(stderr, "Operacja nie jest mozliwa\n");
		return ;
	}
	Typ *temp;
	while ((*wlista) != NULL) {
		temp = *wlista;
		(*wlista) = (*wlista)->next;
		free(temp);
	}
	*wlista = NULL;
	*liczba_typow = 0;
}
void edytuj_szkolenie(Szkolenie *** tab_szkolenie, int * liczba_szkolen, int * granica_szkolen, Lista*wlista, int *liczba_typow) {
	int wybor1 = -1, wybor2 = -1;
	char temp[DL];
	double liczba;
	int liczba2;
	printf("Podaj numer szkolenia ktore chcesz edytowac\n");
	wyswietl_baze(tab_szkolenie, liczba_szkolen);
	wczytaj_liczbe_int(&wybor1);
	while (wybor1<1 || wybor1>*liczba_szkolen) {
		printf("Podaj liczbe calkowita dotania nie wieksza od %d\n", *liczba_szkolen);
		wczytaj_liczbe_int(&wybor1);
	}
	
	printf("Podaj numer pola ktory chcesz edytowac\n");
	wyswietl_pola_szkolen2();
	wczytaj_liczbe_int(&wybor2);
	while (wybor2 < 1 || wybor2>7) {
		printf("Podaj liczbe calkowita dotania nie wieksza od 7\n");
		wczytaj_liczbe_int(&wybor2);
	}
	Szkolenie *szkolenie;
	szkolenie = (*tab_szkolenie)[wybor1 - 1];
	
	
	switch (wybor2) {
	case 1:
		puts("Podaj nazwe szkolenia");
		if (wczytaj2(temp, DL) == NULL) {
			fprintf(stderr, "Blad przy zapisie\n");
		}
		strcpy((szkolenie)->nazwa, temp);
		break;

	case 2:
		puts("Podaj typ szkolenia");
		/*if (wczytaj2(temp, DL) == NULL) {
			fprintf(stderr, "Blad przy zapisie\n");
		}
		strcpy((**szkolenie)->typ_szkolenia, temp);*/
		wybierz_typ(&szkolenie, wlista, liczba_typow);
		break;

	case 3:
		puts("Podaj cene szkolenia");
		wczytaj_liczbe(&liczba);
		(szkolenie)->cena = liczba;
		break;
	case 4:
		puts("Podaj czas szkolenia(w minutach)");
		wczytaj_liczbe_int(&liczba2);
		(szkolenie)->czas = liczba2;
		break;
	case 5:
		puts("Podaj imie szkoleniowca");
		if (wczytaj2(temp, DL) == NULL) {
			fprintf(stderr, "Blad przy zapisie\n");
		}
		strcpy((szkolenie)->szkoleniowiec_imie, temp);
		break;
	case 6:
		puts("Podaj nazwisko szkoleniowca");
		if (wczytaj2(temp, DL) == NULL) {
			fprintf(stderr, "Blad przy zapisie\n");
		}
		strcpy((szkolenie)->szkoleniowiec_nazwisko, temp);
		break;
	case 7:
		puts("Podaj liczbe uczestnikow");
		wczytaj_liczbe_int(&liczba2);
		(szkolenie)->liczba_uczestnikow = liczba2;
		break;

	}
}



//wybierz_typ(szkolenie, wlista, liczba_typow);





