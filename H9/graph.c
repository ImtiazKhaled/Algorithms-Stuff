//Imtiaz Mujtaba Khaled
//1001551928

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Graph{
    char name[20];
    int visited;
    struct Graph * link;
}Graph;
/* 
void groupCheck(Graph * graph, int numVertices)  {
    int k = 0, i = 1, numGroups = 0;
    for(i = 1; i <= numVertices; ++i)   {
        Graph temp = graph[0];
        if(temp.visited == 0) {
            temp.visited = 1;
            while(temp.link ==  NULL)  {
                //temp = (temp.link);
                temp.link == NULL;
                ++k;
            }
        }else   {}
        //temp = graph[0];
        Graph graphGroup[k + 1];
        for( i = 0; i < k; ++i) {
            if(i == 0)  graphGroup[i] = temp;
            else {
                //temp = *(temp.link);
                graphGroup[i] = temp;
            }
        }

        ++numGroups;
    }
    printf("\n%d\n",numGroups);
}
 */

int main(void)  {
    int i, j, k, numVertices;
    printf("enter number of vertices: ");
    scanf("%d",&numVertices);   // takes in the number of vertices in the graph
    Graph * graph = malloc(numVertices * sizeof(Graph));
    for(i = 0; i <= numVertices; ++i)    {   // takes in the vertices in the graph
        printf("enter name: ");
        fgets(graph[i].name, 20, stdin);
        graph[i].name[strlen(graph[i].name)-1] = '\0';
        graph[i].visited = 0;
        graph[i].link = NULL;
    }
    printf("\nGRAPH:\nN = %d\n", numVertices);    // prints the number of vertices
    for(i = 0; i < numVertices; ++i)    
        printf("%d- %s\n", i, graph[i+1].name);    // prints the graph
    
    char nameOne[20], nameTwo[20], fullLine[49];        
    while (strcmp(nameOne, "-1") || strcmp(nameTwo, "-1"))   {
        fgets(fullLine, 50, stdin);
        sscanf(fullLine, "%s\t%s",nameOne, nameTwo);    // reads in two of the edges
        fullLine[strlen(fullLine)-1] = '\0';
        if(strcmp(nameOne, "-1") || strcmp(nameTwo, "-1"))  {
            i = 0; j = 0;
            while(strcmp(graph[i].name, nameOne))   ++i;
            while(strcmp(graph[j].name, nameTwo))   ++j;
            graph[i].link = &(graph[j]);
        }
    }
    
    for(i = 1; i <= numVertices; ++i)   {   // prints the matrix using 4 nested ternary operators
        for(j = 1; j <= numVertices; ++j)
            (graph[i].link == NULL) ? printf("0 ") : // if there is no link print 0
            (strcmp(graph[i].link->name, graph[j].name ) ) ?    // check the link's name of i with the name of the graph j
            ((graph[j].link == NULL ) ? printf("0 ") :  // if there is no link print 0
            (strcmp(graph[j].link->name, graph[i].name) ? printf("0 ") : printf("1 ")) // checks the link's name i with the name of the graph j
             ) : printf("1 ");  // prints 1 if the return of link i matched with the name of j
        printf("\n");
    }

    //groupCheck(graph, numVertices);
    return 0;
}

