#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item {
    char name[100];
    int quantity;
    double price;
    struct Item *next;
} Item;

typedef struct Receipt {
    char date[11];   // YYYY-MM-DD
    Item *items;
    struct Receipt *next;
} Receipt;

//prototipi funkc
Receipt* insert_receipt_sorted(Receipt *head, Receipt *newR);
Item* insert_item_sorted(Item *head, Item *newI);
Receipt* load_receipt(char *filename);
Receipt* load_all_receipts(char *list_file);
void free_all(Receipt *head);
int date_to_int(char *date);
void query(Receipt *head);

//insert receipt by date
Receipt* insert_receipt_sorted(Receipt *head, Receipt *newR) {
    if (head == NULL || date_to_int(newR->date) < date_to_int(head->date)) {
        newR->next = head;
        return newR;
    }
    Receipt *temp = head;
    while (temp->next != NULL &&
           date_to_int(temp->next->date) < date_to_int(newR->date)) {
        temp = temp->next;
    }
    newR->next = temp->next;
    temp->next = newR;
    return head;
}

//item po imenu 
Item* insert_item_sorted(Item *head, Item *newI) {
    if (head == NULL || strcmp(newI->name, head->name) < 0) {
        newI->next = head;
        return newI;
    }
    Item *temp = head;
    while (temp->next != NULL &&
           strcmp(temp->next->name, newI->name) < 0) {
        temp = temp->next;
    }
    newI->next = temp->next;
    temp->next = newI;
    return head;
}

//YYYY-MM-DD to integer
int date_to_int(char *date) {
    int y, m, d;
    sscanf(date, "%d-%d-%d", &y, &m, &d);
    return y * 10000 + m * 100 + d;
}

//load 1 receipt
Receipt* load_receipt(char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return NULL;

    Receipt *r = (Receipt*)malloc(sizeof(Receipt));
    r->items = NULL;
    r->next = NULL;

    fscanf(f, "%10s", r->date);

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        Item *i = (Item*)malloc(sizeof(Item));
        i->next = NULL;

        if (sscanf(line, "%99[^,], %d, %lf", i->name, &i->quantity, &i->price) == 3) {
            r->items = insert_item_sorted(r->items, i);
        } else {
            free(i);
        }
    }

    fclose(f);
    return r;
}

//receipts.txt
Receipt* load_all_receipts(char *list_file) {
    FILE *f = fopen(list_file, "r");
    if (!f) return NULL;

    Receipt *head = NULL;
    char filename[100];

    while (fscanf(f, "%s", filename) != EOF) {
        Receipt *r = load_receipt(filename);
        if (r)
            head = insert_receipt_sorted(head, r);
    }

    fclose(f);
    return head;
}

//money and amount of items in range
void query(Receipt *head) {
    char item_name[100];
    char from[11], to[11];

    printf("Enter item name: ");
    scanf("%s", item_name);
    printf("Enter start date (YYYY-MM-DD): ");
    scanf("%s", from);
    printf("Enter end date (YYYY-MM-DD): ");
    scanf("%s", to);

    int from_int = date_to_int(from);
    int to_int = date_to_int(to);

    int total_quantity = 0;
    double total_money = 0;

    Receipt *r = head;
    while (r) {
        int d = date_to_int(r->date);
        if (d >= from_int && d <= to_int) {
            Item *i = r->items;
            while (i) {
                if (strcmp(i->name, item_name) == 0) {
                    total_quantity += i->quantity;
                    total_money += i->quantity * i->price;
                }
                i = i->next;
            }
        }
        r = r->next;
    }

    printf("\nRESULT:\n");
    printf("Total quantity purchased: %d\n", total_quantity);
    printf("Total money spent: %.2f\n", total_money);
}

//free memory
void free_all(Receipt *head) {
    while (head) {
        Receipt *temp = head;
        head = head->next;

        Item *i = temp->items;
        while (i) {
            Item *t2 = i;
            i = i->next;
            free(t2);
        }

        free(temp);
    }
}

//main
int main() {
    Receipt *list = load_all_receipts("receipts.txt");
    if (!list) {
        printf("Error loading receipts.\n");
        return 1;
    }

    query(list);
    free_all(list);

    return 0;
}
