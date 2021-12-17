#ifndef NONDIRECTEDGRAPH_H
#define NONDIRECTEDGRAPH_H

#include "graph.h"
#include <iostream>
#include <queue>
using namespace std;

template<typename TV, typename TE>
class DirectedGraph : public Graph<TV, TE> {
public:
    DirectedGraph() {}
    ~DirectedGraph() = default;

    bool insertVertex(string id, TV vertex) {
        Vertex<TV, TE>* temp = new Vertex<TV, TE>;
        temp->data = vertex;
        this->vertexes.insert_or_assign(id, temp);
        return true;
    }

    bool createEdge(string id1, string id2, TE w) {
        auto temp1 = this->vertexes.find(id1);
        auto temp2 = this->vertexes.find(id2);
        if (temp1 != this->vertexes.end() && temp2 != this->vertexes.end()) {
            Edge<TV, TE>* adding = new Edge<TV, TE>;
            adding->weight = w;
            adding->vertexes[0] = temp1->second;
            adding->vertexes[1] = temp2->second;
            temp1->second->edges.push_back(adding);
            return true;
        }
        return false;
    }

    bool deleteEdge(string start, string end) {
        auto temp1 = this->vertexes.find(start);
        auto temp2 = this->vertexes.find(end);
        if (temp1 != this->vertexes.end() && temp2 != this->vertexes.end()) {
            for (auto it = temp1->second->edges.begin(); it != temp1->second->edges.end(); it++) {
                if ((*it)->vertexes[1] == temp2->second) {
                    temp1->second->edges.erase(it);
                    return true;
                }
            }
        }
        return false;
    }

    bool deleteVertex(string id) {
        auto temp = this->vertexes.find(id);
        if (temp != this->vertexes.end()) {
            for (auto it1 = this->vertexes.begin(); it1 != this->vertexes.end(); it1++) {
                if (it1->first != id) {
                    deleteEdge(it1->first, id);
                }
            }
            this->vertexes.erase(temp);
            return true;
        }
        return false;
    }

    TE& operator()(string start, string end) {
        auto temp1 = this->vertexes.find(start);
        auto temp2 = this->vertexes.find(end);
        if (temp1 != this->vertexes.end() && temp2 != this->vertexes.end()) {
            for (auto it = temp1->second->edges.begin(); it != temp1->second->edges.end(); it++) {
                if ((*it)->vertexes[1] == temp2->second) {
                    return (*it)->weight;
                }
            }
        }
        throw("not found");
    }

    float density() {
        float v, e;
        v = this->vertexes.size();
        e = 0;
        for (auto it = this->vertexes.begin(); it != this->vertexes.end(); it++) {
            e += it->second->edges.size();
        }
        return e / (v * (v - 1));
    }

    bool isDense(float threshold = 0.5) {
        return (density() >= threshold);
    }

    bool isConnected() {
        unordered_map<TV, TV> temp;
        int s = this->vertexes.size();
        auto it1 = this->vertexes.begin();

        temp.insert_or_assign(it1->second->data, it1->second->data);
        auto it2 = it1->second->edges.begin();
        while (it2 != it1->second->edges.end()) {
            if (temp.find((*it2)->vertexes[1]->data) == temp.end()) {
                temp.insert_or_assign((*it2)->vertexes[1]->data, (*it2)->vertexes[1]->data);
            }
            it2++;
        }
        it1++;

        while (it1 != this->vertexes.end() && temp.size() < s) {
            if (temp.find(it1->second->data) == temp.end()) {
                it2 = it1->second->edges.begin();
                while (it2 != it1->second->edges.end()) {
                    if (temp.find((*it2)->vertexes[1]->data) != temp.end()) {
                        temp.insert_or_assign((*it2)->vertexes[0]->data, (*it2)->vertexes[0]->data);
                        break;
                    }
                    it2++;
                }
            }
            if (temp.find(it1->second->data) != temp.end()) {
                it2 = it1->second->edges.begin();
                while (it2 != it1->second->edges.end()) {
                    if (temp.find((*it2)->vertexes[1]->data) == temp.end()) {
                        temp.insert_or_assign((*it2)->vertexes[1]->data, (*it2)->vertexes[1]->data);
                    }
                    it2++;
                }
            }
            it1++;
        }
        return (temp.size() == s);
    }

