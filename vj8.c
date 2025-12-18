#include <stdio.h>
#include <stdlib.h>

typedef struct tree* Treepos;

struct tree {
    int value;
    Treepos left;
    Treepos right;
};

//aloc node
Treepos CreateNode(int value) {
    Treepos node = (Treepos)malloc(sizeof(struct tree));
    if (!node) return NULL;

    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

//insert tree
Treepos InsertTree(Treepos root, int value) {
    if (root == NULL) {
        return CreateNode(value);
    }

    if (value < root->value) {
        root->left = InsertTree(root->left, value);
    } else if (value > root->value) {
        root->right = InsertTree(root->right, value);
    }

    return root;
}

//min node
Treepos FindMin(Treepos root) {
    if (root == NULL) return NULL;
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

//del node
Treepos DeleteTree(Treepos root, int value) {
    if (root == NULL) return NULL;

    if (value < root->value) {
        root->left = DeleteTree(root->left, value);
    } else if (value > root->value) {
        root->right = DeleteTree(root->right, value);
    } else {
        if (root->left == NULL) {
            Treepos temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Treepos temp = root->left;
            free(root);
            return temp;
        }

        Treepos temp = FindMin(root->right);
        root->value = temp->value;
        root->right = DeleteTree(root->right, temp->value);
    }

    return root;
}

//inorder
int Inorder(Treepos root) {
    if (root == NULL) return 0;
    Inorder(root->left);
    printf("%d ", root->value);
    Inorder(root->right);
    return 1;
}

//preorder
int Preorder(Treepos root) {
    if (root == NULL) return 0;
    printf("%d ", root->value);
    Preorder(root->left);
    Preorder(root->right);
    return 1;
}

//postorder
int Postorder(Treepos root) {
    if (root == NULL) return 0;
    Postorder(root->left);
    Postorder(root->right);
    printf("%d ", root->value);
    return 1;
}

//level order
int Height(Treepos root) {
    if (root == NULL) return 0;
    int leftHeight = Height(root->left);
    int rightHeight = Height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int PrintLevel(Treepos root, int level) {
    if (root == NULL) return 0;
    if (level == 1) {
        printf("%d ", root->value);
    } else {
        PrintLevel(root->left, level - 1);
        PrintLevel(root->right, level - 1);
    }
    return 1;
}

int LevelOrder(Treepos root) {
    int h = Height(root);
    for (int i = 1; i <= h; i++) {
        PrintLevel(root, i);
    }
    return 1;
}

//
int main() {
    Treepos root = NULL;

    // Umetanje elemenata u stablo
    root = InsertTree(root, 50);
    root = InsertTree(root, 30);
    root = InsertTree(root, 70);
    root = InsertTree(root, 20);
    root = InsertTree(root, 40);

    //print tree
    printf("Inorder: ");
    Inorder(root);
    printf("\n");

    printf("Preorder: ");
    Preorder(root);
    printf("\n");

    printf("Postorder: ");
    Postorder(root);
    printf("\n");

    printf("Level order: ");
    LevelOrder(root);
    printf("\n");

    // Brisanje elementa i ponovni ispis
    root = DeleteTree(root, 30);
    printf("\nNakon brisanja 30:\n");

    printf("Inorder: ");
    Inorder(root);
    printf("\n");

    return 0;
}


    return 0;
}
