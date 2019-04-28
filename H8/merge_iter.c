#include <stdio.h>
#include <stdlib.h>

void printArray(int * currentArray, int leftIndex, int rightIndex, int arraySize)   {
    int i;
    for(i = 0; i < leftIndex; i++)  printf("     ,");
    for(i = leftIndex; i < rightIndex; i++)    printf("%5d,",currentArray[i]);
    for(i = rightIndex; i < arraySize; i++)  printf("     ,"); 
    printf("\n");
}


void merge(int * arrayInt, int leftIndex, int midIndex, int rightIndex, int arraySize) {
    int i, j, k;
    int sizeOne = midIndex - leftIndex + 1;
    int sizeTwo = (rightIndex - midIndex - 1); 
    int arrayLeft[sizeOne], arrayRight[sizeTwo];
    for(i = 0; i < sizeOne; ++i)    arrayLeft[i] = arrayInt[ leftIndex + i ];
    for(j = 0; i < sizeTwo; ++j)    arrayRight[j] = arrayInt[ (midIndex - 1) + j ];
    int a = leftIndex + sizeOne;
    int b = rightIndex - sizeTwo;
    i = 0, j = 0;
    k = leftIndex;
    while( k < rightIndex) {
     if(arrayLeft[i] < arrayRight[j])    {
            arrayInt[k] = arrayRight[j];
            ++j;
        }else
        {
            arrayInt[k] = arrayLeft[i];
            ++i;
        }
        ++k;
    }
    printArray(arrayInt, leftIndex, rightIndex, arraySize);
    return;
}


void mergeSort(int * arrayInt, int arraySize)   {
    int i;
    int currentSize, leftIndex;
    printArray(arrayInt, 0, arraySize, arraySize);
    for(currentSize = 1; currentSize <= arraySize - 1; currentSize *= 2)  {
        for(leftIndex = 0; leftIndex < (arraySize - currentSize); leftIndex += (2*currentSize)) {
                if(currentSize > arraySize) currentSize = arraySize;
                int midIndex = leftIndex + currentSize - 1;
                int rightIndex = leftIndex + 2*currentSize;
                 merge( arrayInt, leftIndex, midIndex, rightIndex, arraySize );
        }
    }  
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

