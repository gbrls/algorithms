/*

- Gabriel Schneider - 2019 

This code generates the adjacency matrix of a Qn graph,
traverses it and then prints a path inside it. Such path is
a Gray code (the difference from one vertex to the next, only changes
one bit) and should be a Hamiltonian path.

TODO: Change the algorithm to produce a Hamiltonian cycle, instead of a path.
*/

#include <stdio.h>

#define DIM 3
#define MAX (1<<DIM)

void printb(int n){
    for(int i=1;i<=DIM;i++) putchar((n&(1<<(DIM-i)))?'1':'0');
}

void build(int n, int adj[MAX][MAX], int visited[MAX]){
    if(visited[n]) return;
    visited[n]=1;

    for(int i=0;i<3;i++){
        int x = n^(1<<i);
        adj[n][x]=1;
        adj[x][n]=1;

        build(x,adj,visited);
    }
}

void _build(int adj[MAX][MAX]){
    int visited[MAX]={0};
    build(0,adj,visited);
}

void dfs(int curr, int ptr, int arr[MAX], int adj[MAX][MAX], int visited[MAX]){
    arr[ptr++]=curr; 
    visited[curr]=1;

    for(int i=0;i<MAX;i++){
        if(adj[curr][i] && !visited[i]){
            dfs(i,ptr,arr,adj,visited);
        }
    }
}

void _dfs(int curr, int arr[MAX], int adj[MAX][MAX]){
    int visited[MAX]={};
    int ptr=0;
    dfs(curr,ptr,arr,adj,visited);
}

int main() {

    int adj[MAX][MAX]={0}, path[MAX]={};
    _build(adj);

    printf("Adjacency matrix of the Qn graph:\n");
    for(int i=0;i<MAX;i++){
        for(int j=0;j<MAX;j++){
            printf("%d%c",adj[i][j],j==MAX-1?'\n':' ');
        }
    }

    printf("A path in the Qn graph, such path is a gray code:\n");
    _dfs(0,path,adj);
    for(int i=0;i<MAX;i++){
        printb(path[i]);
        putchar('\n');
    }

    return 0;
}
