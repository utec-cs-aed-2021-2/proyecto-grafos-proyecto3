#include <iostream>
#include <string>
#include "Graph\UndirectedGraph.h"
#include <queue>
using namespace std;


template<typename TV, typename TE>
class prim {
public: //private:
    vector<pair<TE, Edge<TV, TE>*>> prim_aristas;
    std::unordered_map<Vertex<TV, TE>*, int>  vertexes_prim;

    //usado para los DisjointSets y resultados apply
    //vector<int> parent;
    vector<Vertex<TV, TE>*> prim_nodos;
    vector<Edge<TV, TE>*> prim_edges; //usarse en funcion apply

public:
    prim(UnDirectedGraph<TV, TE>* grafo, string id) {
        this->prim_nodos = grafo->copyVertexes();
        ///relating vertexes to idx
        for (int i = 0; i < prim_nodos.size(); i++) {
            this->vertexes_prim.insert_or_assign(prim_nodos[i], i);
        }

        ////
        int V = grafo->vertexes.size();
        priority_queue<pair<TE, Vertex<TV, TE>*>, vector<pair<TE, Vertex<TV, TE>*>>, greater<pair<TE, Vertex<TV, TE>*>>> cola_vertex;
        vector<TE> distancias(V);
        vector<Vertex<TV, TE>*> parent(V);
        vector<bool> visitados(V);
        auto itr = grafo->vertexes.begin();
        int count = 0;
        int idx = 0;
        while (itr != grafo->vertexes.end()) {
            idx = this->vertexes_prim.find(itr->second)->second;
            distancias[idx] = 10000;
            parent[idx] = nullptr;
            visitados[idx] = false;
            cola_vertex.push({ distancias[idx],itr->second });
            itr++;
            count++;
        }
        Vertex<TV, TE>* temp_vertex = grafo->vertexes.find(id)->second;
        idx = this->vertexes_prim.find(temp_vertex)->second;
        distancias[idx] = 0;
        cola_vertex.push({ distancias[idx],temp_vertex });
        while (cola_vertex.empty() == false) {
            pair<TE, Vertex<TV, TE>*> temp_par;
            temp_par = cola_vertex.top();
            cola_vertex.pop();
            auto itr_list = temp_par.second->edges.begin();
            while (itr_list != temp_par.second->edges.end()) {
                Vertex<TV, TE>* temp2;
                if (temp_par.second == (*itr_list)->vertexes[0]) {
                    temp2 = (*itr_list)->vertexes[1];
                }
                else {
                    temp2 = (*itr_list)->vertexes[0];
                }
                int id_temp2 = this->vertexes_prim.find(temp2)->second;
                if (visitados[id_temp2] == false && distancias[id_temp2] > (*itr_list)->weight) {
                    parent[id_temp2] = temp_par.second;
                    visitados[id_temp2] = true;
                    distancias[id_temp2] = (*itr_list)->weight;
                    cout << distancias[id_temp2] << endl;
                    cola_vertex.push({ distancias[id_temp2],temp2 });
                }
                itr_list++;
            }
        }
        cout << grafo->vertexes.find(id)->second << "\n";
        auto itr_ver = grafo->vertexes.begin();
        while (itr_ver != grafo->vertexes.end()) {
            cout << itr_ver->first << " " << itr_ver->second << " " << this->vertexes_prim.find(itr_ver->second)->second << endl;
            itr_ver++;
        }
        for (int i = 0; i < V; i++) {
            cout << distancias[i] << " ";
        }
        cout << "\n";
        for (int i = 0; i < V; i++) {
            cout << parent[i] << " ";
        }
        cout << "\n";
    }
};
