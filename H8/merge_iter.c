#include <stdio.h>
#include <stdlib.h>

void printArray(int * currentArray, int currentSize)   {
    int i;
    for(i = 0; i < currentSize; i++)    printf("%5d,",currentArray[i]);
    printf("\n");
}



void mergeSort(int * arrayInt, int arraySize)   {
    int i;
    int currnetSize, leftIndex;
    printArray(arrayInt, arraySize);
    //for(i = 0; i < arraySize; i++)    arrayInt[i] = -1;
    for(currentSize = 1; currentSize < arraySize - 1; currentSize *= 2)  {
        for(leftIndex = 0; leftIndex < arraySize - 1; leftIndex += currentSize) {
                int mid = ( leftIndex + currentSize ) / 2;
                int right = ( ( currentSize - 1 ) - leftIndex );

        }
    }  
    printArray(arrayInt, arraySize);
    
}

int main(void)  {
    int arraySize; 
    do
    {
        int i;
        scanf("%d",&arraySize);
        int * arrayInt = malloc(arraySize*sizeof(int) * arraySize);
        for(i = 0; i < arraySize; i++)  scanf("%d",&arrayInt[i]);
        printf("\n");
        mergeSort(arrayInt, arraySize);
    } while (arraySize != -1);
    free(arrayInt);
    return 0;    
}

