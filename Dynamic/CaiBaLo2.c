// Cai ba lo 2
// Quy hoach dong

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <limits.h>

typedef struct DoVat {
    char TenDV[50];
    int TL, GT, SL, PA;
} DoVat;

typedef int bang[50][100];

DoVat* readFromFile(int* n, int* W) {
    FILE* f;
    f=fopen("cbl2.txt", "r");
    int i=0;
    DoVat* dsdv;
    dsdv=(DoVat*)malloc(sizeof(DoVat));
    if (f!=NULL) {
        fscanf(f, "%d", W);
        while (!feof(f)) {
            fscanf(f, "%d%d%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].SL, &dsdv[i].TenDV);
            dsdv[i].PA=0;
            i++;
            dsdv=(DoVat*)realloc(dsdv, sizeof(DoVat)*(i+1));
        }
    }
    else {
        printf("Loi doc file !!!\n");
    }
    *n=i;
    fclose(f);
    return dsdv;
}

void inDSDV(DoVat* dsdv, int n, int W) {
    printf("Danh sach do vat \n\n");
    int TongGT=0, TongTL=0;
    int i;
    printf("|---|--------------------|----------|----------|----------|----------|\n");
    printf("|STT|    Ten Do  Vat     | T Luong  |  Gia Tri | So Luong | Phuong An|\n");
    printf("|---|--------------------|----------|----------|----------|----------|\n");
    for (i=0; i<n; i++) {
        printf("|%2d |%-20s|%-10d|%-10d|%-10d|%-10d|\n", i+1, dsdv[i].TenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].SL, dsdv[i].PA);
        TongTL+=dsdv[i].PA*dsdv[i].TL;
        TongGT+=dsdv[i].PA*dsdv[i].GT;
    }
    printf("|---|--------------------|----------|----------|----------|----------|\n");
    printf("Trong luong cai ba lo la: %d\n", W);
    printf("Tong trong luong la: %d\n", TongTL);
    printf("Tong gia tri la: %d\n", TongGT);
}

int min(int a, int b) {
    return (a<b)?a:b;
}

void taoBang(DoVat* dsdv, int n, int W, bang F, bang X) {
    int V;
    for (V=0; V<=W; V++) {
        X[0][V]=min(V/dsdv[0].TL, dsdv[0].SL);
        F[0][V]=X[0][V]*dsdv[0].GT;
    }
    int k;
    for (k=1; k<n; k++) {
        for (V=0; V<=W; V++) {
            int yk=min(V/dsdv[k].TL, dsdv[k].SL);
            int Fmax=INT_MIN;
            int Xmax;
            int xk;
            for (xk=0; xk<=yk; xk++) {
                if ((F[k-1][V-xk*dsdv[k].TL]+xk*dsdv[k].GT)>Fmax) {
                    Fmax=F[k-1][V-xk*dsdv[k].TL]+xk*dsdv[k].GT;
                    Xmax=xk;
                }
            }
            F[k][V]=Fmax;
            X[k][V]=Xmax;
        }
    }
}

void traBang(DoVat* dsdv, int n, int W, bang F, bang X) {
    int V=W;
    int k;
    for (k=n-1; k>=0; k--) {
        dsdv[k].PA=X[k][V];
        V-=dsdv[k].PA*dsdv[k].TL;
    }
}

void inBang(DoVat* dsdv, int n, int W, bang F, bang X) {
    int V;
    int k;
    for (k=0; k<n; k++) {
        for (V=0; V<=W; V++) {
            printf("|%4d%2d ", F[k][V], X[k][V]);
        }
        printf("\n");
    }
}

int main() {
    DoVat* dsdv;
    int n, W;
    dsdv=readFromFile(&n, &W);
    bang X, F;
    taoBang(dsdv, n, W, F, X);
    inBang(dsdv, n, W, F, X);
    traBang(dsdv, n, W, F, X);
    inDSDV(dsdv, n, W);
    return 0;
}