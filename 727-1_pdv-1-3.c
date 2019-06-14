#include <stdio.h>
#include <math.h>

int main() {
    int x,y,b;
    scanf ("%d %d", &x,&y);
    b = (int)(exp(log(x) * y) + 0.5);
    printf ("%d", b );
    return 0;
}
