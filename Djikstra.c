#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#define V 9

int minDistance(int dist[], bool sptSet[])//,int V)
{
	int min = INT_MAX, min_index=0, v;

	for (v = 0; v < V; v++)
		if (sptSet[v] == false && dist[v] < min)
			min = dist[v] ,min_index = v;

	return min_index;
}

int printSolution(int dist[], int n, int parent[],int tujuan)
{
	int src = tujuan;
	printf("Vertex\t Distance\tPath\n");
	for (int i = 1; i < n; i++)
	{
		printf("%2d -> %2d      %2d        ", src, i, dist[i]);
		printPath(parent, i);
		putchar('\n');
	}
}

void dijkstra(int graph[V][V], int src)//, int n)
{
	int dist[V]; // The output array. dist[i] will hold
				// the shortest distance from src to i

	// sptSet[i] will true if vertex i is included / in shortest
	// path tree or shortest distance from src to i is finalized
	bool sptSet[V];

	// Parent array to store shortest path tree
	int parent[V];

	// Initialize all distances as INFINITE and stpSet[] as false
	for (int i = 0; i < V; i++)
	{
		parent[src] = -1;
		dist[i] = INT_MAX;
		sptSet[i] = false;
	}

	// Distance of source vertex from itself is always 0
	dist[src]=0;

	// Find shortest path for all vertices
	for (int count = 0; count < V-1; count++)
	{
		// Pick the minimum distance vertex from the set of
		// vertices not yet processed. u is always equal to src
		// in first iteration.
		int u = minDistance(dist, sptSet);//, V);

		// Mark the picked vertex as processed
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the
		// picked vertex.
		for (int v = 0; v < V; v++)

			// Update dist[v] only if is not in sptSet, there is
			// an edge from u to v, and total weight of path from
			// src to v through u is smaller than current value of
			// dist[v]
			if (!sptSet[v] && graph[u][v] &&
				dist[u] + graph[u][v] < dist[v])
			{
				parent[v] = u;
				dist[v] = dist[u] + graph[u][v];
			}
	}
    //int src1=src;
	// print the constructed distance array
	printSolution(dist, V, parent,src);
}


void printPath(int parent[], int j)
{
	if (parent[j]==-1){ //j is source
        printf("%d ", j);
		return;
	}

	printPath(parent, parent[j]);
	printf("%d ", j);
}

int main()
{
    int v,x,y;
    //printf("Masukkan jumlah vertexnya :");
    //scanf("%d", &V);
    int graph[V][V];
    for(y=0;y<V;y++){
        for(x=0;x<V;x++){
            scanf("%d", &graph[y][x]);
        }
    }

	/* //Let us create the example graph discussed above
	int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
					{4, 0, 8, 0, 0, 0, 0, 11, 0},
					{0, 8, 0, 7, 0, 4, 0, 0, 2},
					{0, 0, 7, 0, 9, 14, 0, 0, 0},
					{0, 0, 0, 9, 0, 10, 0, 0, 0},
					{0, 0, 4, 0, 10, 0, 2, 0, 0},
					{0, 0, 0, 14, 0, 2, 0, 1, 6},
					{8, 11, 0, 0, 0, 0, 1, 0, 7},
					{0, 0, 2, 0, 0, 0, 6, 7, 0}
					};*/

	dijkstra(graph, 0);//, V);

	return 0;
}
