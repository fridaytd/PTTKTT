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

void Read_Data(recordtype a[], int *n)
{
	FILE *f;
	f = fopen("data.txt", "r");
	int i = 0;
	if (f != NULL)
	{
		while(!feof(f))
		{
			fscanf(f, "%d %f", &a[i].key, &a[i].otherfields);
			i++;
		}
	}
	else 
		printf("Loi mo file");
	fclose(f);
	*n = i;
}

void Print_Data(recordtype a[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%3d%5d%8.2f\n", i + 1, a[i].key, a[i].otherfields);
	}
}

int main()
{
	recordtype a[100];
	int n;
	printf("Thuat toan Selection Sort \n\n");
	Read_Data(a, &n);
	printf("Du lieu truoc khi sap xep\n");
	Print_Data(a, n);
	SelectionSort(a, n);
	printf("\nDu lieu sau khi sap xep\n");
	Print_Data(a, n);
    return 0;
}
