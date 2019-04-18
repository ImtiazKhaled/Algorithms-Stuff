#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(lhs, rhs)   (((lhs) < (rhs)) ? rhs : lhs)
#define double_hash(prevHash, tableSize)    ((prevHash * 3) % tableSize)


typedef struct dictionary   {
    char word[101];
    char definition[1000];
}dictionary;

typedef struct hash_table   {
    char word[101];
    char definition[1000];
    int occupied;
}hash_table;


//gets a line count for the given file
int get_line_count(char *dictname)  {
    FILE *file = NULL;
    char c;
    int count=0;
    file = fopen(dictname, "r");
    if(dictname == NULL)    {
        perror("unable to open file");
        exit(0);    
    }
    for (c = getc(file); c != EOF; c = getc(file)) 
        if (c == '\n') count++;
    fclose(file);
    return count;
}


//reads in the file into two strings one for the words the other for the translation 
void read_file(char * dictname, dictionary * dictionaryWords, int count)   {	
    printf("\nLoading the dictionary file %s into a hash table\n", dictname);    
    FILE *file = NULL;
    file = fopen(dictname, "r");
    char bufferWord[101], bufferDefinition[1000], buffer[1000];
    int number_words_dictionary, i = 0, j, k, number_words_test, counter_for_distances = 0;
    if(dictname == NULL)    {
        perror("unable to open file.");
        exit(0);
    }
    //Reads the file into a "dictionary"
    for(i = 0; i <  count; i++)   {
        fscanf(file, "%[^\n]\n", buffer);        
        sscanf (buffer,"%s\t%[^\n]",bufferWord, bufferDefinition);       
        strcpy(dictionaryWords[i].word, bufferWord);
        strcpy(dictionaryWords[i].definition, bufferDefinition);
    }

    fclose(file);        
}

//hash fucntion, written by myself
int hash_function(char * word, int tableSize) {
    int i, hash = 0;
    for(i = 0; i < strlen(word); i++)   {
        hash = (hash + ((int)(word[i]*10)))%tableSize;
    }
    return hash;
}

//gets the closest prime number to 1.3*lineCount
int closest_prime(int lineCount) {
    int i;
    lineCount++;
    for (i = 2; i < lineCount; i++) {
        if(lineCount % i == 0) {
            lineCount++;
            i=2;
        } 
        else    continue;
    }
    return lineCount;
}


//required functions
int search_word(hash_table * hashTable, char * word, int tableSize, int maxProbe, int *probeCounter, int print) {   
    int i = 0; 
    int index = hash_function(word, tableSize); 
    
    while(i <= maxProbe)   {
        if(hashTable[index].occupied)   {
            if(strcmp(word, hashTable[index].word) == 0)    {
                *probeCounter +=  1;    
                if(print == 1)    printf(" Query: %s\n\t%d probes\n\tTranslation: %s\n",hashTable[index].word, *probeCounter, hashTable[index].definition);
                return index;
            }
            else    { 
                index = double_hash(index, tableSize);  //double_hash defined as a macro
                *probeCounter +=  1;
                i++;
                continue;
            }                
        }
        else    {
            *probeCounter +=  1;
            i++;
            continue;
        }
    }
    if(print == 1)  printf(" Query: %s\n\t%d probes\n\tNOT found\n",hashTable[index].word, *probeCounter);
    return -1;
}


void insert_word(hash_table * hashTable, char * word, char * inputDefinition, int tableSize, int *probeCounter, int *hashCounter, int print)    {
    int secondOccurence = 0, index = hash_function(word, tableSize);
    while(hashTable[index].occupied == 1)    {    
        if(!strcmp(word, hashTable[index].word)) {
            *probeCounter += 1;
            secondOccurence = 1;
            break;
        }
        *probeCounter += 1;
        index = double_hash(index, tableSize);  //double hash defined as macro
    }
    if(secondOccurence == 1) {
        char wordToCat[strlen(inputDefinition)+2];
        strcpy(wordToCat, "; "); 
        strcat(wordToCat, inputDefinition);;
        strcat(hashTable[index].definition, wordToCat); 
        *probeCounter += 1;
        *hashCounter += 1;
        return;
    }
    strcpy(hashTable[index].word, word);
    strcpy(hashTable[index].definition, inputDefinition); 
    hashTable[index].occupied = 1;
    *probeCounter += 1;
    *hashCounter += 1;
    return;
}


void delete_word(hash_table * hashTable, char * word, int tableSize, int maxProbe, int *probeCounter)    {
    int index = search_word(hashTable, word, tableSize, maxProbe, probeCounter, 0);
    if(index == -1) {
        printf(" Query: %s\n\t%d probes\n\tItem not found => no deletion.\n",word, *probeCounter);
        return;
    }
    else    {
        hashTable[index].occupied = 0;
        strcpy(hashTable[index].definition, " "); 
        printf(" Query: %s\n\t%d probes\n\tItem was deleted.\n",word, *probeCounter); 
    }
}


