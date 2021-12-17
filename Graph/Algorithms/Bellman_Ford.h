#include <iostream>
#include "Graph\UndirectedGraph.h"
#include "Graph\DirectedGraph.h"

//meter todo este código a una funcion "BellmanFord" en directedgraph.h
//Se retorna un vector o array con las distancias del vertice origen a los demás


//Distancias, origen 0 y demás INF emulado con 10000

    
    
    Vertex<TV,TE>* actual = this->vertexes.find(id)->second;
    std::unordered_map<Vertex<TV, TE>*,int>  vertices_BellmanFord;
    TE* distancias= new TE[this->vertexes.size()]();
    
    //usado en dijkstra, por ver si será necesario en bellman
    vector<Vertex<TV,TE>*> adyacentes;
    
    //Inicializar con false e INF
    auto itr = this->vertexes.begin();
    int contador_arr=0;
    while(itr!=this->vertexes.end()){
      vertices_dijkstra.insert_or_assign(itr->second,contador_arr);
      distancias[contador_arr]=INT_MAX; //emular INF
      contador_arr++;
      ++itr;
    }
    contador_arr=0;

    //posicion correspondiente al vertice de origen.
    int idx_og=vertices_dijkstra.find(actual)->second;
    distancias[idx_og]=0;

    // Step 2: Relax all edges |V| - 1 times. A simple shortest
    // path from src to any other vertex can have at-most |V| - 1
    // edges
    for(int k=0;k<(this->vertexes.size())-1;k++){
      //O(E), depends on the number of edges
      itr = this->vertexes.begin();
      while(itr!=this->vertexes.end()){
        Vertex<TV,TE>* actual = itr->second();
        auto itr_list = actual->edges.begin();  
        while(itr_list!=actual->edges.end()){
          //idx related to src vertex of edge    
          int u = vertices_BellmanFord.find((*itr_list)->vertexes[0])->second;
          //idx related to dest vertex of edge
          int v = vertices_BellmanFord.find((*itr_list)->vertexes[1])->second;
          //edge weight
          TE peso = (*itr_list)->weight; 
          if (distancias[u] != INT_MAX && distancias[u] + peso < distancias[v]){
            distancias[v] = distancias[u] + peso;
          }
          ++itr_list;
        }  
        ++itr;
      }
    }
    return distancias;
    
    
    
    
    /*
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }
    */



    //return distancias;