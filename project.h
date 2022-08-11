#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define reset printf("\033[0m") 
#define cyan printf("\033[1;36m")
#define yellow printf("\033[1;33m")
#define red printf("\033[1;31m")
#define clrscr() printf("\e[1;1H\e[2J")

#define NUM_TILES 64
#define NUM_TILES_PER_ROW 8

/* Definition of a node (vertex)*/
typedef struct node
{
	int value;
	struct node * next;
}node;

typedef node * Node;

/* Definition of an adjacency list */
typedef struct AdjacencyListElement
{
	Node begin;
}AdjacencyListElement;

typedef struct AdjacencyListElement * AdjacencyList;

/* Definition of a graph */
typedef struct graph
{
	int Vertices;
	AdjacencyList Neighbours;
}graph;

typedef graph * Graph;

/* Prototypes */
/*building graph*/
Graph buildKnightGraph();
Node addNode(int x);
int * calculateLegalMoves(int Before);
void addEdge(Graph g, int src, int dest);
int getLength(Node n);
void assignEdges(Graph g, int Before);
const char * assignCase(int x);
void printGraph(Graph g);
void printOptimalZone(Graph g);

/* valid moves*/
bool isOnSameLine(int Before, int After);
bool isOutOfBounds(int x);
bool isExclusionChessboard(int Before, int After);
bool isValidMove(int Before, int After);


/*knight tour*/
int ** AdjacencyMatrix(Graph g);
void knightTour(int ** adjacencyMatrix, int src);
void DFS(int ** adjacencyMatrix, int i, bool visited[], int * count, int ** outputMatrix);
void assignToMatrix(int ** Matrix, int index, int weight);
