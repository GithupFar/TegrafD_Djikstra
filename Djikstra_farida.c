#include <stdio.h>
#include <limits.h> //define INT_MAX
#include <stdbool.h>
#define V 100 //maximal vertex 100

int jarakTerpendek(int dist[], bool sptSet[],int n) //membandingkan jarak path2 sampai menemukan shortest path
{
    int min = INT_MAX, min_index=0, v;
    for (v = 0; v < n; v++)
        if (sptSet[v] == false && dist[v] < min){
            min = dist[v] ;
            min_index = v;
        }
    return min_index;
}

void printLintasan(int parent[], int j) //j is source
{
    if (parent[j]==-1){
        printf("%d ", j);
        return;
    }
    printLintasan(parent, parent[j]);
    printf("%d ", j);
}

void print(int dist[], int n, int parent[],int awal,int akhir) //print path yang menjadi alternatif
{
    int asal = awal;
    printf("Vertex\t Bobot\t\tLintasan\n");
    for (int i = 1; i < akhir+1; i++)
    {
        if(i!=awal&&i==akhir) {
            printf("%2d -> %2d      %2d        ", asal, i, dist[i]);
            printLintasan(parent, i);
            putchar('\n');
        }
    }
}

void dijkstra(int graph[V][V], int awal,int akhir, int n)
{
    int jarak[V]; //tempat shortest path
    bool flag[V]; //flag untuk vertex yang sudah dikunjungi
    int parent[V]; // Parent array to store shortest path tree
    
    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < n; i++) //inisialisasikan semua vertex belum pernah dikunjungi
    {
        parent[awal] = -1;
        jarak[i] = INT_MAX;
        flag[i] = false;
    }
    
    jarak[awal]=0; //inisialisai awal distance 0
    
    // Find shortest path for all vertices
    for (int count = 0; count < n-1; count++)
    {
        int u = jarakTerpendek(jarak, flag,n);
        
        flag[u] = true;
        
        for (int v = 0; v < n; v++)
            //jika belum masuk flag, bobotnya lebih sedikit dari distance update it
            if (!flag[v] && graph[u][v] && jarak[u] + graph[u][v] < jarak[v])
            {
                parent[v] = u;
                jarak[v] = jarak[u] + graph[u][v]; //update isi dist[v]
            }
    }
    print(jarak,n,parent,awal,akhir);
}

int main()
{
    int j,i,awal,akhir,n,graph[V][V];
    printf("Masukkan jumlah vertexnya : ");
    scanf("%d", &n);
    if (n>0) {
        printf("Masukkan bobot pada adjacency matrix:\n");
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                scanf("%d", &graph[i][j]);
            }
        }
    }else return 0;
    
    printf("Masukkan vertex yang menjadi tujuan awal: ");
    scanf("%d",&awal);
    printf("Masukkan vertex yang menjadi tujuan akhir: ");
    scanf("%d",&akhir);
    
    if (akhir>=n) printf("Vertex hanya sampai %d\n", n-1);
    else dijkstra(graph, awal, akhir, n);
    
    return 0;
}
