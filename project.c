#include "project.h"

/** Mapping the Chessboard **/
const char * CHESSBOARD[8][8] = { 
	{ "A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1" },
	{ "A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2" }, 
	{ "A3", "B3", "C3", "D3", "E3", "F3", "G3", "H3" }, 
	{ "A4", "B4", "C4", "D4", "E4", "F4", "G4", "H4" }, 
	{ "A5", "B5", "C5", "D5", "E5", "F5", "G5", "H5" }, 
	{ "A6", "B6", "C6", "D6", "E6", "F6", "G6", "H6" }, 
	{ "A7", "B7", "C7", "D7", "E7", "F7", "G7", "H7" }, 
	{ "A8", "B8", "C8", "D8", "E8", "F8", "G8", "H8" }, 
};

/**Creation of Adjacency List **/
Graph newChessboardForKnight()
{
	Graph element;
	element = malloc(sizeof(*element));
	if(!element) printf("Unable to allocate the chessboard\n");

	element->Vertices = NUM_TILES;

	element->Neighbours = malloc(NUM_TILES * sizeof(AdjacencyListElement));
	if(!element->Neighbours) printf("Unable to allocate the neighbours\n");

	for(int i = 1; i < element->Vertices + 1; ++i)
		element->Neighbours[i - 1].begin = NULL;
	
	return element;
}

/** Adding a node **/
Node addNode(int x)
{
	node * n = malloc(sizeof(node));
	if(!n) printf("Unable to allocate the node\n");
	n->value = x;
	n->next = NULL;

	return n;
}

/** Assignment of boxes according to the value of the box (i.e 1 == A1) **/
const char * assignCase(int x)
{
	if(x <= NUM_TILES_PER_ROW) return CHESSBOARD[x / 10][(x - 1) % NUM_TILES_PER_ROW];
	else if(x <= 16) return CHESSBOARD[(x + 2)/ 10][(x - 1) % NUM_TILES_PER_ROW];
	else if(x <= 24) return CHESSBOARD[(x + 4) / 10][(x - 1) % NUM_TILES_PER_ROW];
	else if(x <= 29) return CHESSBOARD[(x + 5) / 10][(x - 1) % NUM_TILES_PER_ROW];
	else if(x <= 32) return CHESSBOARD[x/ 10][(x - 1) % NUM_TILES_PER_ROW];
	else if(x <= 40) return CHESSBOARD[(x + 7) / 10][(x - 1) % NUM_TILES_PER_ROW];
	else if(x <= 48) return CHESSBOARD[(x + 9)/ 10][(x - 1) % NUM_TILES_PER_ROW];
	else if(x == 49) return "A7";
	else if(x <= 56) return CHESSBOARD[(x + 10)/ 10][(x - 1) % NUM_TILES_PER_ROW];
	else if(x <= NUM_TILES) return CHESSBOARD[(x + 13)/ 10][(x - 1) % NUM_TILES_PER_ROW];
	return "";

}

/** Adding an edge**/
void addEdge(Graph g, int src, int dest)
{
	Node n = addNode(dest);
	n->next = g->Neighbours[src - 1].begin;
	g->Neighbours[src - 1].begin = n;
}

/** Graph display **/
void printGraph(Graph g)
{
	printf("Printing graph :\n");
	for(int i = 1; i < g->Vertices + 1; ++i)
	{
		Node n = g->Neighbours[i - 1].begin;
		printf("(%d) ", i);
		red,printf("Case ");
		yellow,printf("%s", assignCase(i)),reset;
		printf(": [");

		while(n)
		{
			cyan,printf("%s", assignCase(n->value)),reset;
			if(n->next) printf(", ");
			n = n->next;
		}
		printf("]\n");
	}
}

/** Builds the graph for the rider **/
Graph buildKnightGraph()
{
	printf("Creating the Knight's Graph\n");
	Graph g = newChessboardForKnight();

	printf("Assigning edges to the graph\n");
	for(int i = 1; i < g->Vertices + 1; ++i)
		assignEdges(g, i);
		
	return g;
}