    bool isStronglyConnected() {
        unordered_map<TV, TV> temp;
        queue<Vertex<TV, TE>*> q;
        Vertex<TV, TE>* aux;
        int s = this->vertexes.size();
        for (auto it1 = this->vertexes.begin(); it1 != this->vertexes.end(); it1++) {
            q.push(it1->second);
            temp.insert_or_assign(it1->second->data, it1->second->data);
            while (!q.empty()) {
                aux = q.front();
                q.pop();
                auto it2 = aux->edges.begin();
                while (it2 != aux->edges.end()) {
                    if (temp.find((*it2)->vertexes[1]->data) == temp.end()) {
                        q.push((*it2)->vertexes[1]);
                        temp.insert_or_assign((*it2)->vertexes[1]->data, (*it2)->vertexes[1]->data);
                    }
                    it2++;
                }
            }
            if (temp.size() < s) {
                return false;
            }
            temp.clear();
        }
        return true;
    }

    bool empty() {
        return (this->vertexes.size() == 0);
    }

    void clear() {
        this->vertexes.clear();
    }


    void displayVertex(string id) {
        auto temp = this->vertexes.find(id);
        if (temp != this->vertexes.end()) {
            cout << temp->second->data;
            for (auto it = temp->second->edges.begin(); it != temp->second->edges.end(); it++) {
                cout << " -[" << (*it)->weight << "]-> " << (*it)->vertexes[1]->data << " ;";
            }
            cout << endl;
        }
    }

    bool findById(string id) {
        return (this->vertexes.find(id) != this->vertexes.end());
    }

    void display() {
        for (auto temp = this->vertexes.begin(); temp != this->vertexes.end(); temp++) {
            displayVertex(temp->first);
        }
    }

    TE* Dijkstra(string id) {
        //establecer vertice de origen
        int idx_og = 0;
        int contador_visitas = 0;
        Vertex<TV, TE>* actual = this->vertexes.find(id)->second;
        std::unordered_map<Vertex<TV, TE>*, int>  vertices_dijkstra;
        TE* distancias = new TE[this->vertexes.size()]();
        vector<bool> visited;
        vector<Vertex<TV, TE>*> adyacentes;
        vector<bool> actuales;

        auto itr = this->vertexes.begin();

        //Inicializar con false e INF
        while (itr != this->vertexes.end()) {
            vertices_dijkstra.insert_or_assign(itr->second, contador_visitas);
            distancias[contador_visitas] = 100000;
            visited.push_back(false);
            actuales.push_back(false);
            contador_visitas++;
            ++itr;
        }
        contador_visitas = 0;
        //posicion correspondiente al vertice de origen.
        idx_og = vertices_dijkstra.find(actual)->second;
        distancias[idx_og] = 0;
        visited[idx_og] = true;
        actuales[idx_og] = true;
        //recorrer aristas de "actual" y guardar las distancias
        while (contador_visitas < vertices_dijkstra.size()) {
            Vertex<TV, TE>* temp = new Vertex<TV, TE>;

            auto itr_list = actual->edges.begin();
            while (itr_list != actual->edges.end()) {

                temp = (*itr_list)->vertexes[1];

                if (visited[vertices_dijkstra.find(temp)->second] == false) {
                    adyacentes.push_back(temp);
                    visited[vertices_dijkstra.find(temp)->second] = true;
                }
                if (distancias[vertices_dijkstra.find(temp)->second] > distancias[vertices_dijkstra.find(actual)->second] + (*itr_list)->weight) {
                    distancias[vertices_dijkstra.find(temp)->second] = distancias[vertices_dijkstra.find(actual)->second] + (*itr_list)->weight;
                }
                ++itr_list;
            }

            visited[vertices_dijkstra.find(actual)->second] = true;
            contador_visitas++;
            //actualizar el vertice "actual"


            if (adyacentes.size() > 0) {
                temp = adyacentes[0];
            }
            int j = 0;
            TE flag = 100000;
            for (j = 0; j < adyacentes.size(); j++) {


                int idx1 = vertices_dijkstra.find(adyacentes[j])->second;

                if ((flag > distancias[idx1]) && (actuales[idx1] == false)) {
                    flag = distancias[idx1];
                    temp = adyacentes[j];
                }
            }
            //adyacentes.erase(adyacentes.begin() + (j - 1));
            actuales[vertices_dijkstra.find(temp)->second] = true;
            actual = temp;
        }
        /*
        cout << "Juliaca :\n";
        cout << this->vertexes.find("2792")->second << endl;
        int asd = vertices_dijkstra.find(this->vertexes.find("2792")->second)->second;
        cout << asd << endl;

        cout << "Puerto Maldonado\n";
        cout << this->vertexes.find("2808")->second << endl;
        asd = vertices_dijkstra.find(this->vertexes.find("2808")->second)->second;
        cout << asd << endl;

        cout << "Tumbes\n";
        cout << this->vertexes.find("2796")->second << endl;
        asd = vertices_dijkstra.find(this->vertexes.find("2796")->second)->second;
        cout << asd << endl;

        cout << "Huanuco\n";
        cout << this->vertexes.find("6067")->second << endl;
        asd = vertices_dijkstra.find(this->vertexes.find("6067")->second)->second;
        cout << asd << endl;

        cout << "Cajamarca\n";
        cout << this->vertexes.find("6066")->second << endl;
        asd = vertices_dijkstra.find(this->vertexes.find("6066")->second)->second;
        cout << asd << endl;
        cout << endl << endl << distancias[0] << " " << distancias[1] << " " << distancias[2] << " " << distancias[3] << " " << distancias[4] << endl;
        */
        return distancias;
    }

