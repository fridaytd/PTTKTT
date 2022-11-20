// Thuat toan sap xep Heap sort

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
        printf("Loi doc file");
    }
    *n=i;
    fclose(f);
}

void printData(recordType a[], int n) {
    int i;
    for (i=0; i<n; i++) {
        printf("%3d %5d %8.2f\n", i+1, a[i].key, a[i].otherFields);
    }
}

void pushDown(recordType a[], int first, int last) {
    int r=first;
    while (2*r+1<=last) {
        if (2*r+1==last) {
            if (a[r].key>a[last].key)
                swap(&a[r], &a[last]);
            r=last;
        }
        else if (a[r].key>a[2*r+1].key&&a[2*r+1].key<=a[2*r+2].key) {
            swap(&a[r], &a[2*r+1]);
            r=2*r+1;
        }
        else if (a[r].key>a[2*r+2].key&&a[2*r+2].key<a[2*r+1].key) {
            swap(&a[r], &a[2*r+2]);
            r=2*r+2;
        }
        else {
            break;
        }
    }
}

void heapSort(recordType a[], int n) {
    int i;
    for (i=(n-2)/2; i>=0; i--)
        pushDown(a, i, n-1);
    for (i=n-1; i>0; i--) {
        swap(&a[0], &a[i]);
        pushDown(a, 0, i-1);
    }
    swap(&a[0], &a[1]);
}

int main() {
    recordType a[100];
    int n;
    readData(a, &n);
    printf("Thuat toan Heap Sort\n\n");
    printf("Du lieu truoc khi sap xep:\n");
    printData(a, n);
    heapSort(a, n);
    printf("Du lieu sau khi sap xep:\n");
    printData(a, n);
    return 0;
}