#include <stdio.h>
#define MAX 100

int main() {
    FILE *f1 = fopen("data.dat", "r");

    int arr[MAX];
    int i = 0;

    while (fscanf(f1, "%d", &arr[i]) != EOF) {
        i++;
    }

    for(int j = 0; j < i; j++){
        printf("%d\n",arr[j]);
    }

    fclose(f1);

    return 0;
}
