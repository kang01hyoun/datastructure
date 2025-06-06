#include <stdio.h>
#include <stdlib.h>
#define N 10

typedef struct Node {
    int vertex;
    struct Node *nextNode;
} Node;

Node *head[N];
int visited[N];
Node *current[N];
int stackarr[N];

Node* newNode(int vertex){
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->vertex = vertex;
    temp->nextNode = NULL;
    return temp;
}

void addEdge(int from, int to){
    Node *toNode = newNode(to);
    toNode->nextNode = head[from];
    head[from] = toNode;

    Node *fromNode = newNode(from);
    fromNode->nextNode = head[to];
    head[to] = fromNode;
}

void DFS(int start, FILE *fout){
    int top = -1;
    visited[start] = 1;
    fprintf(fout, "starting point vertex : %d\n", start);
    stackarr[++top] = start;

    while (top >= 0) {
        int curr = stackarr[top];

        while (current[curr] != NULL && visited[current[curr]->vertex] == 1) {
            current[curr] = current[curr]->nextNode;
        }

        if (current[curr] != NULL) {
            int neighbor = current[curr]->vertex;
            fprintf(fout, "from %d to %d visited %d\n", curr, neighbor, neighbor);
            visited[neighbor] = 1;
            stackarr[++top] = neighbor;
            current[curr] = current[curr]->nextNode;
        }
        else {
            top--;
        }
    }
}

int main(){
    int starts[10];
    int input;
    int n = N;
    int m;
    FILE *fin, *fout;

    fin = fopen("data.txt", "r");
    fout = fopen("output.txt", "w");
    fscanf(fin, "%d", &m);
    for (int i = 0; i < 10; i++) {
        head[i] = NULL;
        visited[i] = 0;
        current[i] = NULL;
    }

    for (int i = 0; i < m; i++) {
        int from;
        int to;
        fscanf(fin, "%d %d", &from, &to);
        addEdge(from, to);
    }

    fprintf(fout, "인접리스트 출력\n");
    for (int i = 0; i < 10; i++) {
        fprintf(fout, "vertex %d", i);
        Node *ptr = head[i];
        while (ptr != NULL) {
            fprintf(fout, " -> %d", ptr->vertex);
            ptr = ptr->nextNode;
        }
        fprintf(fout, " -> NULL\n");
    }


    printf("탐색할 정점의 수를 입력하세요 : ");
    scanf("%d", &input);
    for (int i = 0; i < input; i++) {
        printf("\n시작할 정점을 입력하십시오 : ");
        scanf("%d", &starts[i]);
    }

    for (int index = 0; index < input; index++) {
        int startv = starts[index];
        for (int i = 0; i < 10; i++) {
            visited[i] = 0;
            current[i] = head[i];
        }
        fprintf(fout, "\n\nDFS search starting point %d \n", startv);
        DFS(startv, fout);
    }

    for (int i = 0; i < 10; i++) {
        Node *ptr = head[i];
        while (ptr) {
            Node *temp = ptr;
            ptr = ptr->nextNode;
            free(temp);
        }
    }
    printf("output.txt에 출력되었습니다. 파일 확인 바랍니다.");
    fclose(fout);
    fclose(fin);
    return 0;
}
