#include<stdio.h>
int main() {
    int n, x, sum=0, kub=1, j;
    scanf("%d", &n);
        if(n>0) {
            for(; n>=1; n--) {
                scanf("%d", &x);
                if(x%2==0)
                {
                    for (j=0; j<3; j++)
                    {
                        kub*=x;
                    }
                sum+=kub;
                kub=1;
                }
            }
        }
    printf("%d", sum);
    return(0);
}