/** If we're off the chessboard **/
bool isOutOfBounds(int x)
{
	if(x <= 0 || x > NUM_TILES)
		return true;
	return false;
}

/** Assign edges for rider graph **/
void assignEdges(Graph g, int Before)
{
	int * legalMoves = calculateLegalMoves(Before);
	for(int i = 1; i < NUM_TILES_PER_ROW + 1; ++i)
		if(!isOutOfBounds(legalMoves[i-1]))
			addEdge(g, Before, legalMoves[i-1]);

	free(legalMoves);
}

/** Calculates legal moves and dismissals as array **/
int * calculateLegalMoves(int Before)
{
	int * legalMove = malloc(NUM_TILES_PER_ROW * sizeof(int));
	if(!legalMove) printf("[!] Unable to allocate legal moves\n");

	int vectorMove[NUM_TILES_PER_ROW] = {-17, -15, -10, -6, 6, 10, 15, 17};

	for(int i = 0; i < NUM_TILES_PER_ROW; ++i)
	{
		int After = Before + vectorMove[i];
		if(!isValidMove(Before, After))
			legalMove[i] = -1;

		else
			legalMove[i] = After;
	}

	return legalMove;
}

/** If the move is valid **/
bool isValidMove(int Before, int After)
{
	return !isOnSameLine(Before, After) && !isExclusionChessboard(Before, After);
}

/** Shows the optimal area where you can play **/
void printOptimalZone(Graph g)
{
	printf("Printing Optimal Zone:\n");
	for(int i = 1; i < g->Vertices + 1; ++i)
	{
		Node n = g->Neighbours[i - 1].begin;
		int length = getLength(n);
		printf("%d ", length);
		if(i%8==0) printf("\n");
	}
	printf("This is the optimal zone to play with the Knight");
}

/** List size accessor **/
int getLength(Node n)
{
	if(!n) return 0;
	return 1 + getLength(n->next);
}

bool isOnSameLine(int Before, int After)
{
	return ((Before > 0 && Before <= 8) && (After > 0 && After <= 8))     ||
		   ((Before > 8 && Before <= 16) && (After > 8 && After <= 16))   ||
		   ((Before > 16 && Before <= 24) && (After > 16 && After <= 24)) ||
		   ((Before > 24 && Before <= 32) && (After > 24 && After <= 32)) ||
		   ((Before > 32 && Before <= 40) && (After > 32 && After <= 40)) ||
		   ((Before > 40 && Before <= 48) && (After > 40 && After <= 48)) ||
		   ((Before > 48 && Before <= 56) && (After > 48 && After <= 56)) ||
		   ((Before > 56 && Before <= 64) && (After > 56 && After <= 64));
}

bool isExclusionChessboard(int Before, int After)
{
	return ((Before == 1 && After == 16) || 
			(Before == 7 && After == 17) || 
			(Before == 8 && (After == 25 || After == 18)) || 
			(Before == 9 && After == 24) || 
			(Before == 15 && After == 25) || 
			(Before == 16 && (After == 33 || After == 26 || After == 1)) || 
			(Before == 17 && (After == 7 || After == 32)) || 
			(Before == 18 && After == 8) || 
			(Before == 23 && After == 33) || 
			(Before == 24 && (After == 41 || After == 9 || After == 34)) || 
			(Before == 25 && (After == 40 || After == 15 || After == 8)) || 
			(Before == 26 && After == 16) || 
			(Before == 31 && After == 41) || 
			(Before == 32 && (After == 42 || After == 17 || After == 49)) || 
			(Before == 33 && (After == 48 || After == 23 || After == 16)) || 
			(Before == 34 && After == 24) || 
			(Before == 39 && After == 49) || 
			(Before == 40 && (After == 57 || After == 50 || After == 25)) || 
			(Before == 41 && (After == 56 || After == 31 || After == 24)) || 
			(Before == 42 && After == 32) || 
			(Before == 47 && After == 57) || 
			(Before == 48 && (After == 58 || After == 33)) || 
			(Before == 49 && (After == 64 || After == 32 || After == 39)) || 
			(Before == 50 && After == 40) || 
			(Before == 56 && After == 41) || 
			(Before == 57 && (After == 47 || After == 40)) || 
			(Before == 58 && After == 48) ||
			(Before == 64 && After == 49));
}


