#include <iostream>
#include <vector>
using namespace std;

vector<int> parent;

void makeSet(int n){
  for(int i=0;i<n;i++){
    parent[i]=i;
  }
}

int find_set(int v){
  if(v==parent[V]){
    return v;
  }
  return parent[v] = find_set(parent[v]);
}

void union_set(int a,int b){
  a=find_set(a);
  b=find_set(b);
  parent[b]=a;  
}

