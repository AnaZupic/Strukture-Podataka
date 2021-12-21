#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct _tree;
typedef struct _tree* Position;
typedef struct _tree {
    int number;
    Position left;
    Position right;

} tree;

struct _list;
typedef struct _list* ListPosition;
typedef struct _list
{
    int element;
    ListPosition next;
} lista;

Position Insert(Position p, int x);
int Print(Position p, ListPosition h);
int Replace(Position p);
int AddToList(ListPosition p, int x);
int AddToFile(char*FileName, ListPosition p);
int EnterFileName(char* FileName);
int FreeAll(Position root);
int Pop(ListPosition head);

int main()
{
    Position root = NULL;
    int a[] = {2, 5, 7, 8, 11, 1, 4, 2, 3, 7};
    int i = 0;
    char* FileName = {0};
    lista head = {.next = NULL, .element = 0 };
    root->number = a[0];
    root->left = NULL;
    root->right = NULL;
    for(i = 1; i < 10; i++) {
        root = insert(root, a[i]);
    }
    print(root);


    /*srand(time(NULL));
    Position root = NULL;
    int i = 0, x = 0;
    root = (Position)malloc(sizeof(tree));
    root->number = rand() % 80 + 10;
    root->left = NULL;
    root->right = NULL;
    printf("%d ", root->number);
    for(i = 1; i < 10; i++) {
        x = rand() % 80 + 10;
        printf("%d ", x);
        root = Insert(root, x);
    }
    printf("\n");*/

    EnterFileName(FileName);

    Print(root, &head);
    AddToFile(FileName, head.next);

    root->number = Replace(root->left) + Replace(root->right);

    printf("\n");
    Print(root, &head);

    AddToFile(FileName, head.next);

    FreeAll(root);

    return 0;
}

Position Insert(Position p, int x)
{
    Position q = NULL;
    if(p == NULL) {
        q = (Position)malloc(sizeof(tree));
        q->number = x;
        q->left = NULL;
        q->right = NULL;
        return q;
    }

    if(x >= p->number) {
        p->right = Insert(p->right, x);
    }
    if(x < p->number) {
        p->left = Insert(p->left, x);
    }

    return p;
}

int Print(Position p, ListPosition h)
{
    if(p == NULL) {
        return -1;
    }

    Print(p->right, h);
    printf("%d ", p->number);
    AddToList(h ,p->number);
    Print(p->left, h);

    return EXIT_SUCCESS;
}

int Replace(Position p)
{
    int t;
    if(p == NULL) {
        return 0;
    }

    t = p->number;
    p->number = Replace(p->left) + Replace(p->right);
    return t + p->number;
}

int AddToList(ListPosition p, int x)
{
    ListPosition q = NULL;
    while(p != NULL) {
        if(p->next == NULL) {
            q = (ListPosition)malloc(sizeof(lista));
            q->element = x;
            p->next = q;
            q->next = NULL;
        }

        p = p->next;
    }

    return EXIT_SUCCESS;
}

int AddToFile(char* FileName, ListPosition p)
{

    FILE* fp = fopen(FileName, "a");
    if(!fp) {
        printf("Can not open file!\n");
        return -1;
    }

    while(p->next)
    {
        fprintf(fp, "%d    ", p->next->element);
        Pop(p);
    }

    fprintf(fp, "\n");

    fclose(fp);

    return EXIT_SUCCESS;
}

int EnterFileName(char* FileName)
{
    printf("Unesite ime datoteke: ");
    scanf(" %s", FileName);

    return EXIT_SUCCESS;
}

int FreeAll(Position root)
{
    if(!root) {
        return EXIT_SUCCESS;
    }

    FreeAll(root->left);

    FreeAll(root->right);

    free(root);

    return EXIT_SUCCESS;
}

int Pop(ListPosition head)
{
    ListPosition temp = head->next;

    head->next = temp->next;
    free(temp);

    return EXIT_SUCCESS;
}
