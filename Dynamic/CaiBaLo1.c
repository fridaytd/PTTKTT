// Cai ba lo 1
// Quy hoach dong

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <limits.h>

typedef struct DoVat {
    char tenDV[100];
    int TL, GT, PA;
} DoVat;

typedef int bang[50][100];

DoVat* readFromFile(int* n, int* W) {
    FILE* f;
    int i=0;
    f=fopen("cbl1.txt", "r");
    DoVat* dsdv;
    dsdv=(DoVat*)malloc(sizeof(DoVat));
    if (f!=NULL) {
        fscanf(f, "%d", W);
        while (!feof(f)) {
            fscanf(f, "%d%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].tenDV);
            dsdv[i].PA=0;
            i++;
            dsdv=(DoVat*)realloc(dsdv, sizeof(DoVat)*(i+1));
        }
    }
    else {
        printf("Loi doc file!!!");
    }
    *n=i;
    fclose(f);
    return dsdv;
}

void inDSDV(DoVat* dsdv, int n, int W) {
    int TongTL=0, TongGT=0;
    int i;
    printf("Danh sach do vat : \n");
    printf("|---|--------------------|----------|----------|----------|\n");
    printf("|STT|    Ten Do Vat      | T Luong  |  G Tri   |   P An   |\n");
    printf("|---|--------------------|----------|----------|----------|\n");
    for (i=0; i<n; i++) {
        printf("| %2d|%-20s|%-10d|%-10d|%-10d|\n", i+1, dsdv[i].tenDV, dsdv[i].TL, dsdv[i].TL, dsdv[i].PA);
        TongTL+=dsdv[i].PA*dsdv[i].TL;
        TongGT+=dsdv[i].PA*dsdv[i].GT;
    }
    printf("|---|--------------------|----------|----------|----------|\n");
    printf("Trong luong cai ba lo la: %d\n", W);
    printf("Tong trong luon la: %d\n", TongTL);
    printf("Tong gia tri la: %d\n", TongGT);
}

void taoBang(DoVat* dsdv, int n, bang F, bang X, int W) {
    int V=W;
    for (V=0; V<=W; V++) {
        X[0][V]=V/dsdv[0].TL;
        F[0][V]=X[0][V]*dsdv[0].GT;
    }
    int k;
    for (k=1; k<n; k++) {
        for (V=0; V<=W; V++) {
            int xk;
            int yk=V/dsdv[k].TL;
            int Fmax=INT_MIN;
            int Xmax;
            for (xk=0; xk<=yk; xk++) {
                if ((F[k-1][V-xk*dsdv[k].TL]+xk*dsdv[k].GT)>Fmax) {
                    Fmax=(F[k-1][V-xk*dsdv[k].TL]+xk*dsdv[k].GT);
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
    int i;
    for (i=n-1; i>=0; i--) {
        dsdv[i].PA=X[i][V];
        V-=dsdv[i].PA*dsdv[i].TL;
    }

}

void inBang(DoVat* dsdv, int n, int W, bang F, bang X) {
    int V;
    int i;
    for (i=0; i<n; i++) {
        for (V=0; V<=W; V++) {
            printf("|%4d%2d ", F[i][V], X[i][V]);
        }
        printf("\n");
    }

}

int main() {
    DoVat* dsdv;
    int n;
    int W;
    dsdv=readFromFile(&n, &W);
    inDSDV(dsdv, n, W);
    bang F, X;
    taoBang(dsdv, n, F, X, W);
    inBang(dsdv, n, W, F, X);
    traBang(dsdv, n, W, F, X);
    inDSDV(dsdv, n, W);
    return 0;
}