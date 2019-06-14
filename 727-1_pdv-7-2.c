#include <stdio.h>
#include <stdlib.h>

int k = 0, comp = 0;

void siftDown (int *arr, int root, int bottom)
{
	int maxChild;
	int done = 0; 
	
	k++;
	while ((root * 2 <= bottom) && (!done)) 
	{
		k++;
		if (root * 2 == bottom)    
		maxChild = root * 2;    
		
		else if (arr[root * 2] > arr[root * 2 + 1])
			maxChild = root * 2;
		else
			maxChild = root * 2 + 1;
		k++;
		if (arr[root] < arr[maxChild]) 
		{
			int temp = arr[root]; 
			arr[root] = arr[maxChild];
			arr[maxChild] = temp;
			root = maxChild;
			comp++;
		}
		else
			done = 1; 
	
		k++;
	}

}

int sorting_function (int *arr, int len)
{
	
	for (int i = (len / 2) - 1; i >= 0; i--)
		siftDown (arr, i, len - 1);
	
	for (int i = len - 1; i >= 1; i--)
	{
		int temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		comp++;
		siftDown (arr, 0, i - 1);
	}	
	 
	return 0;
}

int main ()
{
	int n, i, a;
	int *arr = NULL;

	scanf ("%d", &n);

	arr = (int*) malloc (n * sizeof(int));

	for (i = 0; i < n; i++)
	{
		scanf("%d", &a);
		arr[i] = a;
	}
	
	sorting_function (arr, n);

	for (i = 0; i < n; i++)
	{
		printf("%d", arr[i]);
		if (i != n-1)
		{
			printf (" ");
		}
	}
	printf("\n");

	return 0;
}
