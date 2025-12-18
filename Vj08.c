#include <stdio.h>
#include <stdlib.h>

//struktura 
typedef struct tree* Treepos;

struct tree {
    int value;
    Treepos left;
    Treepos right;
};

//funkc
Treepos CreateNode(int value);
Treepos InsertTree(Treepos root, int value);
Treepos FindMin(Treepos root);
Treepos DeleteTree(Treepos root, int value);

int Inorder(Treepos root);
int Preorder(Treepos root);
int Postorder(Treepos root);

int Height(Treepos root);
int PrintLevel(Treepos root, int level);
int LevelOrder(Treepos root);

void FreeTree(Treepos root);

//main
int main() {
    Treepos root = NULL;

    
    root = InsertTree(root, 50);
    root = InsertTree(root, 30);
    root = InsertTree(root, 70);
    root = InsertTree(root, 20);
    root = InsertTree(root, 40);

    
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

    //del node
    root = DeleteTree(root, 30);
    printf("\nAfter deleting 30:\n");

    printf("Inorder: ");
    Inorder(root);
    printf("\n");

    
    FreeTree(root);
    root = NULL;

    return 0;
}

//

//new node
Treepos CreateNode(int value) {
    Treepos node = (Treepos)malloc(sizeof(struct tree));
    if (!node) return NULL;

    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

//search 
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

//min value node
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

// Preorder
int Preorder(Treepos root) {
    if (root == NULL) return 0;
    printf("%d ", root->value);
    Preorder(root->left);
    Preorder(root->right);
    return 1;
}

//Postorder traversal
int Postorder(Treepos root) {
    if (root == NULL) return 0;
    Postorder(root->left);
    Postorder(root->right);
    printf("%d ", root->value);
    return 1;
}

//tree height
int Height(Treepos root) {
    if (root == NULL) return 0;
    int leftHeight = Height(root->left);
    int rightHeight = Height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

//print node
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

//lvl order
int LevelOrder(Treepos root) {
    int h = Height(root);
    for (int i = 1; i <= h; i++) {
        PrintLevel(root, i);
    }
    return 1;
}

//free
void FreeTree(Treepos root) {
    if (root == NULL)
        return;

    FreeTree(root->left);
    FreeTree(root->right);
    free(root);
}
