#include <iostream>
#include "Graph\UndirectedGraph.h"
#include "Graph\DirectedGraph.h"

//meter todo este código a una funcion "FloydWarshall" en directedgraph.h
int V = this->vertexes.size();

TE** distancias = new TE*[V];
//Matriz distancias = {10000} emulando INF
for(int i=0;i<V;i++){
  distancias[i] = new TE[V]; 
  for(int k=0;k<V;k++){
    distancias[i][k]=10000;
  }
}
//Diagonal = 0
for(int i=0;i<V;i++){
  a[i][i]=0;
}
//Manage indexes (assign each vertex* a index make things easy)
auto itr = this->vertexes.begin();
std::unordered_map<Vertex<TV, TE>*,int>  vertices_FloydW;
int counter=0;
while(itr!=this->vertexes.end()){
  vertices_FloydW.insert_or_assign(itr->second,counter);
  counter++;
  ++itr;
}
//Completar la matriz "distancias" con las distancias entre los vertices que son adyacentes. [i][j]:
//[i] -> origen
//[j] -> destino

itr = this->vertexes.begin();
while(itr!=vertexes.end()){
  Vertex<TV,TE>* temp = itr->second;
  auto itr_edge = temp->edges.begin();
  while(itr_edge!=temp->edges.end()){
    //(*itr_edge)->vertexes[1];
    int idx0 = vertices_FloydW.find(itr->second);
    int idx1 = vertices_FloydW.find(*(itr_edge)->vertexes[1]);
    distancias[idx0][idx1]=(*itr_edge)->weight;
  }
  ++itr;
}

//Triple for anidado para concluir el Floyd Warshall

for(int k=0;k<V;k++){
  for(int i=0;i<V;i++){
    for(int j=0;j<V;j++){
      if(distancias[i][j] > (distancias[i][k]+distancias[k][j])){
        distancias[i][j] = (distancias[i][k]+distancias[k][j]);
      }
    }
  }
}
//Se puede insertar un doble bucle anidado para imprimir los resultados de la matriz "distancias"
cout<<"A\n";
cout<<this->vertexes.find("A")->second<<endl;
int asd=vertices_FloydW.find(this->vertexes.find("A")->second)->second;
cout<<asd<<endl;

cout<<"B\n";
cout<<this->vertexes.find("B")->second<<endl;
asd=vertices_FloydW.find(this->vertexes.find("B")->second)->second;
cout<<asd<<endl;

cout<<"C\n";
cout<<this->vertexes.find("C")->second<<endl;
asd=vertices_FloydW.find(this->vertexes.find("C")->second)->second;
cout<<asd<<endl;

cout<<"D\n";
cout<<this->vertexes.find("D")->second<<endl;
asd=vertices_FloydW.find(this->vertexes.find("D")->second)->second;
cout<<asd<<endl;

for(int o=0;o<V;o++){
  for(int l=0;l<V;l++){
    cout<<distancias[o][l]<<" ";
  }
  cout<<endl;
}

return distancias;
