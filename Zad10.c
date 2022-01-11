#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 30
struct _CvorListe;
typedef struct _CvorListe* PozicijaLista;
typedef struct _CvorListe {
	char grad[MAX];
	int populacija;
	PozicijaLista sljedeci;
} CvorListe;
struct _CvorStabla;
typedef struct _CvorStabla* PozicijaStablo;
typedef struct _CvorStabla {
	char drzava[MAX];
	PozicijaLista gradovi;
	PozicijaStablo lijevo;
	PozicijaStablo desno;
} CvorStabla;
PozicijaLista StvoriClanListe();
PozicijaStablo NadiDrzavu(PozicijaStablo, char*);
PozicijaStablo StvoriClanStabla(char*, PozicijaLista);
PozicijaStablo ProcitajDatotekuDrzava(PozicijaStablo, char*);
int DodajGradUListu(PozicijaLista, char*, int);
PozicijaStablo DodajDrzavaUStablo(char*, PozicijaLista, PozicijaStablo);
PozicijaLista ProcitajDatotekuGradovi(char*);
int PrintLista(PozicijaLista);
int InOrderPrintStablo(PozicijaStablo);
int Odaberi(PozicijaStablo);
int NadiPopulacijeGradovaVeceOdX(PozicijaLista, int);
int main() {
	//zadatak b) binarno stablo s vezanim listama
	int bzv = 0;
	PozicijaStablo headStablo = NULL;
	headStablo = ProcitajDatotekuDrzava(headStablo, "drzave.txt");
	InOrderPrintStablo(headStablo);
	Odaberi(headStablo);
	return EXIT_SUCCESS;
}
PozicijaStablo NadiDrzavu(PozicijaStablo p, char* drzava) {
	if (p == NULL) {
		return NULL;
	}
	if (strcmp(drzava, p->drzava) == 0) {
		return p;
	}
	else if (strcmp(drzava, p->drzava) > 0) {
		return NadiDrzavu(p->desno, drzava);
	}
	return NadiDrzavu(p->lijevo, drzava);
}
int Odaberi(PozicijaStablo headStablo) {
	PozicijaStablo q = NULL;
	char tmp1[MAX];
	int tmp2;
	printf("Odaberi ime drzave koju zelis pretrazivati: ");
	scanf("%s", tmp1);
	printf("Nadi sve gradove vece od x stanovnika: ");
	scanf("%d", &tmp2);
	q = NadiDrzavu(headStablo, tmp1);
	if (!q) {
		printf("Zadana drzava ne postoji!");
		return EXIT_FAILURE;
	}
	NadiPopulacijeGradovaVeceOdX(q->gradovi, tmp2);
	return EXIT_SUCCESS;
}
int NadiPopulacijeGradovaVeceOdX(PozicijaLista headLista, int populacijaX) {
	while (headLista->sljedeci != NULL) {
		if (headLista->populacija > populacijaX) {
			printf("%s %d, ", headLista->grad, headLista->populacija);
		}
		headLista = headLista->sljedeci;
	}
	return EXIT_SUCCESS;
}
int PrintLista(PozicijaLista headLista) {
	while (headLista->sljedeci != NULL) {
		printf("%s %d ", headLista->grad, headLista->populacija);
		headLista = headLista->sljedeci;
	}
	printf("\n\n");
	return EXIT_SUCCESS;
}
PozicijaLista StvoriClanListe() {
	PozicijaLista q = malloc(sizeof(CvorListe));
	if (q == NULL) {
		printf("Greska pri alociranju memorije");
		return NULL;
	}
	strcpy(q->grad, "");
	q->populacija = 0;
	q->sljedeci = NULL;
	return q;
}
PozicijaStablo StvoriClanStabla(char* drzava, PozicijaLista gradovi) {
	PozicijaStablo q = malloc(sizeof(CvorStabla));
	if (q == NULL) {
		printf("Greska pri alociranju memorije");
		return NULL;
	}
	q->gradovi = gradovi;
	strcpy(q->drzava, drzava);
	q->lijevo = NULL;
	q->desno = NULL;
	return q;
}
int InOrderPrintStablo(PozicijaStablo p) {
	if (p == NULL) {
		return EXIT_SUCCESS;
	}
	else {
		InOrderPrintStablo(p->lijevo);
		printf("%s gradovi: ", p->drzava);
		PrintLista(p->gradovi->sljedeci);
		InOrderPrintStablo(p->desno);
	}
	return EXIT_SUCCESS;
}
PozicijaStablo ProcitajDatotekuDrzava(PozicijaStablo headStablo, char* imeDat) {
	PozicijaLista gradovi = NULL;
	char imeDrzava[MAX] = "", imeGradoviDat[MAX] = "";
	FILE* dat = NULL;
	dat = fopen(imeDat, "r");
	if (!dat) {
		printf("Greska pri otvaranju datoteke");
		return NULL;
	}
	while (!feof(dat)) {
		fscanf(dat, "%s %s", imeDrzava, imeGradoviDat);
		gradovi = ProcitajDatotekuGradovi(imeGradoviDat);
		headStablo = DodajDrzavaUStablo(imeDrzava, gradovi, headStablo);
	}
	fclose(dat);
	return headStablo;
}
int DodajGradUListu(PozicijaLista headLista, char* grad, int populacija) {
	PozicijaLista q = StvoriClanListe();
	strcpy(q->grad, grad);
	q->populacija = populacija;
	while (headLista->sljedeci != NULL) {
		if (q->populacija > headLista->sljedeci->populacija) {
			break;
		}
		headLista = headLista->sljedeci;
	}
	q->sljedeci = headLista->sljedeci;
	headLista->sljedeci = q;
	return EXIT_SUCCESS;
}
PozicijaLista ProcitajDatotekuGradovi(char* imeDat) {
	PozicijaLista q = NULL;
	q = StvoriClanListe();
	char gradIme[MAX] = "";
	int gradPopulacija = 0;
	FILE* dat = NULL;
	dat = fopen(imeDat, "r");
	if (!dat) {
		printf("Greska pri otvaranju datoteke");
		return NULL;
	}
	while (!feof(dat)) {
		fscanf(dat, "%s %d", gradIme, &gradPopulacija);
		DodajGradUListu(q, gradIme, gradPopulacija);
	}
	fclose(dat);
	return q;
}
PozicijaStablo DodajDrzavaUStablo(char* drzava, PozicijaLista gradovi, PozicijaStablo p) {
	if (p == NULL) {
		p = StvoriClanStabla(drzava, gradovi);
	}
	else {
		if (strcmp(drzava, p->drzava) < 0) {
			p->lijevo = DodajDrzavaUStablo(drzava, gradovi, p->lijevo);
		}
		if (strcmp(drzava, p->drzava) > 0) {
			p->desno = DodajDrzavaUStablo(drzava, gradovi, p->desno);
		}
	}
	return p;
}