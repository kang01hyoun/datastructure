#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *nextnode;
} Node;

Node *head = NULL;

void insertNode(int input) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = input;
    if (head == NULL) {
        head = newNode;
        newNode->nextnode = head;
    }
    else {
        Node* temp = head;
        while (temp->nextnode != head) {
            temp = temp->nextnode;
        }
        temp->nextnode = newNode;
        newNode->nextnode = head;
    }
}

void deletenode(int key) {
    Node *prevNode = NULL;
    Node *nowNode = head;

    prevNode = head;
    while (prevNode->nextnode != head) {
        prevNode = prevNode->nextnode;
    }

    printf("<");

    while (nowNode->nextnode != nowNode) {
        for (int i = 0; i < key - 1; i++) {
            prevNode = nowNode;
            nowNode = nowNode->nextnode;
        }
        printf("%c, ", 64 + nowNode->data);
        prevNode->nextnode = nowNode->nextnode;
        free(nowNode);
        nowNode = prevNode->nextnode;
    }

    printf("%c>\n", 64 + nowNode->data);
    free(nowNode);
}

int main() {
    int input = 0;
    int key = 0;
    int start = 0;
    printf("input = ");
    scanf("%d",&input);
    printf("\nkey = ");
    scanf("%d",&key);
    printf("\nstart = ");
    scanf("%d",&start);

    for (int i = 1; i <= input; i++) {
        insertNode(i);
    }

	for (int i = 1; i < start; i++){
		head = head->nextnode;
	}
    deletenode(key);
    return 0;
}
