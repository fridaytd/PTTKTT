// Thuat toan sap xep chon

#include <stdio.h>

typedef int keyType;
typedef float otherType;

typedef struct recordType {
    keyType key;
    otherType otherFields;
} recordType;

void swap(recordType* a, recordType* b) {
    recordType temp=*a;
    *a=*b;
    *b=temp;
}

void readData(recordType a[], int* n) {
    FILE* f;
    f=fopen("data.txt", "r");
    int i=0;
    if (f!=NULL) {
        while (!feof(f)) {
            fscanf(f, "%d%f", &a[i].key, &a[i].otherFields);
            i++;
        }
    }
    else {
        printf("Loi doc file !!!");
    }
    *n=i;
    fclose(f);
}

void printData(recordType a[], int n) {
    int i;
    for (i=0; i<n; i++) {
        printf("%d %.2f\n", a[i].key, a[i].otherFields);
    }
}

void selectionSort(recordType a[], int n) {
    int i, j;
    for (i=0; i<n-1; i++) {
        int min=a[i].key;
        int minIndex=i;
        for (j=i+1; j<n; j++) {
            if (a[j].key<min) {
                min=a[j].key;
                minIndex=j;
            }
        }
        swap(&a[i], &a[minIndex]);
    }
}

int main() {
    recordType a[100];
    int n;
    readData(a, &n);
    printf("Thuat toan sap xep chon: \n");
    printf("Du lieu truoc khi sap xep\n");
    printData(a, n);
    selectionSort(a, n);
    printf("Du lieu sau khi sap xep\n");
    printData(a, n);
    return 0;
}