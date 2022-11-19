// Thuat toan sap xep noi bot

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

void bubbleSort(recordType a[], int n) {
    int i, j;
    for (i=1; i<n; i++)
        for (j=n-1; j>=i; j--)
            if (a[j].key<a[j-1].key)
                swap(&a[j], &a[j-1]);
}

int main() {
    recordType a[100];
    int n;
    readData(a, &n);
    printf("Thuat toan sap xep noi bot\n\n");
    printf("Du lieu truoc khi sap xep\n");
    printData(a, n);
    bubbleSort(a, n);
    printf("Du lieu sau khi sap xep\n");
    printData(a, n);
    return 0;
}