#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int arr[MAX];
int length = 0;

void addlist(int input){
    int index = 0;
    while (index < length && input <= arr[index]){
        index++;
    }
    for (int i = length; i > index; i--) {
        arr[i] = arr[i - 1];
    }
    arr[index] = input;
    length++;
}

int main(){
    FILE *f1 = fopen("data.dat", "r");
    int input = 0;
    while (fscanf(f1, "%d", &input) != EOF) {
        addlist(input);
    }

    fclose(f1);

    for (int i = 0; i < length; i++) {
        printf("%d\n", arr[i]);
    }

    return 0;
}
