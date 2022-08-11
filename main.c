#include "project.h"

int main(){
	Graph newChessboardForKnight();
	Graph g = buildKnightGraph();
	int ** adjacencyMatrix = AdjacencyMatrix(g);
	int input;
	while(input != 4){
		clrscr();
		cyan,printf("\n\n\t\t\t=== MENU ===\n\n"),reset;
		yellow,printf("[1] Print the graph\n");
		printf("[2] Print optimal zone\n");
		printf("[3] Knight's Tour\n");
		printf("[4] Exit\n");
		puts("Make your choice !\n"),reset;
		scanf("%d",&input);
		switch(input)
		{
			case 1:
				printGraph(g);
			break;
			case 2:
				printOptimalZone(g);
			break;
			case 3:
			{
				int src;
				do{
				red,printf("Enter the number for the starting case between 1 to 64:\n"),reset;
				scanf("%d",&src);
				}while(src < 1 || src > 64);
				knightTour(adjacencyMatrix, src);
				
			}
			break;
			case 4: 
			break;
			default:
				break;
		}
		cyan,printf("\nReturning to main menu..."),reset;
		getchar();
		getchar();
	}
	
	return 0;
}
