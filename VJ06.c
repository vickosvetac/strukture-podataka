#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Dir {
    char name[50];
    struct _Dir *child;   // first child
    struct _Dir *sibling; // next brother
    struct _Dir *parent;  // parent pointer
} Dir;

//prototipi fnc
Dir* createDir(char *name, Dir *parent);
int insertDir(Dir *current, char *name);
Dir* changeDir(Dir *current, char *name);
Dir* goParent(Dir *current);
int listDir(Dir *current);
int menu();

//directory
Dir* createDir(char *name, Dir *parent) {
    Dir *newDir = (Dir*)malloc(sizeof(Dir));
    if (!newDir) return NULL;

    strcpy(newDir->name, name);
    newDir->child = NULL;
    newDir->sibling = NULL;
    newDir->parent = parent;

    return newDir;
}

//subdir
int insertDir(Dir *current, char *name) {
    Dir *newDir = createDir(name, current);
    if (!newDir) return -1;

    if (current->child == NULL) {
        current->child = newDir;
        return 0;
    }

    Dir *temp = current->child;
    while (temp->sibling != NULL)
        temp = temp->sibling;

    temp->sibling = newDir;
    return 0;
}

//
Dir* changeDir(Dir *current, char *name) {
    Dir *temp = current->child;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0)
            return temp;
        temp = temp->sibling;
    }
    return current;
}

//
Dir* goParent(Dir *current) {
    if (current->parent != NULL)
        return current->parent;
    return current;
}

//content
int listDir(Dir *current) {
    Dir *temp = current->child;
    printf("\nDirectory %s contains:\n", current->name);

    if (!temp) {
        printf("  <empty>\n");
        return 0;
    }

    while (temp != NULL) {
        printf("  %s\n", temp->name);
        temp = temp->sibling;
    }
    return 0;
}


int menu() {
    int choice;
    printf("\n1 - md <name>");
    printf("\n2 - cd <name>");
    printf("\n3 - cd..");
    printf("\n4 - dir");
    printf("\n5 - exit");
    printf("\nChoose: ");
    scanf("%d", &choice);
    return choice;
}

//main
int main() {
    Dir *root = createDir("C:", NULL);
    Dir *current = root;
    int choice;
    char name[50];

    while (1) {
        printf("\n\nCurrent directory: %s\n", current->name);
        choice = menu();

        if (choice == 1) {
            printf("Enter folder name: ");
            scanf("%s", name);
            insertDir(current, name);
        }

        else if (choice == 2) {
            printf("Enter folder to enter: ");
            scanf("%s", name);
            Dir *newpos = changeDir(current, name);
            if (newpos == current)
                printf("Directory not found!\n");
            else
                current = newpos;
        }

        else if (choice == 3) {
            current = goParent(current);
        }

        else if (choice == 4) {
            listDir(current);
        }

        else if (choice == 5) {
            printf("Exiting...\n");
            break;
        }

        else {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
