// TSP 

#include <stdio.h>

typedef struct canh
{
	float do_dai;
	int dau, cuoi;
} canh;

void readFile(char fileName[], canh ds_canh[], int *n, int *so_canh)
{
	FILE *f;
	f = fopen(fileName, "r");
	if (f == NULL)
	{
		printf("Loi doc file !!!");
		return;
	}
	fscanf(f, "%d", n);
	int i, j;
	float d;
	int k = 0;
	for (i = 0; i < *n; i++)
		for (j = 0; j < *n; j++)
		{
			fscanf(f, "%f", &d);
			if (i < j) 
			{
				ds_canh[k].dau = i;
				ds_canh[k].cuoi = j;
				ds_canh[k].do_dai = d;
				k++;
			}
				
		}
	*so_canh = k;
}

void InDS_canh(canh ds_canh[], int n, int k)
{
	int i;
	for (i = 0; i < k; i++)
		printf("%3d. %c%c = %.2f\n", i+1, ds_canh[i].dau + 97, ds_canh[i].cuoi + 97, ds_canh[i].do_dai);
}

void Swap(canh *a, canh *b)
{
	canh temp = *a;
	*a = *b;
	*b = temp;
}

void BubbleSort(canh ds_canh[], int k)
{
	int i, j;
	for (i = 0; i <= k - 2; i++)
		for (j = k - 1; j >= i + 1; j--)
			if (ds_canh[j].do_dai < ds_canh[j - 1].do_dai)
				Swap(&ds_canh[j], &ds_canh[j - 1]);
}

int dinh_cap3(canh PA[], int k, canh moi)
{
	int i = 0;
	int dem = 1;
	while (i < k && dem < 3)
	{
		if (moi.dau == PA[i].dau || moi.dau == PA[i].cuoi)
			dem ++;
		i++;
	}
	if (dem == 3) 
		return 1;
	i = 0;
	dem = 1;
	while (i < k && dem < 3)
	{
		if (moi.cuoi == PA[i].dau || moi.cuoi == PA[i].cuoi)
			dem ++;
		i++;
	}
	return dem == 3;
}

void init_forest(int parent[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		parent[i] = i;
}

int find_root(int parent[], int u)
{
	while (u != parent[u])
		u = parent[u];
	return u;
}

int chu_trinh(int r_dau, int r_cuoi)
{
	return r_dau == r_cuoi;
}

void update_forest(int parent[], int r1, int r2)
{
	parent[r2] = r1;
}

void Greedy(canh ds_canh[], int n, int k, canh PA[], int *k_PA)
{
	BubbleSort(ds_canh, k);
	int parent[50];
	init_forest(parent, n);
	int t = 0;
	int i;
	for (i = 0; i < k; i++)
	{
		if (!dinh_cap3(PA, t, ds_canh[i]) && !chu_trinh(find_root(parent, ds_canh[i].dau), find_root(parent, ds_canh[i].cuoi)))
		{
			update_forest(parent, find_root(parent, ds_canh[i].dau), find_root(parent, ds_canh[i].cuoi));
			PA[t].dau = ds_canh[i].dau;
			PA[t].cuoi = ds_canh[i].cuoi;
			PA[t].do_dai = ds_canh[i].do_dai;
			t++;
		}
		if (t == n - 1)
			break;
	}
	
	for (;i < k; i++)
		if (!dinh_cap3(PA, t, ds_canh[i]) && chu_trinh(find_root(parent, ds_canh[i].dau), find_root(parent, ds_canh[i].cuoi)))
		{
			update_forest(parent, find_root(parent, ds_canh[i].dau), find_root(parent, ds_canh[i].cuoi));
			PA[t].dau = ds_canh[i].dau;
			PA[t].cuoi = ds_canh[i].cuoi;
			PA[t].do_dai = ds_canh[i].do_dai;
			t++;
			break;
		}
	*k_PA = t;
}

float TongDoDaiDuongDi(canh ds_canh[], int k)
{
	float s = 0;
	int i;
	for (i = 0; i < k; i++)
		s+= ds_canh[i].do_dai;
	return s;
}

int main()
{
	canh ds_canh[50], PA[50];
	int n;
	int k;
	int k_PA;
	readFile("TSP.txt", ds_canh, &n, &k);
	printf("Danh sach canh truoc khi SAP XEP\n");
	InDS_canh(ds_canh, n, k);
	Greedy(ds_canh, n, k, PA, &k_PA);
	printf("Danh sach canh sau khi SAP XEP\n");
	InDS_canh(ds_canh, n, k);
	printf("Phuong an TSP :\n");
	InDS_canh(PA, n, k_PA);
	printf("Tong do dai duong di la: %.2f", TongDoDaiDuongDi(PA, k_PA));
	return 0;
}


