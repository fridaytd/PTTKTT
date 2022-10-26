// Bai Toan cai ba lo 1

#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct DoVat
{
    char TenDV[50];
    float TL, GT, DG;
    int PA;
} DoVat;

DoVat *ReadFromFile(float *w, int *n)
{
    FILE *f;
    f = fopen("CaiBaLo1.txt", "r");
    DoVat *dsdv;
    dsdv = (DoVat *)malloc(sizeof(DoVat));
    int i = 0;
    fscanf(f, "%f", w);
    if (f != NULL)
    {
        while (!feof(f))
        {
            fscanf(f, "%f%f%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].TenDV);
            dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
            dsdv[i].PA = 0;
            i++;
            dsdv = (DoVat *)realloc(dsdv, sizeof(DoVat) * (i + 1));
        }
    }
    else
    {
        printf("Loi mo file !!!");
    }
    *n = i;
    fclose(f);
    return dsdv;
}

void Swap(DoVat *a, DoVat *b)
{
    DoVat temp = *a;
    *a = *b;
    *b = temp;
}

void BubbleSort(DoVat *dsdv, int n)
{
    int i, j;
    for (i = 0; i <= n - 2; i++)
        for (j = n - 1; j >= i + 1; j--)
            if (dsdv[j].DG > dsdv[j - 1].DG)
                Swap(&dsdv[j], &dsdv[j - 1]);
}

void InDSDV(DoVat *dsdv, int n, float w)
{
    int i;
    float TongGT = 0, TongTL = 0;
    printf("Phuong an Cai ba lo 1 su dung thuat toan THAM AN nhu sau: \n");
    printf("Trong luong cai ba lo = %-9.2f\n", w);
    printf("|---|------------------|---------|---------|---------|-----------|\n");
    printf("|STT|    Ten Do vat    | T Luong | Gia Tri | Don Gia | Phuong An |\n");
    printf("|---|------------------|---------|---------|---------|-----------|\n");
    for (i = 0; i < n; i++)
    {
        printf("|%2d |%-18s|%-9.2f|%-9.2f|%-9.2f|%6d     |\n", i + 1, dsdv[i].TenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].DG, dsdv[i].PA);
        TongTL += dsdv[i].PA * dsdv[i].TL;
        TongGT += dsdv[i].PA * dsdv[i].GT;
    }
    printf("|---|------------------|---------|---------|---------|-----------|\n");
    printf("Phuong an theo (thu tu don gia giam dan): X(");
    for (i = 0; i < n - 1; i++)
        printf("%d, ", dsdv[i].PA);
    printf("%d)", dsdv[n - 1].PA);
    printf("\nTong trong luong = %-9.2f", TongTL);
    printf("\nTong gia tri = %-9.2f", TongGT);
}

void Greedy(DoVat *dsdv, int n, float w)
{
    int i;
    for (i = 0; i < n; i++)
    {
        dsdv[i].PA = w / dsdv[i].TL;
        w -= dsdv[i].PA * dsdv[i].TL;
    }
}

int main()
{
    int n;
    DoVat *dsdv;
    float w;
    dsdv = ReadFromFile(&w, &n);
    BubbleSort(dsdv, n);
    Greedy(dsdv, n, w);
    InDSDV(dsdv, n, w);
    free(dsdv);
    return 0;
}