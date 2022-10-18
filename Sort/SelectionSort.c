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

void SelectionSort(recordtype a[], int n)
{
    int i, j, lowindex;
    keytype lowkey;
    for (i = 0; i <= n - 2; i++)
    {
        lowkey = a[i].key;
        lowindex = i;
        for (j = i + 1; j <= n - 1; j++)
        {
            if (a[j].key < lowkey)
            {
                lowindex = j;
                lowkey = a[j].key;
            }
        }
        Swap(&a[i], &a[lowindex]);
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
    while (fscanf(f, "%d %f\n", &a[n].key, &a[n].otherfields) != EOF)
    {
        n++;
    }
    SelectionSort(a, n);
    show(a, n);
    fclose(f);
    return 0;
}