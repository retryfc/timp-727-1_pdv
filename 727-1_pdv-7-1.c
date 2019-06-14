#include <stdio.h>
#include <stdlib.h>

void sort(int arr[],int l,int r) {
    int i=l,j=r,d,m=arr[(l+r)/2];
    while(i<=j) {
        for(; arr[i]<m; i++);
        for(; arr[j]>m; j--);
        if(i<=j) {
            d=arr[i];
            arr[i++]=arr[j];
            arr[j--]=d;
        }
    }
    if(l<j) sort(arr,l,j);
    if(i<r) sort(arr,i,r);
}

int main() {
    int n;
    scanf("%d",&n);
    int arr[n];
    for(int i=0; i<n; i++) {
        scanf("%d",&arr[i]);
    }
    sort(arr,0,n);

    for(int i=0; i<n; i++) {
        printf("%d",arr[i]);
        if(i < n-1)
            printf(" ");
    }
    printf("\n");
    return 0;
}

