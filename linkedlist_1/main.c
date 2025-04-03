#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *nextnode;
}Node;

Node *head = NULL;
Node *tail = NULL;

void insertNode(int input) {

    Node *NewNode = (Node*)malloc(sizeof(Node));
    if (head == NULL) {
        head = NewNode;
    }
    else tail->nextnode = NewNode;

    NewNode->data = input;
    NewNode->nextnode = NULL;
    tail = NewNode;

}


int main() {
    FILE *f1 = fopen("data.dat", "r");
    int input = 0;
    while (fscanf(f1, "%d", &input) != EOF) {
        insertNode(input);
    }
    fclose(f1);
    Node *search = head;
    while (search != NULL) {
        printf("%d\n",search->data);
        search = search->nextnode;
    }
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->nextnode;
        free(temp);
    }
    return 0;
}