/** Extract the matrix from the adjacency lists of the graph **/
int ** AdjacencyMatrix(Graph g)
{
	int ** adjacencyMatrix = (int **)malloc(NUM_TILES*sizeof(int *));
	for(int i = 0; i < NUM_TILES; ++i)
		adjacencyMatrix[i] = (int *)malloc(NUM_TILES*sizeof(int));

	for(int i = 1; i < g->Vertices + 1; ++i)
	{
		Node n = g->Neighbours[i - 1].begin;
		for(int j = NUM_TILES-1; j > -1 ; --j)
		{
			if(!n)
				break;

			else if(n->value - 1 == j)
			{
				adjacencyMatrix[i - 1][j] = 1;
				n = n->next;
			}

		}
	}

	return adjacencyMatrix;
}

/** DFS  **/
void DFS(int ** adjacencyMatrix, int i, bool visited[], int * count, int ** outputMatrix)
{	
	assignToMatrix(outputMatrix, i + 1, *count);
	if(*count < 63)
		red,printf("%s", assignCase(i + 1)),reset, printf("["), printf("%d", i+1), printf("]"),cyan, printf("("), printf("%d", (*count)++ +1), printf(") "),reset,printf("> ");

	else
		red,printf("%s", assignCase(i + 1)),reset, printf("["), printf("%d", i+1), printf("]"), cyan,printf("("), printf("%d", *count+1), printf(")"),reset;

	
	visited[i] = true;

	for(int j = 0; j < NUM_TILES; ++j)
		if(!visited[j] && adjacencyMatrix[i][j])
			DFS(adjacencyMatrix, j, visited, count, outputMatrix);
}
 /** Rider's Journey **/
void knightTour(int ** adjacencyMatrix, int src)
{
	bool visited[NUM_TILES];
	for(int i = 0; i < NUM_TILES; ++i)
		visited[i] = false;

	int count = 0;
	int ** outputMatrix = (int **)malloc(NUM_TILES_PER_ROW*sizeof(int *));
	for(int i = 0; i < NUM_TILES_PER_ROW; ++i)
		outputMatrix[i] = (int *)malloc(NUM_TILES_PER_ROW*sizeof(int));

	DFS(adjacencyMatrix, src - 1, visited, &count, outputMatrix);

	printf("\n\n\n");
	red,printf("[+] There is the output matrix for the starting case:"),yellow, printf(" %s\n", assignCase(src)),reset;
	for(int i=0;i<NUM_TILES_PER_ROW;i++){
		for(int j=0;j<NUM_TILES_PER_ROW;j++){
			printf("%2d ",outputMatrix[i][j]+1);
			}
		printf("\n");
	}
	
}

/* Assignment to Rider Journey Matrix */
void assignToMatrix(int ** Matrix, int index, int weight)
{
	int x,y;
	if(index == 49)
	{
		x = 6;
		y = 0;
		Matrix[x][y] = weight;
		return;
	}

	y = (index - 1) % NUM_TILES_PER_ROW;

	x = (index <= NUM_TILES_PER_ROW) ? (int)(index / 10) :
		(index <= NUM_TILES_PER_ROW * 2) ? (int)((index + 2) / 10) :
		(index <= NUM_TILES_PER_ROW * 3) ? (int)((index + 3) / 10) :
		(index <= 29) ? (int)((index + 5) / 10) :
		(index <= NUM_TILES_PER_ROW * 4) ? (int)(index / 10) :
		(index <= NUM_TILES_PER_ROW * 5) ? (int)((index + 7) / 10) :
		(index <= NUM_TILES_PER_ROW * 6) ? (int)((index + 9) / 10) :
		(index <= NUM_TILES_PER_ROW * 7) ? (int)((index + 10) / 10):  (int)((index + 13) / 10);

	Matrix[x][y] = weight;
}
