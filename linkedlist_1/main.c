#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *nextnode;
}Node;

Node *head = NULL;
Node *tail = NULL;

void insertNode(int input) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = input;
    newNode->nextnode = NULL;

    if(head == NULL || input >= head->data){
        newNode->nextnode = head;
        head = newNode;
        if(tail == NULL){
            tail = newNode;
        }
    }
    else {
    Node *current = head;
    while (1) {
        if (current->nextnode == NULL) {
            current->nextnode = newNode;
            tail = newNode;
            break;
            }
        else if (input >= current->nextnode->data) {
                newNode->nextnode = current->nextnode;
                current->nextnode = newNode;
                break;
            }
        current = current->nextnode;
        }
    }
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
