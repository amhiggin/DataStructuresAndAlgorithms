/*
 *	@Author Amber Higgins.
 *	Student number: 13327954
 *	3D5A Assignment 4 - Dijkstra's Algorithm.
 *
 *	The DFS search works well for all valid characters and indexes entered.
 *	The Dijkstra algorithm identifies the correct paths in each case but for some reason is not accumulating the total cost of the path correctly.
 *	I believe that instead, it is simply combining the cost of the nearest edge connected to the source node, and the sought node.
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMVERTICES 12						// Number of vertices/nodes in the graph.
#define MAXSENTINEL 99999					// 'maximum value' initialiser for test variables.

typedef struct Node{
	char nodeValue;
	int edge_weight;
} Node;

// Arrays to store the distances, path costs and path cost predictions. Note costOfPath[][] used because it copies the graph weightings from graph[][] but can be edited by the calling function.
int distance[NUMVERTICES], costOfPath[NUMVERTICES][NUMVERTICES], prediction[NUMVERTICES];
bool visitedNode[NUMVERTICES], foundNode=false;

// Using an adjacency matrix to represent the graph elements
struct Node* graph[NUMVERTICES][NUMVERTICES];


void graphInitialise();						// Initialises the graph nodes and variables.
void assignWeight(int weight, int x_pos, int y_pos);		// Assigns an edge-weight to a given graph node in both directions (assumes directed graph).
void printGraphElements();					// Prints out the adjacency matrix for the graph elements, showing their path weightings.
void setGraphWeights();						// Specifies the weights to set for connected graph nodes.
void reinitialiseTheNodeVisitedAttribute();			// Resets global array visitedNode[].
void depthFirstSearch(int sourceNode, char targetNode);		// Performs DFS for the node targetNode, starting with node with index sourceNode.
void assertWhetherSearchSuccessful();				// Asserts whether the node being searched for, was found in the graph. 
void initialiseDijkstraVariables(int sourceNode);		// Initialises global variables used by the dijkstra() function.
bool outputDijkstraResults(int sourceNode, char targetNode);	// Outputs results from the Dijkstra algorithm. Parent nodes for path e.g. C<-B<-A represents A as a parent of B, B a parent of C.
bool dijkstra(int sourceNode, char targetNode); 		// Function to search a graph using Dijkstra's minimum-distance algorithm.  Returns true if node found, false if not.



int main(){
	// Initialise graph elements and print to the console.
	graphInitialise();
	setGraphWeights();
	printGraphElements();
	
	// Perform the two required depth-first searches
	printf("\n-----DFS of 'X' starting from 'A' (#1)-----\n");
	depthFirstSearch(0, 'X');
	assertWhetherSearchSuccessful();
	reinitialiseTheNodeVisitedAttribute();
	
	printf("\n-----DFS of 'B' starting from 'K' (#2)-----\n");
	depthFirstSearch(10, 'B');
	assertWhetherSearchSuccessful();
	reinitialiseTheNodeVisitedAttribute();
	
	//Perform the two required Dijkstra searches.
	printf("\n-----Starting Dijkstra search of 'X', starting from 'A' (#1)-----\n");
	dijkstra(0, 'X');
	assertWhetherSearchSuccessful();
	reinitialiseTheNodeVisitedAttribute();
	
	printf("\n-----Starting Dijkstra search of 'J', starting from 'A' (#2)-----\n");
	outdijkstra(0, 'J');
	assertWhetherSearchSuccessful();
	reinitialiseTheNodeVisitedAttribute();
	
	return 0;
}


void graphInitialise(){
	printf("---Initialising the graph elements---\n");
	
	// Allocate memory for each element of graph.
	for(int i=0;i<NUMVERTICES;i++){
		for(int j=0;j<NUMVERTICES;j++){
			graph[i][j] = (Node*)malloc(sizeof(Node*));
		}
	}
	
	// Initialise each node to null weighting, and initial 'character' value.
	for(int i=0;i<NUMVERTICES-1;i++){
		for(int j=0;j<NUMVERTICES-1;j++){
			graph[i][j]->edge_weight=0;
			graph[i][j]->nodeValue = ('A'+j);		
		}
		// No nodes have been visited yet - initialise to not-visited.
		visitedNode[i] = false;
	}
}


void assignWeight(int weight, int x_pos, int y_pos){
	//edge X->Y 
	graph[x_pos][y_pos]->edge_weight = weight;
	//edge Y->X has same weight (directed graph)
	graph[y_pos][x_pos]->edge_weight = weight;
}


void printGraphElements(){
    char letter;
    
    printf("\nGraph - Edge weights\n   ");
    for(int k =0; k<NUMVERTICES-1; k++){
        letter = ('A' + k);
        printf("%c  ", letter);
    }
    
    printf("\n");
    for(int i = 0; i < NUMVERTICES-1; ++i){
        // print letters
        letter = ('A' + i);
        printf("%c  ", letter);
	
	// print the weights for that letter
        for(int j = 0; j < NUMVERTICES-1; ++j)
            printf("%d  ", graph[i][j]->edge_weight); 

        printf("\n");
    }
    printf("\n");
}



void setGraphWeights(){
	printf("...Setting graph weights...\n");
	// Assign the weightings between the appropriate nodes.
	assignWeight(1,0,1);
	assignWeight(2,1,2);
	assignWeight(2,1,3);
	assignWeight(3,2,4);
	assignWeight(2,2,5);
	assignWeight(1,5,7);
	assignWeight(2,5,8);
	assignWeight(4,5,9);
	assignWeight(11,8,10);
	assignWeight(5,9,11);
	assignWeight(1,9,6);
	assignWeight(2,6,10);
	assignWeight(3,6,11);
	assignWeight(2,3,6);				
}


void reinitialiseTheNodeVisitedAttribute(){
	for(int i=0;i<NUMVERTICES;i++){
		visitedNode[i]=false;
	}
}


void depthFirstSearch(int sourceNode, char targetNode){
	// Print out the starting node's character, corresponding to the 'sourceNode' index given.
	char currentValue = ('A' + sourceNode);
	printf("%c ", currentValue);
	// We can now mark this node visited.
	visitedNode[sourceNode]=true;
	
	// Check whether, on this recursion, we have found the node we are looking for.
	if(currentValue ==targetNode){
		// Print a mark at this line if found, then return.
		printf(" || ");
		foundNode=true;
		return;
	}
	
	// Else, keep searching any connected nodes for a path to the node we want.
	for( int i=0;i<NUMVERTICES;i++){
		if(visitedNode[i] ==false && graph[sourceNode][i]->edge_weight>0){
			// This is a possible route to our target - recursively DFS on this node.
			depthFirstSearch(i, targetNode);
		}
	}
}


void assertWhetherSearchSuccessful(){
	if(foundNode==true){
		printf("\nFound node at '||' point - HALT\n");
	} else {
		printf("\nNode doesn't exist in graph\n");
	}
	
	//re-initialise foundNode
	foundNode=false;
}


void initialiseDijkstraVariables(int sourceNode){
	int i, j;

	// Initialise the path costs/weightings between the nodes.
	for(i=0;i<NUMVERTICES;i++){
		for(j=0;j<NUMVERTICES;j++){
			if(graph[i][j]->edge_weight ==0){
				costOfPath[i][j] = MAXSENTINEL;			// There is no existing path weighting - assign a default large value.
			} else costOfPath[i][j] = graph[i][j]->edge_weight;	// There is an existing non-zero path weighting.
		}
	}
	
	// Initialise the required variables:
	for(i=0;i<NUMVERTICES;i++){
		distance[i] = costOfPath[sourceNode][i];			// Gives a default initialisation of the distance cost between the sourceNode and the current node.
		prediction[i] = sourceNode;					// Gives a default initialisation of where the current node will branch to, as the sourceNode.
		visitedNode[i] = false;						// By default, the node will not have been visited before the graph has been searched.
	}
}



bool outputDijkstraResults(int sourceNode, char targetNode){
	for(int j=0;j<NUMVERTICES;j++){
		// Go through each node which isn't the starting node (the sourceNode)
		if(j!=sourceNode){
			// Print the minimum distance weighting between the two nodes.
			printf("\nMinimum distance weighting to %c from %c is %i", 'A'+j, 'A'+sourceNode, distance[j]);
			printf(", path = %c", 'A'+j);
			
			int i=j;
			
			// Print the minimum distance path between the two nodes.
			while(i!=sourceNode){
				i=prediction[i];
				printf("<-%c", 'A'+i);
			} 
			
			// Identify whether the value being sought exists in the graph.
			if('A'+j == targetNode){
				foundNode=true;
				printf(" \t\t|| ");
			}
		}
	}
	return foundNode;
}



void dijkstra(int sourceNode, char targetNode){
	// Declare, initialise the required variables.
	int minDistance, count=1, i, j;
	initialiseDijkstraVariables(sourceNode);
		
	// We have visited the source node specified.
	visitedNode[sourceNode]=true;
	
	while(count<NUMVERTICES-1){
		// Initialise minDistance to be a large value by default.	
		minDistance=MAXSENTINEL;
		
		for( i=0; i<NUMVERTICES;i++){
			if(distance[i] < minDistance && visitedNode[i]==false){
				// This is a new shortest path - save its weighting.
				minDistance = distance[i];
			}
			 // We have visited this node now.
			visitedNode[i]=true;
			
			for(j=0;j<NUMVERTICES;j++){
				if(visitedNode[j]==false){
					if((minDistance+costOfPath[i][j])<distance[j]){
						// We can say this is definitely part of the shortest path - save this path weighting.
						distance[j] = minDistance+costOfPath[i][j];
						// Save our knowledge of which minimum-cost node is connected to the current node.
						prediction[j] = i;
					}
				}
			}
		}
		// Go to next node for next iteration
		count++;
	}
	
	// Assert whether we have found the node successfully in the graph, and print to console
	foundNode = outputDijkstraResults(sourceNode, targetNode);
}
