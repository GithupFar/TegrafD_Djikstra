#include <stdio.h>
#include <limits.h> //define INT_MAX
#include <stdbool.h>
#define V 100 //maximal vertex 100

int minDistance(int dist[], bool sptSet[],int n) //membandingkan jarak path2 sampai menemukan shortest path
{
    int min = INT_MAX, min_index=0, v;
    for (v = 0; v < n; v++)
        if (sptSet[v] == false && dist[v] < min){
            min = dist[v] ;
            min_index = v;
        }
    return min_index;
}

void printPath(int parent[], int j) //j is source
{
    if (parent[j]==-1){
        printf("%d ", j);
        return;
    }
    printPath(parent, parent[j]);
    printf("%d ", j);
}

void printSolution(int dist[], int n, int parent[],int tujuan,int akhir) //print path yang menjadi alternatif
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
    int dist[V]; //tempat shortest path

    bool sptSet[V]; //flag untuk vertex yang sudah dikunjungi

    int parent[V]; // Parent array to store shortest path tree

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < n; i++) //inisialisasikan semua vertex belum pernah dikunjungi
    {
        parent[awal] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[awal]=0; //inisialisai awal distance 0

    // Find shortest path for all vertices
    for (int count = 0; count < n-1; count++)
    {
        int u = minDistance(dist, sptSet,n);

        sptSet[u] = true;

        for (int v = 0; v < n; v++)
            //jika belum masuk flag, bobotnya lebih sedikit dari distance update it
            if (!sptSet[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v]; //update isi dist[v]
            }
    }
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
    printf("Masukkan vertex yang menjadi tujuan akhir: ");
    scanf("%d",&akhir);
    if (akhir>=n) {
        printf("Vertex hanya sampai %d\n", n-1);
    }
    else dijkstra(graph, awal, akhir, n);

    return 0;
}
