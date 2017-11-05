//
//  main.c
//  graf-dijkstra algo
//
//  Created by Safira Vanillia Putri on 11/4/17.
//  Copyright © 2017 Safira Vanillia Putri. All rights reserved.
//

#include<stdio.h>
#define INFINITE 999
#define MAX 100

void dijkstra(int bobot[MAX][MAX],int n,int awal,int akhir);

int main() {
    int bobot[MAX][MAX],i,j,n,awal,akhir;
    printf("Masukkan jumlah vertex: ");
    scanf("%d",&n);

    if (n>0) {
        printf("Masukkan bobot pada adjacency matrix:\n");
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                
                scanf("%d", &bobot[i][j]);
            }
        }
    }else return 0;
    
    printf("\nMasukkan vertex awal: ");
    scanf("%d",&awal);
    printf("Masukkan vertex akhir: ");
    scanf("%d", &akhir);
    if (akhir>=n) {
        printf("Vertex hanya sampai %d\n", n-1);
    }else dijkstra(bobot,n,awal,akhir);
    
    return 0;
}

void dijkstra(int bobot[MAX][MAX],int n,int awal, int akhir) {
    
    int temp[MAX][MAX],jarak[MAX],pred[MAX],flag[MAX],jum,jarak_minim,vertex_selanjutnya,i,j;
    
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(bobot[i][j]==0) temp[i][j]=INFINITE;
            else temp[i][j]=bobot[i][j];
        }
    }
    
    for(i=0;i<n;i++) {
        jarak[i]=temp[awal][i];
        pred[i]=awal;
        flag[i]=0;
    }
    
    jarak[awal]=0;
    flag[awal]=1;
    jum=1;
    
    while(jum<n-1) {
        jarak_minim=INFINITE;
        
        //vertex selanjutnya ngasih vertex ke jarak minimum
        for(i=0;i<n;i++){
            if(jarak[i]<jarak_minim&&!flag[i]){
                jarak_minim=jarak[i];
                vertex_selanjutnya=i;
            }
        }
        
        //cek apa ada lintasan yang lebih baik lewat vertex selanjutnya
        flag[vertex_selanjutnya]=1;
        for(i=0;i<n;i++){
            if(!flag[i]){
                if(jarak_minim+temp[vertex_selanjutnya][i]<jarak[i]) {
                    jarak[i]=jarak_minim+temp[vertex_selanjutnya][i];
                    pred[i]=vertex_selanjutnya;
                }
            }
        }
        jum++;
    }
    
    for(i=0;i<akhir+1;i++) {
        if(i!=awal) {
            printf("\n\nBobot ke vertex %d=%d\n",i,jarak[i]);
            printf("Lintasan : %d",i);
            
            j=i;
            while (j!=awal) {
                j=pred[j];
                printf("<-%d",j);
            }
            printf("\n");
        }
    }
}
