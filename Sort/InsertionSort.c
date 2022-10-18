#include <stdio.h>

typedef int keytype;
typedef float othertype;
typedef struct
{
    keytype key;
    othertype otherfields;
} recordtype;

void Swap(recordtype *a, recordtype *b)
{
    recordtype temp = *a;
    *a = *b;
    *b = temp;
}

void InsertionSort(recordtype a[], int n)
{
    int i, j;
    for (i = 1; i <= n - 1; i++)
    {
        j = i;
        while (j > 0 && a[j].key < a[j - 1].key)
        {
            Swap(&a[j], &a[j - 1]);
            j--;
        }
    }
}

void show(recordtype a[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d %f\n", a[i].key, a[i].otherfields);
}

int main()
{
    FILE *f;
    f = fopen("data.txt", "r");
    recordtype a[100];
    int n = 0;
    while (fscanf(f, "%d %f", &a[n].key, &a[n].otherfields) != EOF)
    {
        n++;
    }
    InsertionSort(a, n);
    show(a, n);
    fclose(f);
    return 0;
}