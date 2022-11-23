// Bai toan cai ba lo 2 quy hoach donh

#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct DoVat {
    char TenDV[50];
    int TL, GT, SL, PA;
} DoVat;

typedef int bang[50][100];


DoVat* readFromFile(int* n, int* W) {
    FILE* f;
    f = fopen("cbl2.txt", "r");
    int i = 0;
    DoVat* dsdv;
    dsdv = (DoVat*)malloc(sizeof(DoVat));
    if (f != NULL) {
        fscanf(f, "%d", W);
        while (!feof(f)) {
            fscanf(f, "%d%d%d %[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].SL, &dsdv[i].TenDV);
            dsdv[i].PA = 0;
            i++;
            dsdv = (DoVat*)realloc(dsdv, sizeof(DoVat) * (i + 1));
        }
    }
    else {
        printf("Loi doc file !!!\n");
    }
    *n = i;
    fclose(f);
    return dsdv;
}

void indsdv(DoVat* dsdv, int n, float w) {
    printf("Bai toan Cai ba lo 2 giai bang thuat toan THAM AN : \n\n");
    printf("|---|--------------------|----------|----------|----------|----------|\n");
    printf("|STT|      Ten Do Vat    | T Luong  | Gia Tri  | So Luong |Phuong An |\n");
    printf("|---|--------------------|----------|----------|----------|----------|\n");
    int i;
    float TongGT = 0, TongTL = 0;
    for (i = 0; i < n; i++) {
        printf("|%2d |%-20s|%-10d|%-10d|%-10d|%-10d|\n", i + 1, dsdv[i].TenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].SL, dsdv[i].PA);
        TongTL += dsdv[i].PA * dsdv[i].TL;
        TongGT += dsdv[i].PA * dsdv[i].GT;
    }
    printf("|---|--------------------|----------|----------|----------|----------|----------|\n");
    printf("Phuong an X(");
    for (i = 0; i < n - 1; i++) {
        printf("%d, ", dsdv[i].PA);
    }
    printf("%d)\n", dsdv[i].PA);
    printf("Trong luong Cai ba lo la: %.2f\n", w);
    printf("Tong trong luong la: %.2f\n", TongTL);
    printf("Tong gia tri la: %.2f\n", TongGT);
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

void taoBang(DoVat* dsdv, int n, int w, bang F, bang X) {
    int v;
    for (v = 0; v <= w; v++) {
        X[0][v] = min(v / dsdv[0].TL, dsdv[0].SL);
        F[0][v] = X[0][v] * dsdv[0].GT;
    }
    int k;
    for (k = 1; k < n; k++) {
        for (v = 0; v <= w; v++) {
            int fmax = F[k - 1][v];
            int xmax = 0;
            int yk = min(dsdv[k].SL, v / dsdv[k].TL);
            int j;
            for (j = 1; j <= yk; j++) {
                if (F[k - 1][v - j * dsdv[k].TL] + j * dsdv[k].GT > fmax) {
                    fmax = F[k - 1][v - j * dsdv[k].TL] + j * dsdv[k].GT;
                    xmax = j;
                }
            }
            F[k][v] = fmax;
            X[k][v] = xmax;
        }
    }
}

void traBang(DoVat* dsdv, int n, int w, bang F, bang X) {
    int v = w;
    int k;
    for (k = n - 1; k >= 0; k--) {
        dsdv[k].PA = X[k][v];
        v -= X[k][v] * dsdv[k].TL;
    }
}

void inBang(DoVat* dsdv, int n, int w, bang F, bang X) {
    int v;
    int k;
    for (k = 0; k < n; k++) {
        for (v = 0; v <= w; v++)
            printf("|%4d%2d", F[k][v], X[k][v]);
        printf("\n");
    }
}

int main() {
    DoVat* dsdv;
    int n, w;
    dsdv = readFromFile(&n, &w);
    bang X, F;
    taoBang(dsdv, n, w, F, X);
    inBang(dsdv, n, w, F, X);
    traBang(dsdv, n, w, F, X);
    indsdv(dsdv, n, w);
    return 0;
}