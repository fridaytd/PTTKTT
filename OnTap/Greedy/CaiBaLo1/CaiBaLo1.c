#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct DoVat {
    char TenDV[50];
    float TL, GT, DG;
    int PA;
} DoVat;

DoVat* readFromFile(int* n, float* w) {
    FILE* f;
    f = fopen("cbl1_data.txt", "r");
    int i = 0;
    DoVat* dsdv;
    dsdv = (DoVat*)malloc(sizeof(DoVat));
    if (f != NULL) {
        fscanf(f, "%f", w);
        while (!feof(f)) {
            fscanf(f, "%f%f%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].TenDV);
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
    return dsdv;
    fclose(f);
}

void indsdv(DoVat* dsdv, int n, float w) {
    printf("Danh sach do vat: \n");
    printf("|---|--------------------|----------|----------|----------|----------|\n");
    printf("|STT|     Ten Do Vat     | T Luong  |  Gia Tri |  Don Gia | Phuong An|\n");
    printf("|---|--------------------|----------|----------|----------|----------|\n");
    int i;
    float TongTL = 0, TongGT = 0;
    for (i = 0; i < n; i++) {
        printf("|%2d |%-20s|%-10.2f|%-10.2f|%-10.2f|%-10d|\n", i + 1, dsdv[i].TenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].DG, dsdv[i].PA);
        TongTL += dsdv[i].PA * dsdv[i].TL;
        TongGT += dsdv[i].PA * dsdv[i].GT;
    }
    printf("|---|--------------------|----------|----------|----------|----------|\n");
    printf("Phuong an sap xep theo thu tu don gia giam dan la: X(");
    for (i = 0; i < n - 1; i++)
        printf("%d, ", dsdv[i].PA);
    printf("%d)\n", dsdv[n - 1].PA);
    printf("Trong luong cai ba lo la: %.2f\n", w);
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

void greedy(DoVat* dsdv, int n, float w) {
    float v = w;
    int i = 0;
    while (i < n && v >= 0) {
        dsdv[i].PA = v / dsdv[i].TL;
        v -= dsdv[i].PA * dsdv[i].TL;
        i++;
    }
}

int main() {
    DoVat* dsdv;
    int n;
    float w;
    dsdv = readFromFile(&n, &w);
    printf("Greedy: Cai Ba Lo 1\n");
    bubbleSort(dsdv, n);
    greedy(dsdv, n, w);
    indsdv(dsdv, n, w);
    return 0;
}