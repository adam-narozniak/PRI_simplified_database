#ifndef STRUCT
#define STRUCT
#define DL 50
struct typ {
	char typ_szkolenia[DL];
	struct typ * next;
};
typedef struct typ Typ;

typedef Typ *Lista;

struct szkolenie {
	char nazwa[DL];
	char typ_szkolenia[DL];
	double cena;
	int czas;
	char szkoleniowiec_imie[DL];
	char szkoleniowiec_nazwisko[DL];
	int liczba_uczestnikow;
};
typedef struct szkolenie Szkolenie;
//typedef Szkolenie * Rekord;//wskaznik do Szkolenia potrzebny do tablicy
#endif