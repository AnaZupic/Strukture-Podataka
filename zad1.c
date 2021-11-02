#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE (128)
#define MAX_LINE (1024)
#define _CRT_SECURE_NO_WARNINGS

typedef struct _student {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	double bodovi;
}student;

int ProcitajBrojRedakaIzDatoteke(char*nazivDatoteke);
student*AlocirajMemorijuIProcitajStudente(int brojStudenata, char*nazivDatoteke);
student*RacunanjeBodova(student*, int, FILE*);

int main()
{
	FILE*dat = NULL;
	student*studenti = NULL;
	int n;

	dat = fopen_s("studenti.txt", "r");

	n = ProcitajBrojRedakaIzDatoteke("studenti.txt");
	printf("Broj studenata u datoteci: %d", n);

	studenti = (student*)malloc(n * sizeof(student));

	rewind(dat);
	RacunanjeBodova(studenti, n, dat);

	fclose(dat);

	return 0;
}

int ProcitajBrojRedakaIzDatoteke(char*nazivDatoteke)
{
	int brojac = 0;
	FILE*datoteka = NULL;
	char buffer[MAX_LINE] = { 0 };

	datoteka = fopen_s(nazivDatoteke, "r");

	if (!datoteka) {
		printf("Greska!");
		return -1;
	}

	while (!feof(datoteka))
	{
		fegts(buffer, MAX_LINE, datoteka);
		brojac++;
	}

	fclose(datoteka);

	return brojac;
}

student*AlocirajMemorijuIProcitajStudente(int brojStudenata, char*nazivDatoteke)
{
	int brojac = 0;
	FILE*datoteka = NULL;
	student* studenti = NULL;

	studenti = (student*)malloc(brojStudenata * sizeof(student));
	datoteka = fopen_s(nazivDatoteke, "r");

	if (!datoteka) {
		printf("Greska alociranja!");
		free(studenti);
		return NULL;
	}

	while (!feof(datoteka)) {
		fscanf_s(datoteka, "%s %s %lf", studenti[brojac].ime, studenti[brojac].prezime, &studenti[brojac].bodovi);
		brojac++;
	}

	fclose(datoteka);


	return studenti;
}

student*RacunanjeBodova(student*stud, int n, FILE*dat)
{
	int i;
	int maxBrojBodova = 0;
	float*relativniBodovi = NULL;

	relativniBodovi = (float*)malloc(n * sizeof(float));

	for (i = 0; i < n; i++) {
		fscanf_s(dat, " %s %s %d", stud[i].ime, stud[i].prezime, &stud[i].bodovi);
		if (maxBrojBodova < stud[i].bodovi) {
			maxBrojBodova = stud[i].bodovi;
		}
	}
	for (i = 0; i < n; i++) {
		relativniBodovi[i] = (double)stud[i].bodovi / maxBrojBodova * 100;
		printf("\n%s %s %lf %.2f%%", stud[i].ime, stud[i].prezime, stud[i].bodovi, relativniBodovi[i]);
	}
	return stud;
}