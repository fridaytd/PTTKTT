// Bai toan TSP giai bang tham an

#include <stdio.h>

typedef struct canh {
    int dau, cuoi;
    float doDai;
} canh;

void readFile(canh* dsc, int* n) {
    FILE* f;
    f = fopen("TSP.txt", "r");
    int t = 0;
    if (f != NULL) {
        fscanf(f, "%d", n);
        int i, j;
        for (i = 0; i < *n; i++) {
            for (j = 0; j < *n; j++) {
                float k;
                fscanf(f, "%f", &k);
                if (i < j) {
                    dsc[t].dau = i;
                    dsc[t].cuoi = j;
                    dsc[t].doDai = k;
                    t++;
                }
            }
        }
    }
    else {
        printf("Loi doc file !!!");
    }
}

void inDSC(canh* dsc, int n) {
    int t = n * (n - 1) / 2;
    int i;
    for (i = 0; i < t; i++) {
        printf("%c%c = %.2f\n", dsc[i].dau + 97, dsc[i].cuoi + 97, dsc[i].doDai);
    }
}

void swap(canh* a, canh* b) {
    canh temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(canh* dsc, int n) {
    int k = n * (n - 1) / 2;
    int i, j;
    for (i = 1; i < k; i++)
        for (j = k - 1; j >= i; j--)
            if (dsc[j].doDai < dsc[j - 1].doDai)
                swap(&dsc[j], &dsc[j - 1]);
}


void initForest(int* parent, int n) {
    int i;
    for (i = 0; i < n; i++)
        parent[i] = i;
}

int findRoot(int* parent, int k) {
    while (k != parent[k]) {
        k = parent[k];
    }
    return k;
}

int isSameRoot(int* parent, int a, int b) {
    return (findRoot(parent, a) == findRoot(parent, b));
}

void updateRoot(int* parent, int a, int b) {
    parent[b] = a;
}

int laDinhCap3(canh* PA, int k, canh t) {
    int i;
    int count = 1;
    for (i = 0; i < k; i++)
        if (t.dau == PA[i].dau || t.dau == PA[i].cuoi)
            count++;

    if (count >= 3) {
        return 1;
    }

    count = 1;
    for (i = 0; i < k; i++)
        if (t.cuoi == PA[i].dau || t.cuoi == PA[i].cuoi)
            count++;
    return count >= 3;
}

void greedy(canh* dsc, int n, canh PA[], int parent[]) {
    initForest(parent, n);
    bubbleSort(dsc, n);
    int count = 0;
    int i;
    for (i = 0; i < n * (n - 1) / 2; i++) {
        if (!laDinhCap3(PA, count, dsc[i]) && !isSameRoot(parent, dsc[i].dau, dsc[i].cuoi)) {
            PA[count] = dsc[i];
            count++;
            updateRoot(parent, findRoot(parent, dsc[i].dau), findRoot(parent, dsc[i].cuoi));
        }
        if (count == n - 1)
            break;
    }
    for (; i < n * (n - 1) / 2; i++) {
        if (!laDinhCap3(PA, count, dsc[i]) && isSameRoot(parent, dsc[i].dau, dsc[i].cuoi)) {
            PA[count] = dsc[i];
            count++;
            updateRoot(parent, findRoot(parent, dsc[i].dau), findRoot(parent, dsc[i].cuoi));
            break;
        }
    }
}


void inPA(canh* PA, int n, int* parent) {
    printf("Danh sach phuong an: \n");
    float sum = 0;
    int i;
    for (i = 0; i < n; i++)
        printf("%c%c = %.2f\n", PA[i].dau + 97, PA[i].cuoi + 97, PA[i].doDai);
    printf("Duong di tim duoc la: ");
    int mark[100];
    for (i = 0; i < n; i++)
        mark[i] = 0;
    printf("%c -> %c", PA[0].dau + 97, PA[0].cuoi + 97);
    mark[0] = 1;
    int k = PA[0].cuoi;
    for (i = 2; i <= n; i++) {
        int j;
        for (j = 0; j < n; j++) {
            if (k == PA[j].dau && mark[j] == 0) {
                printf(" -> %c", PA[j].cuoi + 97);
                k = PA[j].cuoi;
                mark[j] = 1;
            }
            else if (k == PA[j].cuoi && mark[j] == 0) {
                printf(" -> %c", PA[j].dau + 97);
                k = PA[j].dau;
                mark[j] = 1;
            }
        }
    }
    for (i = 0; i < n; i++)
        sum += PA[i].doDai;
    printf("\nTong chieu dai duong di la: %.2f", sum);
}

int main() {
    canh dsc[100];
    int n;
    readFile(dsc, &n);
    printf("Bai toan TSP giai bang THAM AN la: \n");
    printf("Danh sach canh truoc khi sap xep la: \n");
    inDSC(dsc, n);
    canh PA[100];
    int parent[100];
    greedy(dsc, n, PA, parent);
    printf("Danh sach canh sau khi sap xep la: \n");
    inDSC(dsc, n);
    inPA(PA, n, parent);
    return 0;
}