    //Floyd-Warshall
    TE** FloydWarshall() {
        int V = this->vertexes.size();

        TE** distancias = new TE * [V];
        //Matriz distancias = {10000} emulando INF
        for (int i = 0; i < V; i++) {
            distancias[i] = new TE[V];
            for (int k = 0; k < V; k++) {
                distancias[i][k] = 10000;
            }
        }
        //Diagonal = 0
        for (int i = 0; i < V; i++) {
            distancias[i][i] = 0;
        }
        //Manage indexes (assign each vertex* a index make things easy)
        auto itr = this->vertexes.begin();
        std::unordered_map<Vertex<TV, TE>*, int>  vertices_FloydW;
        int counter = 0;
        while (itr != this->vertexes.end()) {
            vertices_FloydW.insert_or_assign(itr->second, counter);
            counter++;
            ++itr;
        }
        //Completar la matriz "distancias" con las distancias entre los vertices que son adyacentes. [i][j]:
        //[i] -> origen
        //[j] -> destino

        itr = this->vertexes.begin();
        while (itr != this->vertexes.end()) {
            Vertex<TV, TE>* temp = itr->second;
            auto itr_edge = temp->edges.begin();
            while (itr_edge != temp->edges.end()) {
                //(*itr_edge)->vertexes[1];
                int idx0 = vertices_FloydW.find(itr->second)->second;
                int idx1 = vertices_FloydW.find((*itr_edge)->vertexes[1])->second;
                distancias[idx0][idx1] = (*itr_edge)->weight;
                itr_edge++;
            }
            ++itr;
        }

        //Triple for anidado para concluir el Floyd Warshall

        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (distancias[i][j] > (distancias[i][k] + distancias[k][j])) {
                        distancias[i][j] = (distancias[i][k] + distancias[k][j]);
                    }
                }
            }
        }
        //Se puede insertar un doble bucle anidado para imprimir los resultados de la matriz "distancias"
        /*
        cout<<"Juliaca\n";
        cout<<this->vertexes.find("2792")->second<<endl;
        int asd=vertices_FloydW.find(this->vertexes.find("2792")->second)->second;
        cout<<asd<<endl;

        cout<<"Puerto Maldonado\n";
        cout<<this->vertexes.find("2808")->second<<endl;
        asd=vertices_FloydW.find(this->vertexes.find("2808")->second)->second;
        cout<<asd<<endl;

        cout<<"Tumbes\n";
        cout<<this->vertexes.find("2796")->second<<endl;
        asd=vertices_FloydW.find(this->vertexes.find("2796")->second)->second;
        cout<<asd<<endl;

        cout<<"Huanuco\n";
        cout<<this->vertexes.find("6067")->second<<endl;
        asd=vertices_FloydW.find(this->vertexes.find("6067")->second)->second;
        cout<<asd<<endl;

        cout << "Cajamarca\n";
        cout << this->vertexes.find("6066")->second << endl;
        asd = vertices_FloydW.find(this->vertexes.find("6066")->second)->second;
        cout << asd << endl;


        for(int o=0;o<this->vertexes.size();o++){
          for(int l=0;l<this->vertexes.size();l++){
            cout<<distancias[o][l]<<" ";
          }
          cout<<endl;
        }
        */
        return distancias;
    }


    //BellmanFord
    TE* BellmanFord(string id) {
        Vertex<TV, TE>* actual = this->vertexes.find(id)->second;
        std::unordered_map<Vertex<TV, TE>*, int>  vertices_BellmanFord;
        TE* distancias = new TE[this->vertexes.size()]();

        //usado en dijkstra, por ver si será necesario en bellman
        vector<Vertex<TV, TE>*> adyacentes;

        //Inicializar con false e INF
        auto itr = this->vertexes.begin();
        int contador_arr = 0;
        while (itr != this->vertexes.end()) {
            vertices_BellmanFord.insert_or_assign(itr->second, contador_arr);
            distancias[contador_arr] = 10000; //emular INF
            contador_arr++;
            ++itr;
        }
        contador_arr = 0;

        //posicion correspondiente al vertice de origen.
        int idx_og = vertices_BellmanFord.find(actual)->second;
        distancias[idx_og] = 0;

        // Step 2: Relax all edges |V| - 1 times. A simple shortest
        // path from src to any other vertex can have at-most |V| - 1
        // edges
        for (int k = 0; k < (this->vertexes.size()) - 1; k++) {
            //O(E), depends on the number of edges
            itr = this->vertexes.begin();
            while (itr != this->vertexes.end()) {
                Vertex<TV, TE>* actual = itr->second;
                auto itr_list = actual->edges.begin();
                while (itr_list != actual->edges.end()) {
                    //idx related to src vertex of edge    
                    int u = vertices_BellmanFord.find((*itr_list)->vertexes[0])->second;
                    //idx related to dest vertex of edge
                    int v = vertices_BellmanFord.find((*itr_list)->vertexes[1])->second;
                    //edge weight
                    TE peso = (*itr_list)->weight;
                    if (distancias[u] != 10000 && distancias[u] + peso < distancias[v]) {
                        distancias[v] = distancias[u] + peso;
                    }
                    ++itr_list;
                }
                ++itr;
            }
        }
        /*
        cout<<"Juliaca\n";
        cout<<this->vertexes.find("2792")->second<<endl;
        int asd=vertices_BellmanFord.find(this->vertexes.find("2792")->second)->second;
        cout<<asd<<endl;

        cout<<"Puerto Maldonado\n";
        cout<<this->vertexes.find("2808")->second<<endl;
        asd=vertices_BellmanFord.find(this->vertexes.find("2808")->second)->second;
        cout<<asd<<endl;

        cout<<"Tumbes\n";
        cout<<this->vertexes.find("2796")->second<<endl;
        asd=vertices_BellmanFord.find(this->vertexes.find("2796")->second)->second;
        cout<<asd<<endl;

        cout<<"Huanuco\n";
        cout<<this->vertexes.find("6067")->second<<endl;
        asd=vertices_BellmanFord.find(this->vertexes.find("6067")->second)->second;
        cout<<asd<<endl;

        cout << "Cajamarca\n";
        cout << this->vertexes.find("6066")->second << endl;
        asd = vertices_BellmanFord.find(this->vertexes.find("6066")->second)->second;
        cout << asd << endl;

        for(int f=0;f<this->vertexes.size();f++){
          cout<<distancias[f]<<" ";
        }
        */

        return distancias;
    }
};


#endif