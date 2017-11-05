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

void printPath(int parent[], int j)
{
    if (parent[j]==-1){ //j is source
        printf("%d ", j);
        return;
    }
    
    printPath(parent, parent[j]);
    printf("%d ", j);
}

void printSolution(int dist[], int n, int parent[],int tujuan,int akhir)
{
    int src = tujuan;
    printf("Vertex\t Distance\tPath\n");
    for (int i = 1; i < akhir+1; i++)
    {
        if(i!=tujuan) {
        printf("%2d -> %2d      %2d        ", src, i, dist[i]);
        printPath(parent, i);
        putchar('\n');
        }
    }
}

void dijkstra(int graph[V][V], int awal,int akhir, int n)
{
    int dist[V]; // The output array. dist[i] will hold
				// the shortest distance from src to i
    
    // sptSet[i] will true if vertex i is included / in shortest
    // path tree or shortest distance from src to i is finalized
    bool sptSet[V];
    
    // Parent array to store shortest path tree
    int parent[V];
    
    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < n; i++)
    {
        parent[awal] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
    
    // Distance of source vertex from itself is always 0
    dist[awal]=0;
    
    // Find shortest path for all vertices
    for (int count = 0; count < n-1; count++)
    {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to src
        // in first iteration.
        int u = minDistance(dist, sptSet);//, V);
        
        // Mark the picked vertex as processed
        sptSet[u] = true;
        
        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < n; v++)
            
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
    printSolution(dist, n, parent, awal,akhir);
}

int main()
{
    int x,y,awal,akhir,n;
    int graph[V][V];
    printf("Masukkan jumlah vertexnya : ");
    scanf("%d", &n);
    if (n>0) {
        printf("Masukkan bobot pada adjacency matrix:\n");
        for(y=0;y<n;y++){
            for(x=0;x<n;x++){
                
                scanf("%d", &graph[y][x]);
            }
        }
    }else return 0;
    
    printf("Masukkan vertex yang menjadi tujuan awal: ");
    scanf("%d",&awal);
    printf("Masukkan vertex yang menjadi tujuan awal: ");
    scanf("%d",&akhir);
    if (akhir>=n) {
        printf("Vertex hanya sampai %d\n", n-1);
    }
    else dijkstra(graph, awal, akhir, n);
    
    return 0;
}
