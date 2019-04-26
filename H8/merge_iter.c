#include <stdio.h>
#include <stdlib.h>
#define minimum(X, Y)   (( X < Y )? X : Y)

void printArray(int * currentArray, int currentSize)   {
    int i;
    for(i = 0; i < currentSize; i++)    printf("%5d,",currentArray[i]);
    printf("\n");
}


void merge(int * arrayInt, int leftIndex, int midIndex, int rightIndex) {
    int i, j, k, sizeOne = (midIndex - leftIndex + 1), sizeTwo = (rightIndex - midIndex);
    int arrayLeft[sizeOne], arrayRight[sizeTwo];
    for(i = 0; i < sizeOne; ++i)

    return;
}


void mergeSort(int * arrayInt, int arraySize)   {
    int i;
    int currentSize, leftIndex;
    printArray(arrayInt, arraySize);
    for(currentSize = 1; currentSize <= arraySize - 1; currentSize = currentSize*2)  {
        for(leftIndex = 0; leftIndex < arraySize - 1; leftIndex = currentSize*2) {
                int midIndex = leftIndex + currentSize - 1;
                int rightIndex = minimum( leftIndex + 2*currentSize -1 , arraySize - 1 );
                merge(arrayInt, leftIndex, midIndex, rightIndex );

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
        free(arrayInt); 

    } while (arraySize != -1);
    return 0;    
}

