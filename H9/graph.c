//Imtiaz Mujtaba Khaled
//1001551928
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Graph{
    char name[20];
}Graph;


int main(void)  {
    int i, numVertices;
    printf("enter number of vertices: ");
    scanf("%d",&numVertices);   //takes in the number of vertices in the graph
    Graph * graph = malloc(numVertices * sizeof(Graph));
    for(i = 0; i <= numVertices; ++i)    {   //takes in the vertices in the graph
        printf("enter name: ");
        fgets(graph[i].name, 20, stdin);
        graph[i].name[strlen(graph[i].name)-1] = '\0';
    }
    printf("\nGRAPH:\nN = %d\n", numVertices);    //prints the number of vertices
    for(i = 0; i < numVertices; ++i)    
        printf("%d- %s\n", i, graph[i+1].name);    //prints the graph
    printf("\n");
    char nameOne[20], nameTwo[20], fullLine[49];
        
    do
    {
        fgets(fullLine, 50, stdin);
        sscanf(fullLine, "%s\t%s",nameOne, nameTwo);    //reads in two of the edges
        if(strcmp(nameOne, "-1") || strcmp(nameTwo, "-1"))  {
            continue;
        }

    } while (strcmp(nameOne, "-1") || strcmp(nameTwo, "-1"));
    
    return 0;
}

