#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(lhs, rhs)   (((lhs) < (rhs)) ? rhs : lhs)
#define double_hash(prevHash, tableSize)    ((prevHash  * 2) % tableSize)


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
        hash = (hash + ((int)word[i]*10))%tableSize;
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
    int i; 
    int index = hash_function(word, tableSize); 
    if(maxProbe == 0)   {
        while(1)   {
        if(hashTable[index].occupied)   {
            if(strcmp(word, hashTable[index].word) == 0)    {    
                if(print == 1)    printf("Quert: %s\tTranslation: %s\n",hashTable[index].word ,hashTable[index].definition);
                return index;
            }
            else    { 
            index = double_hash(index, tableSize);  //double_hash defined as a macro
            *probeCounter = *probeCounter + 1;
            i++;
            continue;
            }                
        }
        else    continue;
        *probeCounter = *probeCounter + 1;
        i++;
        }
    }
    else    {
        while( i < 5)   {
            if(hashTable[index].occupied)   {
                if(strcmp(word, hashTable[index].word) == 0)    {    
                    if(print == 1)    printf("Quert: %s\tTranslation: %s\n",hashTable[index].word ,hashTable[index].definition);
                    return index;
                }
                else    { 
                index = double_hash(index, tableSize);  //double_hash defined as a macro
                *probeCounter = *probeCounter + 1;
                i++;
                continue;
                }                
            }
            else    continue;
            *probeCounter = *probeCounter + 1;
            i++;
        }
    }
    if(print == 1)  printf("NOT found\n");
    return -1;
}


void insert_word(hash_table * hashTable, char * word, char * inputDefinition, int tableSize, int maxProbe, int *probeCounter)    {
    int index = search_word(hashTable, word, tableSize, maxProbe, probeCounter, 0);
    if(index != -1) {
        char wordToCat[strlen(inputDefinition)+2];
        strcpy(wordToCat, "; "); 
        strcat(wordToCat, inputDefinition);;
        strcat(hashTable[index].definition, wordToCat); 
        //probeCounter = 0;
        return;
    }

    index = hash_function(word, tableSize); 
    strcpy(hashTable[index].word, word);
    strcpy(hashTable[index].definition, inputDefinition); 
    hashTable[index].occupied = 1;
    return;
}

void delete_word(hash_table * hashTable, char * word, int tableSize, int maxProbe, int *probeCounter)    {
    int index = search_word(hashTable, word, tableSize, maxProbe, probeCounter, 0);
    if(index == -1) {
        printf("Item not found => no deletion.\n");
        return;
    }
    else    {
        hashTable[index].occupied = 0;
        strcpy(hashTable[index].word, " "); 
        strcpy(hashTable[index].definition, " "); 
        printf("Item was deleted.\n");
    }
}


int main(void)  {
    int i, lineCount, totalProbe = 0, maxProbe = 0, counterProbe = 0;
    char dictionaryName[50], choice;
    printf("Enter the filename with the dictionary data (include the extension e.g. Spanish.txt): ");   
    fgets(dictionaryName, 50, stdin);
    dictionaryName[strlen(dictionaryName)-1] = '\0';
    lineCount = get_line_count(dictionaryName); //gets the number of lines in the file 
    dictionary * dictionaryWords = malloc((lineCount)*sizeof(dictionary));  //dynamically allocate a blank dictionary to be filled out by "read_file"
    read_file(dictionaryName, dictionaryWords, lineCount); //reads in the dictionary from the file
    int tableSize = closest_prime(lineCount); //gets the closest prime number to 1.3*lineCount
    hash_table * hashTable = malloc((tableSize)*sizeof(hash_table));    //dynamically allocate a blank hash table
    int * probeCounter = malloc((tableSize)*sizeof(int));    //array to store all the probeCounter values
    

    for(int i = 0; i < lineCount; i++)  {
        probeCounter[i] = 1;
        insert_word(hashTable, dictionaryWords[i].word, dictionaryWords[i].definition, tableSize, maxProbe, probeCounter + i);
    /*     printf("curr counter: %d\tmaxprobe: %d\n", probeCounter[i], maxProbe);
        maxProbe = max(probeCounter[i], maxProbe); //gets the maximum number of probes needed to search for in the hash table
        probeCounter[i] = counterProbe;
        printf("curr counter: %d\tmaxprobe: %d\n", probeCounter[i], maxProbe);
     */
    }
    
    printf("\ndone with table\n");
    /* 
    int index = search_word(hashTable, "aback", tableSize, maxProbe, probeCounter, 1);
    index = search_word(hashTable, "horse", tableSize, maxProbe, probeCounter, 1);
    index = search_word(hashTable, "sun", tableSize, maxProbe, probeCounter, 1);
    index = search_word(hashTable, "cat", tableSize, maxProbe, probeCounter, 1);
    delete_word(hashTable, "cat", tableSize, maxProbe, probeCounter);
    index = search_word(hashTable, "cat", tableSize, maxProbe, probeCounter, 1);
    delete_word(hashTable, "cat", tableSize, maxProbe, probeCounter);
    insert_word(hashTable, "cat", "*******", tableSize, maxProbe, &probeCounter[i]);
    index = search_word(hashTable, "cat", tableSize, maxProbe, probeCounter, 1);
    insert_word(hashTable, "cat", "elgato", tableSize, maxProbe, &probeCounter[i]);
    index = search_word(hashTable, "cat", tableSize, maxProbe, probeCounter, 1);
    insert_word(hashTable, "cat", "gato", tableSize, maxProbe, &probeCounter[i]);
    index = search_word(hashTable, "cat", tableSize, maxProbe, probeCounter, 1);
     */
    
    /* insert_word(hashTable, "cat", "henlo", tableSize, maxProbe, &probeCounter[i]);
    insert_word(hashTable, "cat", "hooman", tableSize, maxProbe, &probeCounter[i]);
    
    
    delete_word(hashTable, "cat", tableSize, maxProbe, probeCounter);
    index = search_word(hashTable, "cat", tableSize, maxProbe, probeCounter, 1);
    delete_word(hashTable, "cat", tableSize, maxProbe, probeCounter);

    
    for(i = 0; i < tableSize; i++) printf("occupied: %d\tname: %s\tdefinition: %s\n", hashTable[i].occupied, hashTable[i].word, hashTable[i].definition);

    int index = search_word(hashTable, dictionaryWords[2].word, tableSize, maxProbe, &probeCounter[2]);
    printf("%d",probeCounter[2]);
 */
    
    /*
    int hash = hash_function(dictionaryWords[3].word,tableSize);
    printf("%d\n", hash);
    hash = double_hash(hash,tableSize);
    printf("%d\n", hash);
    hash = double_hash(hash,tableSize);
    printf("%d\n", hash);
    hash = double_hash(hash,tableSize);
    printf("%d\n", hash);*/    
    
    free(dictionaryWords);
    free(hashTable);
    free(probeCounter);
    return 0;
}

