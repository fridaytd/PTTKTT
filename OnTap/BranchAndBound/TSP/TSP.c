// Bai toan TSP giai bang NHANH CAN
#include <stdio.h>
#include <float.h>

typedef struct canh {
    int dau, cuoi;
    float dodai;
    int daDung;
} canh;

void readFile(canh a[][100], int* n) {
    FILE* f;
    f = fopen("tsp.txt", "r");
    fscanf(f, "%d", n);
    int i, j;
    for (i = 0; i < *n; i++)
        for (j = 0; j < *n; j++) {
            fscanf(f, "%f", &a[i][j].dodai);
            a[i][j].dau = i;
            a[i][j].cuoi = j;
            a[i][j].daDung = 0;
        }
}

void inMaTran(canh a[][100], int n) {
    printf("Ma tran dinh: \n");
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%c%c=%.2f ", i + 97, j + 97, a[i][j].dodai);
        }
        printf("\n");
    }
}

float canhNN(canh a[][100], int n) {
    float min = FLT_MAX;
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (i != j && a[i][j].daDung == 0 && a[i][j].dodai < min)
                min = a[i][j].dodai;
    return min;
}

float canDuoi(canh a[][100], int n, int i, float* TGT) {
    return *TGT + (n - i) * canhNN(a, n);
}

int laChuTrinh(canh x[], int i, int j) {
    int k;
    for (k = 0; k < i; k++) {
        if (x[k].dau == j)
            return 1;
    }
    return 0;
}

void capNhatPA(canh a[][100], int n, float TGT, float* GNNTT, canh x[], canh PA[]) {
    x[n - 1] = a[x[n - 2].cuoi][x[0].dau];
    TGT += x[n - 1].dodai;
    if (TGT < *GNNTT) {
        *GNNTT = TGT;
        int i;
        for (i = 0; i < n; i++)
            PA[i] = x[i];
    }
}

void nhanhCan(int i, canh a[][100], int n, int dau, float* TGT, float* CD, float* GNNTT, canh x[], canh PA[]) {
    int j;
    for (j = 0; j < n; j++) {
        if (j != dau && a[dau][j].daDung == 0 && !laChuTrinh(x, i, j)) {
            *TGT += a[dau][j].dodai;
            *CD = canDuoi(a, n, i + 1, TGT);
            if (*CD < *GNNTT) {
                x[i] = a[dau][j];
                a[dau][j].daDung = 1;
                a[j][dau].daDung = 1;
                if (i == n - 2)
                    capNhatPA(a, n, *TGT, GNNTT, x, PA);
                else
                    nhanhCan(i + 1, a, n, j, TGT, CD, GNNTT, x, PA);
            }
            *TGT -= a[dau][j].dodai;
            a[dau][j].daDung = 0;
            a[j][dau].daDung = 0;
        }
    }
}

void inPA(canh PA[], int n, float GNNTT) {
    printf("Duong di tim duoc la: %c", PA[0].dau + 97);
    int i;
    for (i = 0; i < n; i++)
        printf(" -> %c", PA[i].cuoi + 97);
    printf("\nChieu dai duong di la: %.2f", GNNTT);
}

void reset(canh a[][100], int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            a[i][j].daDung = 0;
}

int main() {
    canh a[100][100];
    int n;
    readFile(a, &n);
    inMaTran(a, n);
    while (1) {
        fflush(stdin);
        printf("Nhap dinh xuat phat: \n");
        char m;
        scanf("%c", &m);
        getchar();
        float TGT = 0, CD = 0, GNNTT = FLT_MAX;
        canh x[100], PA[100];
        nhanhCan(0, a, n, m - 97, &TGT, &CD, &GNNTT, x, PA);
        inPA(PA, n, GNNTT);
        fflush(stdin);
        printf("\nTiep tuc ?? (y/n)");
        char k;
        scanf("%c", &k);
        getchar();
        if (k != 'y')
            break;
        reset(a, n);
    }

    return 0;
}