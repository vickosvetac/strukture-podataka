#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node* Position;

struct node {
    int value;
    Position left;
    Position right;
};

Position createNode(int x) {
    Position p = malloc(sizeof(struct node));
    p->value = x;
    p->left = NULL;
    p->right = NULL;
    return p;
}

Position insert(Position root, int x) {
    if (root == NULL)
        return createNode(x);

    if (x < root->value)
        root->left = insert(root->left, x);
    else
        root->right = insert(root->right, x);

    return root;
}

int inorderToFile(Position root, FILE* fp) {
    if (root == NULL)
        return 0;

    inorderToFile(root->left, fp);
    fprintf(fp, "%d ", root->value);
    inorderToFile(root->right, fp);

    return 0;
}



int replace(Position root) {
    if (root == NULL)
        return 0;

    int left = replace(root->left);
    int right = replace(root->right);
    int old = root->value;

    root->value = left + right;

    return root->value + old;
}

int main() {
    int niz[] = {2,5,7,8,11,1,4,2,3,7};
    int n = 10;
    int i;
    Position root = NULL;

  
    for (i = 0; i < n; i++)
        root = insert(root, niz[i]);

    
    FILE* f1 = fopen("inorder_a.txt", "w");
    inorderToFile(root, f1);
    fclose(f1);

   
    replace(root);


    FILE* f2 = fopen("inorder_b.txt", "w");
    inorderToFile(root, f2);
    fclose(f2);


    Position root2 = NULL;
    srand((unsigned)time(NULL));

    for (i = 0; i < 10; i++)
        root2 = insert(root2, (rand() % 81) + 10);

    FILE* f3 = fopen("inorder_random_a.txt", "w");
    inorderToFile(root2, f3);
    fclose(f3);

    replace(root2);

    FILE* f4 = fopen("inorder_random_b.txt", "w");
    inorderToFile(root2, f4);
    fclose(f4);

    return 0;
}
