#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *leftNode;
    struct Node *rightNode;
};

struct Node* newNode(int key) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = key;
    temp->leftNode = NULL;
    temp->rightNode = NULL;
    return temp;
}

struct Node* search(struct Node *BTNode, int key) {
    if (BTNode == NULL)
        return NULL;
    if (key == BTNode->data)
        return BTNode;
    if (key < BTNode->data)
        return search(BTNode->leftNode, key);
    return search(BTNode->rightNode, key);
}

struct Node* insert(struct Node* BTNode, int key) {
    if (BTNode == NULL)
        return newNode(key);
    if (key < BTNode->data)
        BTNode->leftNode = insert(BTNode->leftNode, key);
    else if (key > BTNode->data)
        BTNode->rightNode = insert(BTNode->rightNode, key);
    return BTNode;
}

struct Node* minNode(struct Node* node) {
    struct Node* temp = node;
    while (temp && temp->leftNode != NULL)
        temp = temp->leftNode;
    return temp;
}

struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return root;
    if (key < root->data)
        root->leftNode = deleteNode(root->leftNode, key);
    else if (key > root->data)
        root->rightNode = deleteNode(root->rightNode, key);
    else {
        if (root->leftNode == NULL) {
            struct Node* tmp = root->rightNode;
            free(root);
            return tmp;
        }
        else if (root->rightNode == NULL) {
            struct Node* tmp = root->leftNode;
            free(root);
            return tmp;
        }
        struct Node* tmp = minNode(root->rightNode);
        root->data = tmp->data;
        root->rightNode = deleteNode(root->rightNode, tmp->data);
    }
    return root;
}

void saveTree(FILE *fout, struct Node *root) {
    if (!root) return;
    fprintf(fout, "%d\n", root->data);
    saveTree(fout, root->leftNode);
    saveTree(fout, root->rightNode);
}

int main(void) {
    char input;
    int key;
    struct Node *BT = NULL;

    FILE *fin = fopen("data.txt", "r");
    FILE *fout = fopen("output.txt", "w");


    while (fscanf(fin,"%d", &key) == 1){
        BT = insert(BT, key);
    }
    fclose(fin);


    while (1) {
        printf("=== 이진탐색트리 메뉴 ===\n");
        printf("(s) search key\n");
        printf("(i) insert key\n");
        printf("(d) delete key\n");
        printf("(q) quit\n");
        printf("Input: ");
        scanf(" %c", &input);

        if (input == 's') {
            printf("정수를 입력하세요 :");
            scanf("%d", &key);
            struct Node *found = search(BT, key);
            if (found)
                printf("Found %d\n", key);
            else
                printf("Not found\n");
            continue;
        }
        else if (input == 'i') {
            printf("정수를 입력하세요 :");
            scanf("%d", &key);
            BT = insert(BT, key);
            printf("Insert finished %d\n", key);
            continue;
        }
        else if (input == 'd') {
            printf("정수를 입력하세요 :");
            scanf("%d", &key);
            BT = deleteNode(BT, key);
            printf("Deleted %d\n", key);
            continue;
        }
        else if (input == 'q') {
            break;
        }
        continue;
    }

    if (fout) {
        saveTree(fout, BT);
        fclose(fout);
    }

    return 0;
}
