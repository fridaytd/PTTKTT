// Bai toan Cai Ba Lo 2
// Su dung ky thuat nhanh can
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct DoVat
{
    char TenDV[50];
    float TL, GT, DG;
    int PA, SL;
} DoVat;

DoVat *ReadFromFile(float *w, int *n)
{
    int i = 0;
    FILE *f;
    f = fopen("CBL2.txt", "r");
    DoVat *dsdv;
    dsdv = (DoVat *)malloc(sizeof(DoVat));
    if (f != NULL)
    {
        fscanf(f, "%f", w);
        while (!feof(f))
        {
            fscanf(f, "%f%f%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].SL, dsdv[i].TenDV);
            dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
            dsdv[i].PA = 0;
            i++;
            dsdv = (DoVat *)realloc(dsdv, sizeof(DoVat) * (i + 1));
        }
    }
    else
    {
        printf("Loi doc file!!!");
    }
    *n = i;
    return dsdv;
}

void In_dsdv(DoVat dsdv[], float w, int n)
{
    float TongTL = 0;
    float TongGT = 0;
    printf("Tong trong luong cai ba lo la: %.2f\n", w);
    printf("Bai toan Cai Ba Lo 2 su dung NHANH CAN la:\n\n");
    printf("|---|--------------------|---------|---------|---------|---------|----------|\n");
    printf("|STT|     Ten Do Vat     | TLuong  |  GTri   |  DGia   |  SLuong |   PAn    |\n");
    printf("|---|--------------------|---------|---------|---------|---------|----------|\n");
    int i;
    for (i = 0; i < n; i++)
    {
        printf("|%2d |%-20s|%-9.2f|%-9.2f|%-9.2f|%-9d|%-10d|\n", (i + 1), dsdv[i].TenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].DG, dsdv[i].SL, dsdv[i].PA);
        TongGT += dsdv[i].PA * dsdv[i].GT;
        TongTL += dsdv[i].PA * dsdv[i].TL;
    }
    printf("|---|--------------------|---------|---------|---------|---------|----------|\n");
    printf("Tong trong luong: %.2f\n", TongTL);
    printf("Tong gia tri: %.2f\n", TongGT);
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
    for (i = 0; i < n - 1; i++)
        for (j = n - 1; j >= i + 1; j--)
            if (dsdv[j].DG > dsdv[j - 1].DG)
                Swap(&dsdv[j], &dsdv[j - 1]);
}

float min(float a, float b)
{
    return (a < b) ? a : b;
}

void Tao_Nut_Goc(DoVat dsdv[], float *TGT, float w, float *v, float *CT, float *GLNTT)
{
    *TGT = 0;
    *v = w;
    *GLNTT = 0;
    *CT = *v * dsdv[0].DG;
}

void Cap_nhat_GLNTT(DoVat dsdv[], int n, float *TGT, float *GLNTT, int x[])
{
    int i;
    if (*TGT > *GLNTT)
    {
        *GLNTT = *TGT;
        for (i = 0; i < n; i++)
        {
            dsdv[i].PA = x[i];
        }
    }
}

void Nhanh_Can(int i, DoVat dsdv[], int n, float *TGT, float *v, float *CT, float *GLNTT, int x[])
{
    int yk = min(*v / dsdv[i].TL, dsdv[i].SL);
    int j;
    for (j = yk; j >= 0; j--)
    {
        (*TGT) += j * dsdv[i].GT;
        (*v) -= j * dsdv[i].TL;
        if (i + i <= n)
            (*CT) = *TGT + *v * dsdv[i + 1].DG;
        else
            (*CT) = *TGT;
        if (*CT > *GLNTT)
        {
            x[i] = j;
            if (i == n - 1 || *v == 0)
            {
                Cap_nhat_GLNTT(dsdv, n, TGT, GLNTT, x);
            }
            else
            {
                Nhanh_Can(i + 1, dsdv, n, TGT, v, CT, GLNTT, x);
            }
        }
        x[i] = 0;
        (*TGT) -= j * dsdv[i].GT;
        (*v) += j * dsdv[i].TL;
    }
}

int main()
{
    DoVat *dsdv;
    int n;
    float w;
    float TGT, v, CT, GLNTT;
    int x[100];
    dsdv = ReadFromFile(&w, &n);
    // In_dsdv(dsdv, w, n);

    BubbleSort(dsdv, n);
    Tao_Nut_Goc(dsdv, &TGT, w, &v, &CT, &GLNTT);
    // printf("%f\n", CT);
    Nhanh_Can(0, dsdv, n, &TGT, &v, &CT, &GLNTT, x);
    In_dsdv(dsdv, w, n);
    return 0;
}