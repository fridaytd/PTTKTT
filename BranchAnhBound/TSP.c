#include <stdio.h>
#include <float.h>

typedef struct canh {
    int dau, cuoi;
    int da_dung;
    float do_dai;
} canh;

void readFile(canh a[][100], int* n) {
    FILE* f;
    int k=0;
    f=fopen("tsp.txt", "r");
    if (f!=NULL) {
        fscanf(f, "%d", &k);
        int i, j;
        for (i=0; i<k; i++)
            for (j=0; j<k; j++) {
                fscanf(f, "%f", &a[i][j].do_dai);
                a[i][j].dau=i;
                a[i][j].cuoi=j;
                a[i][j].da_dung=0;
            }
    }
    else {
        printf("Loi doc file!!!");
    }
    *n=k;
    fclose(f);
}

void inMaTran(canh a[][100], int n) {
    printf("Ma tran trong so cua do thi la: \n");
    int i, j;
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++)
            printf("%c%c = %.2f ", i+97, j+97, a[i][j].do_dai);
        printf("\n");
    }
}

float canhNN(canh a[][100], int n) {
    float Cmin=FLT_MAX;
    int i, j;
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            if (i!=j&&!a[i][j].da_dung&&a[i][j].do_dai<Cmin)
                Cmin=a[i][j].do_dai;
    return Cmin;
}

float canDuoi(canh a[][100], int n, int i, float TGT) {
    return TGT+(n-i)*canhNN(a, n);
}

void capNhatPhuongAn(canh a[][100], int n, float TGT, float* GNNTT, canh x[], canh PA[]) {
    x[n-1]=a[x[n-2].cuoi][x[0].dau];
    TGT+=x[n-1].do_dai;
    if (TGT<*GNNTT) {
        *GNNTT=TGT;
        int i;
        for (i=0; i<n; i++) {
            PA[i]=x[i];
        }
    }
}

int laChuTrinh(canh x[], int k, int canhTiepTheo) {
    int i;
    for (i=0; i<k; i++)
        if (x[i].dau==canhTiepTheo)
            return 1;
    return 0;
}

void NhanhCan(int i, canh a[][100], int n, int dau, float* TGT, float* CD, float* GNNTT, canh x[], canh PA[]) {
    int j; // canh tiep theo
    for (j=0; j<n; j++) {
        if (j!=dau&&!a[dau][j].da_dung&&!laChuTrinh(x, i, j)) {
            *TGT+=a[dau][j].do_dai;
            *CD=canDuoi(a, n, i+1, *TGT);
            if (*CD<*GNNTT) {
                x[i]=a[dau][j];
                a[dau][j].da_dung=1;
                a[j][dau].da_dung=1;
                if (i==n-2) {
                    capNhatPhuongAn(a, n, *TGT, GNNTT, x, PA);
                }
                else {
                    NhanhCan(i+1, a, n, j, TGT, CD, GNNTT, x, PA);
                }
            }
            *TGT-=a[dau][j].do_dai;
            a[j][dau].da_dung=0;
            a[dau][j].da_dung=0;
        }
    }
}

void inPA(canh PA[], int n, float GNNTT) {
    printf("Phuong an tim duoc la: \n");
    int i;
    for (i=0; i<n; i++)
        printf("%c%c = %.2f\n", PA[i].dau+97, PA[i].cuoi+97, PA[i].do_dai);
    printf("Duong di: ");
    for (i=0; i<n; i++)
        printf("%c -> ", PA[i].dau+97);
    printf("%c\n", PA[n-1].cuoi+97);
    printf("Chieu dai duong di: %.2f\n", GNNTT);
}

int main() {
    canh a[100][100];
    int n;
    readFile(a, &n);
    inMaTran(a, n);
    float TGT, CD, GNNTT=FLT_MAX;
    canh x[100], PA[100];
    NhanhCan(0, a, n, 0, &TGT, &CD, &GNNTT, x, PA);
    inPA(PA, n, GNNTT);
    return 0;
}