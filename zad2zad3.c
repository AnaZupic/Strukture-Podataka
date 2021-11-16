#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (1024)

struct _Person;
typedef struct _Person *Position;
typedef struct _Person
{
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
} Person;

int PrependList(Position head, char* name, char* surname, int birthYear);
int AppendList(Position head, char* name, char* surname, int birthYear);
int PrintList(Position first);
Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfter(Position position, Position newPerson);
Position FindLast(Position head);
Position FindBefore(Position first);
Position FindBySurname(char* surname, Position first);
int DeleteAfter(Position head, char* surname);
int DodajIznad(Position head, char* name, char* surname, int birthYear, char* before);
int DodajIspod(Position head, char* name, char* surname, int birthYear, char* after);
int Sortiraj(Position head, char* name, char* surname, int birthYear);
int UnesiUDatoteku(char* fileName, Position first);
int ProcitajIzDatoteke(char* fileName, Position head);

int main(int argc, char** argv)
{
	Person head = { .next = NULL,.name = {0},.surname = {0},.birthYear = 0 };
	Position p = &head;
	char name[50] = { 0 };
	char surname[50] = { 0 };
	int birthYear = 0;
	int izbor = 0;
	char prezime[50] = { 0 };
	printf("\nBIRANJE RADNJE:\n"
		"Unesite:\n"
		"1 za dodati na pocetak liste\n"
		"2 za dodati na kraj liste\n"
		"3 za izbrisati s liste\n"
		"4 za ispisati listu\n"
		"5 za sortirati listu\n");
	scanf("%d", &izbor);

	switch (izbor) {
	case 1: {
		printf("Unesite ime prezime i godinu rodenja\n");
		scanf(" %s %s %d", name, surname, &birthYear);
		PrependList(p, name, surname, birthYear);
		break;
	}
	case 2: {
		printf("Unesite ime prezime i godinu rodenja\n");
		scanf(" %s %s %d", name, surname, &birthYear);
		AppendList(p, name, surname, birthYear);
		break;
	}
	case 3: {
		printf("\nKoga zelite izbrisati\n");
		scanf(" %s", prezime);
		DeleteAfter(prezime, p);
		break;
	}
	case 4: {
		PrintList(p->next);
		break;
	}
	case 5: {
		UnesiUDatoteku("Sort.txt", p->next);
		ProcitajIzDatoteke("Sort.txt",p);
		break;
	}
	default: {
		printf("GRESKA\n");
	}
}


	return EXIT_SUCCESS;
}



Position CreatePerson(char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson)
	{
		perror("Couldn't allocate memmory.\n");
		return NULL;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	return newPerson;
}

int InsertAfter(Position p, Position newPerson)
{
	newPerson->next = p->next;
	p->next = newPerson;

	return 0;
}

Position FindLast(Position head)
{
	Position last = head;

	while (last->next)
	{
		last = last->next;
	}

	return last;
}

int PrependList(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = CreateNewPerson(name, surname, birthYear);
	if (!newPerson)
		return -1;

	InsertAfter(head, newPerson);

	return 0;
}
int AppendList(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	Position last = NULL;

	newPerson = CreateNewPerson(name, surname, birthYear);
	if (!newPerson)
		return -1;

	last = FindLast(head);
	InsertAfter(last, newPerson);

	return 0;
}

int PrintList(Position first)
{
	Position temp = first;

	if (!temp)
		printf("The list is empty. :(\n");
	for (temp; temp; temp = temp->next)
		printf("Name: %-10s Surname: %-13s Birthyear: %d\n",
			temp->name, temp->surname, temp->birthYear);
	printf("\n");

	return 0;
}

Position FindBySurname(char* surname, Position first)
{
	Position temp = first;

	for (temp; temp; temp = temp->next)
		if (strcmp(temp->surname, surname) == 0)
			return temp;

	return temp;
}

Position FindBefore(char* surname, Position head)
{
	Position temp = head;

	for (temp; temp->next; temp = temp->next)
		if (strcmp(temp->next->surname, surname) == 0)
			return temp;

	return temp;
}

int DeleteAfter(char* surname, Position head)
{
	Position temp = head;
	Position toDelete = NULL;

	for (temp; temp->next; temp = temp->next)
		if (strcmp(temp->next->surname, surname) == 0)
		{
			toDelete = temp->next;
			temp->next = toDelete->next;
			free(toDelete);
			return 0;
		}

	return -1;
}


int DodajIspod(Position head, char* name, char* surname, int birthYear, char* after)
{
	Position temp = NULL;
	Position newPerson = NULL;

	temp = FindBySurname(after, head->next);
	if (!temp)
		return -1;

	newPerson = CreateNewPerson(name, surname, birthYear);
	if (!newPerson)
		return -1;

	InsertAfter(temp, newPerson);

	return 0;
}

int DodajIznad(Position head, char* name, char* surname, int birthYear, char* before)
{
	Position temp = NULL;
	Position newPerson = NULL;

	temp = FindPrevious(before, head);
	if (!temp)
		return -1;

	newPerson = CreateNewPerson(name, surname, birthYear);
	if (!newPerson)
		return -1;

	InsertAfter(temp, newPerson);

	return 0;
}

int Sortiraj(Position head, char* name, char* surname, int birthYear)
{
	Position temp = head;
	Position newPerson = NULL;

	for (temp; temp->next; temp = temp->next)
	{
		if (strcmp(surname, temp->next->surname) == 0)
		{
			if (strcmp(name, temp->next->name) < 0)
				break;
			if (strcmp(name, temp->next->name) == 0)
			{
				if (birthYear < temp->next->birthYear)
					break;
			}
		}
		if (strcmp(surname, temp->next->surname) < 0)
			break;
	}

	newPerson = CreateNewPerson(name, surname, birthYear);
	if (!newPerson)
		return -1;

	InsertAfter(temp, newPerson);

	return 0;
}

int UnesiUDatoteku(char* fileName, Position first)
{
	Position temp = first;
	FILE* f = NULL;

	f = fopen(fileName, "w");
	if (f == NULL)
	{
		printf("Neuspjesno otvaranje datoteke.");
		return -1;
	}

	fprintf(f, " Name       Surname       Birthyear");
	for (temp; temp; temp = temp->next)
		fprintf(f, "\n %-10s %-13s %d",
			temp->name, temp->surname, temp->birthYear);
	printf("\n");

	fclose(f);

	return 0;
}

int ProcitajIzDatoteke(char* fileName, Position head)
{
	Position temp = head;
	FILE* f = NULL;
	char buffer[MAX_SIZE] = { 0 };
	char name[20] = { 0 };
	char surname[20] = { 0 };
	int birthYear = 0;

	f = fopen(fileName, "r");
	if (f == NULL)
	{
		printf("Neuspjesno otvaranje datoteke.");
		return -1;
	}

	while (!feof(f))
	{
		fgets(buffer, MAX_SIZE, f);
		if (sscanf(buffer, " %s %s %d", name, surname, &birthYear) == 3)
		{
			SortedAdd(temp, name, surname, birthYear);
		}
	}

	fclose(f);

	return 0;
}
