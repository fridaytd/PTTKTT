// Thuat toan sap xep nhanh 

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
        printf("%3d%5d%7.2f\n", i+1, a[i].key, a[i].otherFields);
    }
}

int findPivot(recordType a[], int f, int l) {
    int i=f+1;
    while (i<=l&&a[f].key==a[i].key) {
        i++;
    }
    if (i>l)
        return -1;
    else
        return (a[f].key>a[i].key)?f:i;
}

int partition(recordType a[], int f, int l, keyType pivot) {
    int L=f;
    int R=l;
    while (L<R) {
        while (a[L].key<pivot)
            L++;
        while (a[R].key>=pivot)
            R--;
        if (L<R)
            swap(&a[L], &a[R]);
    }
    return L;
}

void quickSort(recordType a[], int f, int l) {
    int indexPivot=findPivot(a, f, l);
    if (indexPivot!=-1) {
        int pivot=a[indexPivot].key;
        int k=partition(a, f, l, pivot);
        quickSort(a, f, k-1);
        quickSort(a, k, l);
    }
}

int main() {
    recordType a[100];
    int n;
    readData(a, &n);
    printf("Thuat toan Quick Sort\n\n");
    printf("Du lieu truoc khi sap xep: \n");
    printData(a, n);
    quickSort(a, 0, n-1);
    printf("Du lieu sau khi sap xep: \n");
    printData(a, n);
    return 0;
}