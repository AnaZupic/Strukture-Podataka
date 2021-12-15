#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<malloc.h>
#define MAX 1024
#define razmak 5

typedef struct stablo* S;
struct stablo {
	int element;
	S left;
	S right;
};

int Menu();
S Operacija(S);
int getNum();
S Unesi(S, int);
int Ispisi(S, int);
S Nadji(S, int);
S PronadiNajmanji(S);
S Izbrisi(const S, S);

int Menu() {
	printf("==============================\n");
	printf("*\t1 - Unesi novi cvor\t\t*\n");
	printf("*\t2 - Ispisi elemente stabla\t*\n");
	printf("*\t3 - Izbrisi element stabla\t*\n");
	printf("*\t4 - Ponovo ispisi izbornik\t*\n");
	printf("*\t0 - Zatvori program\t\t*\n");
	printf("==============================\n");

	return 0;
}
S Operacija(S root) {
	int command = 0;
	S Stab;

	printf("\nVas izbor -> ");
	scanf(" %d", &command);

	switch (command) {
	case 1:
		root = Unesi(root, getNum());
		return root;

	case 2:
		Ispisi(root, 0);
		return root;

	case 3:
		Stab = Nadji(root, getNum());
		Izbrisi(root, Stab);
		return root;

	case 4:
		Menu();
		return root;

	case 0:
		return NULL;

	default:
		printf("Greska, pokusajte ponovo!\n");
	}
}

int getNum()
{
	int n;
	printf("Unesite broj: ");
	scanf(" %d", &n);

	return n;
}

S Unesi(S root, int x)
{
	if (root == NULL) {
		root = malloc(sizeof(S));
		root->element = x;
		root->left = NULL;
		root->right = NULL;
		return root;
	}

	else if (x > root->element) {
		root->right = Unesi(root->right, x);
	}

	else if (x < root->element) {
		root->left = Unesi(root->left, x);
	}

	return root;
}

int Ispisi(S root, int space) {

	int i = 0;

	if (root == NULL)
		return 0;

	space += razmak;

	Ispisi(root->right, space);

	printf("\n");
	for (i = razmak; i < space; i++)
		printf(" ");
	printf("%d\n", root->element);

	Ispisi(root->left, space);

	return EXIT_SUCCESS;
}

S Nadji(S root, int pronadi)
{
	S cvor;
	cvor = root;

	if (cvor == NULL)
		return NULL;

	else if (cvor->element == pronadi) {
		return cvor;
	}

	else if (pronadi > cvor->element) {
		return Nadji(cvor->right, pronadi);
	}

	else if (pronadi < cvor->element) {
		return Nadji(cvor->left, pronadi);
	}

	return cvor;
}

S PronadiNajmanji(S root)
{
	if (root == NULL)
		return NULL;
	else if (root->left == NULL)
		return root;

	return PronadiNajmanji(root->left);
}

S Izbrisi(S root, S del)
{
	S pomocna = root;
	S temp = NULL;

	if (pomocna == NULL)
		return NULL;

	else if (del->element < pomocna->element)
		pomocna->left = Izbrisi(pomocna->left, del);

	else if (del->element > pomocna->element)
		pomocna->right = Izbrisi(pomocna->right, del);

	else if (pomocna->left && pomocna->right) {
		temp = PronadiNajmanji(pomocna->right);
		pomocna->element = temp->element;
		pomocna->right = Izbrisi(pomocna->right, pomocna);
	}

	else {
		temp = pomocna;

		if (pomocna->left == NULL)
			pomocna = pomocna->right;
		else
			pomocna = pomocna->left;

		free(temp);
	}

	return pomocna;
}