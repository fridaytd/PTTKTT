// Bai toan Cai Ba Lo 2 sư dung NHANH CAN 
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct DoVat {
    char TenDV[50];
    float TL, GT, DG;
    int SL, PA;
} DoVat;

DoVat* readFromFile(int* n, float* w) {
    FILE* f;
    f = fopen("cbl2_data.txt", "r");
    DoVat* ds;
    ds = (DoVat*)malloc(sizeof(DoVat));
    int i = 0;
    fscanf(f, "%f", w);
    while (!feof(f)) {
        fscanf(f, "%f%f%d%[^\n]", &ds[i].TL, &ds[i].GT, &ds[i].SL, &ds[i].TenDV);
        ds[i].DG = ds[i].GT / ds[i].TL;
        ds[i].PA = 0;
        i++;
        ds = (DoVat*)realloc(ds, sizeof(DoVat) * (i + 1));
    }
    *n = i;
    fclose(f);
    return ds;
}

void inDS(DoVat* ds, int n, float w) {
    float tongTL = 0, tongGT = 0;
    printf("|---|--------------------|----------|----------|----------|----------|---------|\n");
    printf("|STT|    Ten Do Vat      | T Luong  |  Gia Tri |  Don Gia | S Luong  |   P  An |\n");
    printf("|---|--------------------|----------|----------|----------|----------|---------|\n");
    int i;
    for (i = 0; i < n; i++) {
        printf("|%2d |%-20s|%-10.2f|%-10.2f|%-10.2f|%-10d|%-10d|\n", i + 1, ds[i].TenDV, ds[i].TL, ds[i].GT, ds[i].DG, ds[i].SL, ds[i].PA);
        tongTL += ds[i].PA * ds[i].TL;
        tongGT += ds[i].PA * ds[i].GT;
    }
    printf("|---|--------------------|----------|----------|----------|----------|---------|\n");
    printf("Phuong an sap xep theo don gia giam dan la: X(");
    for (i = 0; i < n - 1; i++)
        printf("%d, ", ds[i].PA);
    printf("%d)\n", ds[n - 1].PA);
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

int min(int a, int b) {
    return (a < b) ? a : b;
}

void taoNutGoc(DoVat* ds, int n, float* TGT, float* v, float w, float* GLNTT, float* CT) {
    *TGT = 0;
    *v = w;
    *GLNTT = 0;
    *CT = *v * ds[0].DG;
}

void capNhatPA(DoVat* ds, int n, float* TGT, float* GLNTT, int x[]) {
    if (*TGT > *GLNTT) {
        *GLNTT = *TGT;
        int i;
        for (i = 0; i < n; i++)
            ds[i].PA = x[i];
    }
}

void nhanhCan(int i, DoVat* ds, int n, float* v, float* TGT, float* GLNTT, float* CT, int x[]) {
    int j;
    j = min(ds[i].SL, *v / ds[i].TL);
    int k;
    for (k = j; k >= 0; k--) {
        *TGT += k * ds[i].GT;
        *v -= k * ds[i].TL;
        if (i + 1 < n) {
            *CT = *TGT + *v * ds[i + 1].DG;
        }
        else {
            *CT = *TGT;
        }
        if (*CT > *GLNTT) {
            x[i] = k;
            if (i < n - 1) {
                nhanhCan(i + 1, ds, n, v, TGT, GLNTT, CT, x);
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
    float v = w, TGT = 0, GLNTT = 0, CT = 0;
    int x[100];
    bubbleSort(ds, n);
    taoNutGoc(ds, n, &TGT, &v, w, &GLNTT, &CT);
    nhanhCan(0, ds, n, &v, &TGT, &GLNTT, &CT, x);
    inDS(ds, n, w);
    return 0;
}