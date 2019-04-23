#include <stdio.h>

int main(void)  {
    do
    {
        int arraySize;
        scanf("%d",&arraySize);
        int * arrayInt = malloc(arraySize*sizeof(int));
    } while (arraySize != -1);
    
}