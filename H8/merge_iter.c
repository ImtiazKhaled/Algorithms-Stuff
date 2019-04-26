#include <stdio.h>
#include <stdlib.h>
#define minimum(X, Y)   (( X < Y )? X : Y)

void printArray(int * currentArray, int currentSize)   {
    int i;
    for(i = 0; i < currentSize; i++)    printf("%5d,",currentArray[i]);
    printf("\n");
}


void merge(int * arrayInt, int leftIndex, int midIndex, int rightIndex) {
    int i, j, k;
    int sizeOne = (midIndex - leftIndex + 1);
    int sizeTwo = (rightIndex - midIndex);
    int arrayLeft[sizeOne], arrayRight[sizeTwo];
    for(i = 0; i < sizeOne; ++i)    arrayLeft[i] = arrayInt[ leftIndex + i ];
    for(j = 0; i < sizeTwo; ++j)    arrayRight[j] = arrayInt[ rightIndex + j ];
    i = 0, j = 0, k = 0;
    
    for( k =  leftIndex; k < rightIndex; ++k)   {
        if(arrayLeft[i] <= arrayRight[j])    {
            arrayInt[k] = arrayLeft[i];
            ++i;
        }else
        {
            arrayInt[k] = arrayRight[j];
            ++j;
        }
        
    }
    return;
}


void mergeSort(int * arrayInt, int arraySize)   {
    int i;
    int currentSize, leftIndex;
    printArray(arrayInt, arraySize);
    for(currentSize = 1; currentSize <= arraySize - 1; currentSize *= 2)  {
        for(leftIndex = 0; leftIndex < arraySize - 1; leftIndex += 2*currentSize) {
                int midIndex = leftIndex + currentSize - 1;
                int potentialRight = (leftIndex - 1) + 2*currentSize;
                int otherPotentialRight = arraySize - 1;
                int rightIndex = minimum( potentialRight , otherPotentialRight );
                merge(arrayInt, leftIndex, midIndex, rightIndex );
                //printf("left: %d, mid: %d, right: %d, current size: %d\n",leftIndex,midIndex,rightIndex,currentSize);      
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

