// Bai toan Cai ba lo 2 giai bang thuat toan tham an.

#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct DoVat {
    char TenDV[50];
    float TL, GT, DG;
    int PA, SL;
} DoVat;

DoVat* readFromFile(int* n, float* w) {
    FILE* f;
    f = fopen("cbl2_data.txt", "r");
    DoVat* dsdv;
    dsdv = (DoVat*)malloc(sizeof(DoVat));
    int i = 0;
    if (f != NULL) {
        fscanf(f, "%f", w);
        while (!feof(f)) {
            fscanf(f, "%f%f%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].SL, &dsdv[i].TenDV);
            dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
            dsdv[i].PA = 0;
            i++;
            dsdv = (DoVat*)realloc(dsdv, sizeof(DoVat) * (i + 1));
        }
    }
    else {
        printf("Loi doc file !!!");
    }
    *n = i;
    fclose(f);
    return dsdv;
}

void indsdv(DoVat* dsdv, int n, float w) {
    printf("Bai toan Cai ba lo 2 giai bang thuat toan THAM AN : \n\n");
    printf("|---|--------------------|----------|----------|----------|----------|----------|\n");
    printf("|STT|      Ten Do Vat    | T Luong  | Gia Tri  | Don Gia  | So Luong |Phuong An |\n");
    printf("|---|--------------------|----------|----------|----------|----------|----------|\n");
    int i;
    float TongGT = 0, TongTL = 0;
    for (i = 0; i < n; i++) {
        printf("|%2d |%-20s|%-10.2f|%-10.2f|%-10.2f|%-10d|%-10d|\n", i + 1, dsdv[i].TenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].DG, dsdv[i].SL, dsdv[i].PA);
        TongTL += dsdv[i].PA * dsdv[i].TL;
        TongGT += dsdv[i].PA * dsdv[i].GT;
    }
    printf("|---|--------------------|----------|----------|----------|----------|----------|\n");
    printf("Phuong an sap xep theo thu tu don gia giam dan la: X(");
    for (i = 0; i < n - 1; i++) {
        printf("%d, ", dsdv[i].PA);
    }
    printf("%d)\n", dsdv[i].PA);
    printf("Trong luong Cai ba lo la: %.2f\n", w);
    printf("Tong trong luong la: %.2f\n", TongTL);
    printf("Tong gia tri la: %.2f\n", TongGT);
}

void swap(DoVat* a, DoVat* b) {
    DoVat temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(DoVat* dsdv, int n) {
    int i, j;
    for (i = 1; i < n; i++)
        for (j = n - 1; j >= i; j--)
            if (dsdv[j].DG > dsdv[j - 1].DG)
                swap(&dsdv[j], &dsdv[j - 1]);
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

void greedy(DoVat* dsdv, int n, float w) {
    float v = w;
    int i = 0;
    while (i < n && v >= 0) {
        dsdv[i].PA = min(dsdv[i].SL, v / dsdv[i].TL);
        v -= dsdv[i].PA * dsdv[i].TL;
        i++;
    }
}

int main() {
    DoVat* dsdv;
    int n;
    float w;
    dsdv = readFromFile(&n, &w);
    bubbleSort(dsdv, n);
    greedy(dsdv, n, w);
    indsdv(dsdv, n, w);
    return 0;
}