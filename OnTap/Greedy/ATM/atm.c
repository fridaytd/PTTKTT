// Bai toan ATM giat bang thuat toan THAM AM

#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct tien {
    char tenTien[50];
    int MG, PA;
} tien;

tien* readFromFile(int* n) {
    FILE* f;
    f = fopen("atm_data.txt", "r");
    tien* dst;
    dst = (tien*)malloc(sizeof(tien));
    int i = 0;
    if (f != NULL) {
        while (!feof(f)) {
            fscanf(f, "%d%[^\n]", &dst[i].MG, &dst[i].tenTien);
            dst[i].PA = 0;
            i++;
            dst = (tien*)realloc(dst, sizeof(tien) * (i + 1));
        }
    }
    else {
        printf("Loi doc file !!!\n");
    }
    *n = i;
    fclose(f);
    return dst;
}

void inTien(tien* dst, int n, int tienCanRut) {
    printf("Bai toan ATM giat bang thuat toan THAM AN\n\n");
    printf("|---|-------------------------|----------|----------|---------------|\n");
    printf("|STT|         Ten Tien        | Menh Gia |   So To  |   Thanh Tien  |\n");
    printf("|---|-------------------------|----------|----------|---------------|\n");
    int tienDaTra = 0;
    int i;
    for (i = 0; i < n; i++) {
        printf("|%2d |%-25s|%-10d|%-10d|%-15d|\n", i + 1, dst[i].tenTien, dst[i].MG, dst[i].PA, dst[i].PA * dst[i].MG);
        tienDaTra += dst[i].PA * dst[i].MG;
    }
    printf("|---|-------------------------|----------|----------|---------------|\n");
    printf("So tien can rut la: %d\n", tienCanRut);
    printf("so tien da tra la: %d\n", tienDaTra);
}

void swap(tien* a, tien* b) {
    tien temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(tien* dst, int n) {
    int i, j;
    for (i = 1; i < n; i++)
        for (j = n - 1; j >= i; j--)
            if (dst[j].MG > dst[j - 1].MG)
                swap(&dst[j], &dst[j - 1]);
}

void greedy(tien* dst, int n, int tienCanRut) {
    int i = 0;
    while (i < n && tienCanRut >= 0) {
        dst[i].PA = tienCanRut / dst[i].MG;
        tienCanRut -= dst[i].PA * dst[i].MG;
        i++;
    }
}

int main() {
    tien* dst;
    int n, tienCanRut;
    dst = readFromFile(&n);
    printf("Nhap so tien can rut: \n");
    scanf("%d", &tienCanRut);
    bubbleSort(dst, n);
    greedy(dst, n, tienCanRut);
    inTien(dst, n, tienCanRut);
    return 0;
}