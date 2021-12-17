#include <iostream>
#include <string>
#include "Graph\UndirectedGraph.h"
#include <queue>

using namespace std;


template<typename TV, typename TE>
class kruskal {
public: //private:
    vector<pair<TE, Edge<TV, TE>*>> kruskal_aristas;
    std::unordered_map<Vertex<TV, TE>*, int>  vertexes;

    //usado para los DisjointSets y resultados apply
    vector<int> parent;
    vector<Vertex<TV, TE>*> kruskal_nodos;
    vector<Edge<TV, TE>*> kruskal_edges; //usarse en funcion apply

public:
    kruskal(UnDirectedGraph<TV, TE>* grafo) {
        this->kruskal_aristas = grafo->sortEdges();
        this->kruskal_nodos = grafo->copyVertexes();

        for (int i = 0; i < kruskal_nodos.size(); i++) {
            this->vertexes.insert_or_assign(kruskal_nodos[i], i);
        }

        //DisjointSets para realizar MST por kruskal
        makeSet(kruskal_nodos.size());

        int cm = kruskal_nodos.size();
        int pos = 0;
        while (cm != 1 && pos < kruskal_aristas.size()) {

            Edge<TV, TE>* temp = kruskal_aristas[pos].second;

            int id0 = this->vertexes.find(temp->vertexes[0])->second;
            int id1 = this->vertexes.find(temp->vertexes[1])->second;
            if (find_set(id0) != find_set(id1)) {
                union_set(id0, id1);
                kruskal_edges.push_back(temp);
                cm--;
            }
            pos++;
        }

    }

    UnDirectedGraph<TV, TE> apply() {
        UnDirectedGraph<TV, TE> MST;

        //Insert Vertexes
        for (int i = 0; i < kruskal_nodos.size(); i++) {
            TV value = kruskal_nodos[i]->data;
            string id = std::to_string(i);
            MST.insertVertex(id, value);
        }

        //Inser Edges
        for (int j = 0; j < kruskal_edges.size(); j++) {
            kruskal_edges[j];
            Edge<TV, TE>* temp = kruskal_edges[j];
            int id1 = this->vertexes.find(temp->vertexes[0])->second;
            int id2 = this->vertexes.find(temp->vertexes[1])->second;
            string id1_str = std::to_string(id1);
            string id2_str = std::to_string(id2);
            MST.createEdge(id1_str, id2_str, temp->weight);
        }

        return MST;
    }



private:
    void makeSet(int n) {
        parent.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find_set(int v) {
        if (v == parent[v]) {
            return v;
        }
        return parent[v] = find_set(parent[v]);
    }

    void union_set(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        parent[b] = a;
    }

};
