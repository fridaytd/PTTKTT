// Tam giac so
// Quy hoach dong

#include <stdio.h>
#include <limits.h> 

void readFile(int a[][100], int* n) {
    FILE* f;
    f=fopen("tamgiacso.txt", "r");
    int i=0;
    if (f!=NULL) {
        while (!feof(f)) {
            int j;
            for (j=0; j<=i; j++)
                fscanf(f, "%d", &a[i][j]);
            i++;
        }
    }
    else {
        printf("Loi doc file !!!");
    }
    *n=i;
    fclose(f);
}

void inMaTran(int a[][100], int n) {
    printf("\nMa tran:\n");
    int i, j;
    for (i=0; i<n; i++) {
        for (j=0; j<=i; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}

int maxIndex(int F[][100], int i, int j) {
    int Fmax=INT_MIN;
    int maxId;
    int k;
    for (k=j-1; k<=j+1; k++) {
        if (k>=0&&k<=i&&F[i][k]>Fmax) {
            Fmax=F[i][k];
            maxId=k;
        }
    }
    return maxId;
}

void taoBang(int a[][100], int n, int F[][100]) {
    F[0][0]=a[0][0];
    int i, j;
    for (i=1; i<n; i++) {
        for (j=0; j<=i; j++) {
            F[i][j]=F[i-1][maxIndex(F, i-1, j)]+a[i][j];
        }
    }
}

void traBang(int F[][100], int n, int PA[]) {
    int j=0;
    int Fmax=F[n-1][j];
    // Tim index max hang cuoi
    int i;
    for (i=1; i<n; i++)
        if (F[n-1][i]>Fmax) {
            Fmax=F[n-1][i];
            j=i;
        }
    PA[n-1]=j;
    int k;
    for (k=n-1; k>=1; k--) {
        j=maxIndex(F, k-1, j);
        PA[k-1]=j;
    }
}

void inPA(int a[][100], int n, int PA[]) {
    int i;
    int sum=a[0][0];
    printf("\nDuong di: ");
    printf("(1, 1)");
    for (i=1; i<n; i++) {
        printf(" -> (%d, %d)", i+1, PA[i]+1);
        sum+=a[i][PA[i]];
    }
    printf("\nTong gia tri la: %d", sum);
}

int main() {
    int a[100][100];
    int n;
    readFile(a, &n);
    inMaTran(a, n);
    int F[100][100];
    taoBang(a, n, F);
    inMaTran(F, n);
    int PA[100];
    traBang(F, n, PA);
    inPA(a, n, PA);
    return 0;
}