#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void constructHeap(int arr[], int n) {
    int j;
    int temp;
    int left;
    int right;
    int imsi;
    for (int i = n/2; i >= 0; i--) {
        temp = arr[i];
        j = i;
        left = (2*j) + 1;
        right = (2*j) + 2;
        while (left < n) {
            if (right < n && arr[left] >= arr[right]) {
                imsi = right;
            }
            else {
                imsi = left;
            }
            if (temp < arr[imsi]) {
                break;
            }
            arr[j] = arr[imsi];
            j = imsi;
            left = (2 * j) + 1;
            right = (2 * j) + 2;
        }
        arr[j] = temp;
    }
}

int heapsort(int arr[], int n) {
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        constructHeap(arr, i);
    }
    return 0;
}

int main() {
    FILE *fin  = fopen("data.txt", "r");
    FILE *fout = fopen("result.out", "w");

    int arr[1000];
    int n = 0;

    while (n < 1000 && fscanf(fin, "%d", &arr[n]) == 1) {
        n++;
    }
    fclose(fin);

    fprintf(fout, "최초 배열 \n");
    for (int i = 0; i < n; i++) {
        fprintf(fout, "%d \n", arr[i]);
    }
    fprintf(fout, "\n");

    constructHeap(arr, n);
    fprintf(fout, "힙을 구성한 직후 배열 상태\n");
    for (int i = 0; i < n; i++) {
        fprintf(fout, "%d \n", arr[i]);
    }
    fprintf(fout, "\n");
    heapsort(arr, n);

    fprintf(fout, " 힙 정렬 결과\n");
    for (int i = 0; i < n; i++) {
        fprintf(fout, "%d \n", arr[i]);
    }
    fprintf(fout, "\n");

    fclose(fout);
    return 0;
}
