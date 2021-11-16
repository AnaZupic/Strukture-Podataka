#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 1024


typedef struct polinom {
	int koef;
	int eksp;
	polinom* next;
}polinom;


int procitajPolinom(polinom p1, polinom p2, char *imeDatoteke);
int zbrojPolinoma(polinom*p1, polinom*p2, polinom*suma);
int izbrisiNule(suma);
int umnozakPolinoma(polinom*p1, polinom*p2, polinom*umnozak);
int sortiraj(polinom umn);

int main(int argc, char**argv)
{
	polinom p1 = { .koef = 0,.eksp = 0,.next = NULL };
	polinom p2 = { .koef = 0,.eksp = 0,.next = NULL };
	polinom suma = { .koef = 0,.eksp = 0,.next = NULL };
	polinom umnozak = { .koef = 0,.eksp = 0,.next = NULL };
	char imeDatoteke = NULL;

	ProcitajPolinom(p1, p2, imeDatoteke);



	return EXIT_SUCCESS;
}

int procitajPolinom(polinom p1, polinom p2, char *imeDatoteke)
{
	FILE*fp = NULL;
	char buffer[MAX] = { 0 };

	fp = fopen(imeDatoteke, "r");
	if (!fp) {
		perror("Nemoguce otvoriti datoteku!\n");
		return -1;
	}
	fgets(buffer, MAX, fp);
	fgets(buffer, MAX, fp);
	
	fclose(fp);

	return	EXIT_SUCCESS;
}

int zbrojPolinoma(polinom*p1,polinom*p2,polinom*suma)
{
	polinom *pol1 = p1->next;
	polinom *pol2 = p2->next;

	while (pol1 != NULL) {
		dodajSortirano(suma, pol1->koef, pol1->eksp);
		pol1 = pol1->next;
	}
	while (pol2 != NULL) {
		dodajSortirano(suma, pol2->koef, pol2->eksp);
		pol2 = pol2->next;
	}
	izbrisiNule(suma);
	return EXIT_SUCCESS;
}

int izbrisiNule(polinom *pol)
{
	polinom*pom;
	polinom*p = pol;

	while (p->next != NULL)
	{
		if (!p->next->koef) {
			pom = p->next;
			p->next = p->next->next;
		}
		p=p->next;
	}
	return EXIT_SUCCESS;
}

int umnozakPolinoma(polinom*p1, polinom*p2, polinom* umnozak)
{
	polinom *pol1 = p1->next;
	polinom*pol2 = p2->next;

	while (pol1 != NULL)
	{
		pol2 = p2->next;
		while (pol2 != NULL)
		{
			sortiraj(&umnozak);
			pol2 = pol2->next;
		}
		pol1 = pol1->next;
	}

	izbrisiNule(&umnozak);

	return EXIT_SUCCESS;
}

int sortiraj(polinom *umn)
{
	polinom *pom;

	*umn = umn->next;
	*pom = umn->next;

	while (umn != NULL && &pom != NULL) {
		if (umn->eksp == pom->eksp) {
			umn->koef = umn->koef + pom->koef;
			umn->next = pom->next;
			free(&pom);
			pom = umn->next;
		}
		else {
			umn = umn->next;
			pom= pom->next;
		}
	}

	return EXIT_SUCCESS;
}