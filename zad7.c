#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30

struct _Direktorij;
typedef struct _Direktorij *PozicijaDirektorij;
typedef struct _Direktorij {
	char ime[MAX];
	PozicijaDirektorij dijete;
	PozicijaDirektorij susjed;
} Direktorij;

struct _Cvor;
typedef struct _Cvor *Pozicija;
typedef struct _Cvor {
	PozicijaDirektorij roditelj;
	Pozicija sljedeci;
} Cvor;

int Push(Pozicija, PozicijaDirektorij);
int PrintOpcije();
int SortiraniUnos(PozicijaDirektorij, PozicijaDirektorij);
int dir(PozicijaDirektorij);
int izlaz(Pozicija, PozicijaDirektorij);
PozicijaDirektorij cdRoditelj(Pozicija);
PozicijaDirektorij Pop(Pozicija);
PozicijaDirektorij cd(Pozicija, PozicijaDirektorij, char*);
PozicijaDirektorij StvoriDirektorij(char*);
PozicijaDirektorij md(Pozicija, PozicijaDirektorij, char*);
Pozicija StvoriPoziciju();


int main() {
	char operacija = '0';
	int isActive = 1;

	char ime[MAX];
	Pozicija stog = NULL;
	PozicijaDirektorij korijen = NULL, trenutni = NULL, rezultat = NULL;


	stog = StvoriPoziciju();
	korijen = StvoriDirektorij("C:");
	trenutni = korijen;

	while (isActive) {
		PrintOpcije();
		scanf(" %c", &operacija);

		switch (operacija) {
		case '1':
			printf("Odabrano: md\n");
			printf("Ime novog direktorija: ");
			scanf("%s", ime);
			rezultat = md(stog, trenutni, ime);
			if (!rezultat) {
				printf("Greska pri stvaranju direktorija");
			}
			break;
		case '2':
			printf("Odabrano: cd dir\n");
			printf("Ime direktorija: ");
			scanf("%s", ime);
			rezultat = cd(stog, trenutni, ime);
			if (!rezultat) {
				printf("Greska pri otvaranju direktorija");
			}
			else {
				trenutni = rezultat;
			}
			break;
		case '3':
			printf("Odabrano: cd..\n");
			rezultat = cdRoditelj(stog);
			if (!rezultat) {
				printf("Ne moze se ici vise od korijena!");
			}
			else {
				trenutni = rezultat;
			}
			break;
		case '4':
			printf("Odabrano: dir\n");
			dir(trenutni);
			break;
		case '5':
			printf("Odabrano: prekid programa");
			isActive = 0;
			break;
		default:
			printf("Ne valjan odabir - probajte ponovno");
			break;
		}
	}
	return 0;
}

int dir(PozicijaDirektorij trenutni) {
	PozicijaDirektorij tmp = NULL;
	printf("%s\n", trenutni->ime);
	if (trenutni->dijete != NULL) {
		tmp = trenutni->dijete;
		while (tmp != NULL) {
			printf("\t%s", tmp->ime);
			tmp = tmp->susjed;
		}
	}
	return 0;
};

PozicijaDirektorij cd(Pozicija stog, PozicijaDirektorij trenutni, char *ime) {
	PozicijaDirektorij q = NULL, tmp = NULL;
	if (trenutni->dijete == NULL) {
		printf("Trenutni direkotorij je prazan");
		return NULL;
	}
	tmp = trenutni->dijete;
	while (tmp != NULL) {
		if (strcmp(ime, tmp->ime) == 0) {
			q = tmp;
		}
		tmp = tmp->susjed;
	}
	Push(stog, trenutni);
	return q;
}

int SortiraniUnos(PozicijaDirektorij trenutni, PozicijaDirektorij q) {
	PozicijaDirektorij head = NULL, r = NULL;
	head = StvoriDirektorij(" ");
	r = head;


	if (trenutni->dijete == NULL) {
		trenutni->dijete = q;
		return 0;
	}

	head->susjed = trenutni->dijete;
	while (r->susjed != NULL && strcmp(r->susjed->ime, q->ime) < 0) {
		r = r->susjed;
	}
	q->susjed = r->susjed;
	r->susjed = q;
	trenutni->dijete = head->susjed;
	return 0;
};

PozicijaDirektorij md(Pozicija stog, PozicijaDirektorij trenutni, char* ime) {
	PozicijaDirektorij q = NULL;
	q = StvoriDirektorij(ime);
	SortiraniUnos(trenutni, q);
	return q;
}

int PrintOpcije() {
	printf("\n\n********************************************************************\n\n");
	printf("Odaberi operaciju: \n\t 1. md (stvori direktorij) \n\t 2. cd dir (promjeni direktorij) \n\t 3. cd.. (promjeni u direktorij roditelja) "
		"\n\t 4. dir (ispisi sadrzaj odabranog direktorija) \n\t 5. prekid program\n");
	return 0;
}

Pozicija StvoriPoziciju() {
	Pozicija q = malloc(sizeof(Cvor));
	if (!q) {
		printf("Greska pri alociranju memorije");
		return NULL;
	}
	q->sljedeci = NULL;
	return q;
}

PozicijaDirektorij StvoriDirektorij(char *ime) {
	PozicijaDirektorij q = malloc(sizeof(Direktorij));
	if (!q) {
		printf("Greska pri alociranju memorije");
		return NULL;
	}
	q->susjed = NULL;
	q->dijete = NULL;
	strcpy(q->ime, ime);
	return q;
}
PozicijaDirektorij Pop(Pozicija stog) {
	Pozicija tmp = NULL;
	PozicijaDirektorij p = NULL;
	if (stog == NULL || stog->sljedeci == NULL) {
		return NULL;
	}
	tmp = stog->sljedeci;
	p = tmp->roditelj;
	stog->sljedeci = tmp->sljedeci;
	free(tmp);
	return p;
}

int Push(Pozicija stog, PozicijaDirektorij trenutni) {
	Pozicija q = NULL;
	q = StvoriPoziciju();
	q->roditelj = trenutni;
	q->sljedeci = stog->sljedeci;
	stog->sljedeci = q;
	return 0;
}

PozicijaDirektorij cdRoditelj(Pozicija stog) {
	return Pop(stog);
}