void print_hash_table(hash_table * hashTable, int tableSize) {
    int i;
    for(i = 0; i < tableSize; i++) 
        printf("%s\t%s\n", hashTable[i].word, hashTable[i].definition);  
}


int main(void)  {
    int i, index, lineCount, totalProbe = 0, maxProbe = 0, hashCounter = 0, stoploop = 1;
    double averageProbes = 0;
    char dictionaryName[50], choice = {-1}, userInput[100], word[20], definition[50];
    printf("Enter the filename with the dictionary data (include the extension e.g. Spanish.txt): ");   
    fgets(dictionaryName, 50, stdin);
    dictionaryName[strlen(dictionaryName)-1] = '\0';
    lineCount = get_line_count(dictionaryName); //gets the number of lines in the file 
    dictionary * dictionaryWords = malloc((lineCount)*sizeof(dictionary));  //dynamically allocate a blank dictionary to be filled out by "read_file"
    read_file(dictionaryName, dictionaryWords, lineCount); //reads in the dictionary from the file
    int tableSize = closest_prime(2*lineCount); //gets the closest prime number to 1.3*lineCount
    hash_table * hashTable = malloc((tableSize)*sizeof(hash_table));    //dynamically allocate a blank hash table
    int * probeCounter = malloc((tableSize)*sizeof(int));    //array to store all the probeCounter values
    
    for(i = 0; i < tableSize; i++)  {
        hashTable[i].occupied = 0;  //set all elements in table to unoccupied
        probeCounter[i] = 0;    //set all probe counters to zero
    }
    
    
    int unHashed = lineCount;
    
    for(i = 0; i < lineCount; i++)  {
        insert_word(hashTable, dictionaryWords[i].word, dictionaryWords[i].definition, tableSize, probeCounter + i, &hashCounter, 0);  //contructs a hashtable with the given data
        maxProbe = max(probeCounter[i], maxProbe); //gets the maximum number of probes needed to search for in the hash table
        totalProbe +=probeCounter[i];   //gets the total number of probes during the insertion
    }

    free(dictionaryWords);  //deallocates memory used to store the dictionary words
    averageProbes = (double)totalProbe/(double)lineCount; //gets the average number of probes for all operations
    int * probeTable = malloc(maxProbe*sizeof(int)); //dynamically allocate to an array of probe counters
    for(i = 0; i < lineCount; i++)   probeTable[probeCounter[i]] += 1;  //fill the dynamically allocated table with the probe counter values
    printf("\nHash Table\n\taverage number of probes:\t\t%0.2f\n\tmax_run of probes:\t\t\t%d\n\ttotal PROBES (for %d items):\t\t%d\n\titem NOT hased (out of %d):\t\t0\n\n", averageProbes, maxProbe, lineCount, totalProbe, lineCount);
    printf("Probes|Count of keys\n-------------------\n");
    for(i = 1; i <= maxProbe; i++)   {   
        if(probeTable[i] == 0)  continue;
        else    printf("%6d|%6d\n----------------------\n",i, probeTable[i]);
    }
    //print the format shown on run1, except table is dynamically allocated
    
    i = lineCount - 1;
    totalProbe = 0;
    while(stoploop)    {    //enter loop for user input
        i++;
        probeCounter[i] = 0;
        strcpy(definition, " ");
        printf("READ op:");
        scanf("%c",&choice);
        getchar();
        fgets(userInput, 99, stdin);
        switch(choice)  {
            case 's':   userInput[strlen(userInput)-1] = '\0';
                        index = search_word(hashTable, userInput, tableSize, maxProbe, probeCounter + i, 1);
                        break;  //searches for the userInput
            case 'd':   userInput[strlen(userInput)-1] = '\0';
                        delete_word(hashTable, userInput, tableSize, maxProbe, probeCounter + i);
                        break;  //deletes the userInput
            case 'i':   sscanf (userInput,"%s\t%[^\n]",word, definition);      
                        insert_word(hashTable, word, definition, tableSize, probeCounter + i, &hashCounter, 1);
                        printf(" Query: %s\n\t%d probes\n\tWill insert pair [%s, %s]\n",word, probeCounter[i],word, definition);
                        break;   //inserts the word and defition provided by the user
            case 'q':   stoploop = 0; break;    //breaks the loop
            default: printf("that is not a valid command try again.\n"); //default if user input is wrong
        }
        totalProbe += probeCounter[i];
    }
    averageProbes = (double)totalProbe/(double)(i - lineCount - 1); //calculates average number of probes for the user inputs
    printf("\nAverage probes per operation:\t%0.2f\n",averageProbes);
    free(probeTable);
    free(hashTable);
    free(probeCounter);
    return 0; 
}


