#include<stdio.h>
int main() {
    int n, x1, x2;
    scanf("%d", &n);
    if(n>0) {
        scanf("%d", &x1);
        n--;
        if(n>0) {
            for(; n>=1; n--) {
                scanf("%d", &x2);
                if(x1>x2)
                    x1=x2;
            }
        }
    }
    printf("%d", x1);
    return(0);
}
