#include <stdio.h>

void mergeSort(int * arrayInt, arraySize)   {
    printArray(arrayInt, arraySize);
    for(i = 0; i < arraySize; i++)    arrayInt[i] = -1;
    printArray(arrayInt, arraySize);
    
}

void printArray(int * currentArray, int currentSize)   {
    int i;
    for(i = 0; i < currentSize; i++)    printf("%5d",currentArray[i]);
    printf("\n");
}


int main(void)  {
    do
    {
        int arraySize;
        scanf("%d",&arraySize);
        int * arrayInt = malloc(arraySize*sizeof(int));
        mergeSort(arrayInt, arrarySize);
    } while (arraySize != -1);
    return 0;    
}

