#include<stdio.h>
#include"tekst.h"
#include"struct.h"
void powitanie(void) {
	printf("Projekt nr 3 baza danych\nDane autora:Adam Narozniak grupa srody godzina 14:15-16:00\n");
	printf("Podaj nazwe pliku na ktorym chcesz operowac,\njesli podasz nazwe ktora nie istnieje plik zostanie utworzony\n");
}
void wyswietl_menu(void) {
	printf("Podaj co chcesz zrobic\n");
	printf("%s\n%s\n%s\n%s\n%s\n%s\n", "1) Wyswietl baze(pozniej bedziesz poproszony o tryb sortowania)", "2) Dodaj rekord", "3) Czysc cala baze","4) Edytuj szkolenie","5) Sortuj baze", "Aby zakonczyc wcisnij q");
}
void wyswietl_typy(Lista *wlista) {
	int i = 0;
	Typ *temp = *wlista;
	for (i = 0; temp != NULL; temp = temp->next, i++) {
		printf("%2d) %s\n", i + 1, temp->typ_szkolenia);
	}
}
void menu_typy(void) {
	printf("%25s %25s\n%25s %25s\n", "Wcisnij 1 aby wybrac typ szkolenia ", "Wcisnij 2 aby dodac typ szkolenia ", "Wcisnij 3 aby edytkowac typ szkolenie", "Wcisnij 4 aby usunac typ szkolenia");

}
void wyswietl_baze(Szkolenie *** tab_szkolenie, int * liczba_szkolen) {
	int i;
	for (i = 0; i < *liczba_szkolen; i++) {
		printf("%d)******************************\n", i + 1);
		printf("Nazwa szkolenia: %s\n", (*tab_szkolenie)[i]->nazwa);
		printf("Typ szkolenia: %s\n", (*tab_szkolenie)[i]->typ_szkolenia);
		printf("Cena szkolenia: %.2f zl\n", (*tab_szkolenie)[i]->cena);
		printf("Czas szkolenia: %d minut\n", (*tab_szkolenie)[i]->czas);
		printf("Imie szkleniowca: %s\n", (*tab_szkolenie)[i]->szkoleniowiec_imie);
		printf("Nazwisko szkoleniowca: %s\n", (*tab_szkolenie)[i]->szkoleniowiec_nazwisko);
		printf("Liczba uczestnikow: %d\n\n", (*tab_szkolenie)[i]->liczba_uczestnikow);
	}
}
void wyswietl_pola_szkolen(void) {
	printf("0) Domyslnie\n");
	printf("1) Nazwa szkolenia\n");
	printf("2) Typ szkolenia\n");
	printf("3) Cena szkolenia\n");
	printf("4) Czas szkolenia\n");
	printf("5) Imie szkleniowca\n");
	printf("6) Nazwisko szkoleniowca\n");
	printf("7) Liczba uczestnikow\n");
}
void wyswietl_pola_szkolen2(void) {
	printf("1) Nazwa szkolenia\n");
	printf("2) Typ szkolenia\n");
	printf("3) Cena szkolenia\n");
	printf("4) Czas szkolenia\n");
	printf("5) Imie szkleniowca\n");
	printf("6) Nazwisko szkoleniowca\n");
	printf("7) Liczba uczestnikow\n");
}