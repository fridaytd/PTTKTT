// Bai toan Cai Ba Lo 1, giai bang NHANH CAN
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
    DoVat* ds;
    ds = (DoVat*)malloc(sizeof(DoVat));
    if (f != NULL) {
        fscanf(f, "%f", w);
        while (!feof(f)) {
            fscanf(f, "%f%f%[^\n]", &ds[i].TL, &ds[i].GT, &ds[i].TenDV);
            ds[i].DG = ds[i].GT / ds[i].TL;
            ds[i].PA = 0;
            i++;
            ds = (DoVat*)realloc(ds, sizeof(DoVat) * (i + 1));
        }
    }
    else {
        printf("Loi doc file !!!");
    }
    *n = i;
    fclose(f);
    return ds;
}

void inDS(DoVat* ds, int n, float w) {
    printf("|---|--------------------|----------|----------|----------|----------|\n");
    printf("|STT|      Ten Do Vat    | T Luong  | Gia Tri  | Don Gia  | P  An    |\n");
    printf("|---|--------------------|----------|----------|----------|--------- |\n");
    int i;
    float tongTL = 0, tongGT = 0;
    for (i = 0; i < n; i++) {
        printf("|%2d |%-20s|%-10.2f|%-10.2f|%-10.2f|%-10d|\n", i + 1, ds[i].TenDV, ds[i].TL, ds[i].GT, ds[i].DG, ds[i].PA);
        tongTL += ds[i].PA * ds[i].TL;
        tongGT += ds[i].PA * ds[i].GT;
    }
    printf("|---|--------------------|----------|----------|---------------------|\n");
    printf("Trong luong cai ba lo la: %.2f\n", w);
    printf("Tong Trong luong la: %.2f\n", tongTL);
    printf("Tong Gia tri la: %.2f\n", tongGT);
}

void swap(DoVat* a, DoVat* b) {
    DoVat temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(DoVat* ds, int n) {
    int i, j;
    for (i = 1; i < n; i++)
        for (j = n - 1; j >= i; j--)
            if (ds[j].DG > ds[j - 1].DG)
                swap(&ds[j], &ds[j - 1]);
}

void capNhatPA(DoVat* ds, int n, float* TGT, float* GLNTT, int x[]) {
    if (*TGT > *GLNTT) {
        *GLNTT = *TGT;
        int i;
        for (i = 0; i < n; i++) {
            ds[i].PA = x[i];
        }
    }
}

void nhanhCan(int i, DoVat* ds, int n, float* v, float* TGT, float* CT, float* GLNTT, int x[]) {
    int j;
    j = *v / ds[i].TL;
    int k;
    for (k = j; k >= 0; k--) {
        *TGT += k * ds[i].GT;
        *v -= k * ds[i].TL;
        if (i + 1 <= n - 1)
            *CT = *TGT + *v * ds[i + 1].DG;
        else
            *CT = *TGT;
        if (*CT > *GLNTT) {
            x[i] = k;
            if (i < n - 1) {
                nhanhCan(i + 1, ds, n, v, TGT, CT, GLNTT, x);
            }
            else {
                capNhatPA(ds, n, TGT, GLNTT, x);
            }
        }
        *TGT -= k * ds[i].GT;
        *v += k * ds[i].TL;
    }
}

int main() {
    DoVat* ds;
    int n;
    float w;
    ds = readFromFile(&n, &w);
    float TGT = 0, GLNTT = 0, CT = 0;
    int x[100];
    float v = w;
    bubbleSort(ds, n);
    nhanhCan(0, ds, n, &v, &TGT, &CT, &GLNTT, x);
    inDS(ds, n, w);
    return 0;
}