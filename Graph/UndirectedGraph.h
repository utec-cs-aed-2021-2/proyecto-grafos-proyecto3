#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include "graph.h"
#include <iostream>
#include <queue>
using namespace std;

template<typename TV, typename TE>
class UnDirectedGraph : public Graph<TV, TE> {
public: //private:
  //list<Edge<TV,TE>*> aristas;

public:
    bool insertVertex(string id, TV vertex) {
        Vertex<TV, TE>* temp = new Vertex<TV, TE>(vertex);
        this->vertexes.insert_or_assign(id, temp);
        return true;
    }

    bool createEdge(string id1, string id2, TE w) {
        //Arista no puede tener el mismo vértice en los 2 extremos
        if (id1 == id2) {
            return false;
        }
        auto v1 = this->vertexes.find(id1);
        auto v2 = this->vertexes.find(id2);
        //inicializar arista
        Edge<TV, TE>* arista = new Edge<TV, TE>(this->vertexes.find(id1)->second, this->vertexes.find(id2)->second, w);
        //Insertar la arista en las listas de los vértices correspondientes
        this->vertexes.find(id1)->second->edges.push_back(arista);
        this->vertexes.find(id2)->second->edges.push_back(arista);
        //this->aristas.push_back(arista);
        return true;
    }

    bool createEdge_v1(string id1, string id2, TE w) {
        //Arista no puede tener el mismo vértice en los 2 extremos
        if (id1 == id2) {
            return false;
        }
        auto v1 = this->vertexes.find(id1);
        auto v2 = this->vertexes.find(id2);
        //inicializar arista
        Edge<TV, TE>* arista = new Edge<TV, TE>(v1->second, v2->second, w);
        //Insertar la arista en las listas de los vértices correspondientes
        v1->second->edges.push_back(arista);
        //this->aristas.push_back(arista);
        return true;
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



    bool deleteEdge(string start, string end) {
        auto itr_start = this->vertexes.find(start)->second->edges.begin();
        auto itr_end = this->vertexes.find(end)->second->edges.begin();
        while (itr_start != this->vertexes.find(start)->second->edges.end()) {
            if ((*itr_start)->vertexes[0] == this->vertexes.find(end)->second || (*itr_start)->vertexes[1] == this->vertexes.find(end)->second) {
                this->vertexes.find(start)->second->edges.erase(itr_start);
                break;
            }
            else {
                std::advance(itr_start, 1);
            }
        }

        while (itr_end != this->vertexes.find(end)->second->edges.end()) {
            if ((*itr_end)->vertexes[0] == this->vertexes.find(end)->second || (*itr_end)->vertexes[1] == this->vertexes.find(end)->second) {
                this->vertexes.find(end)->second->edges.erase(itr_end);
                break;
            }
            else {
                std::advance(itr_end, 1);
            }
        }
        return true;
    }

    TE& operator()(string start, string end) {
        Vertex<TV, TE>* v1 = new Vertex<TV, TE>();
        Vertex<TV, TE>* v2 = new Vertex<TV, TE>();

        v1 = this->vertexes.find(start)->second;
        v2 = this->vertexes.find(end)->second;
        //si alguno no existe
        if (this->vertexes.find(start) == this->vertexes.end() || this->vertexes.find(end) == this->vertexes.end()) {
            throw("Uno de los vertices no existe en este grafo");
        }
        else {

            auto iterador = v1->edges.begin();

            while (iterador != v1->edges.end()) {
                if ((*iterador)->vertexes[0] == v2 || (*iterador)->vertexes[1] == v2) {

                    return (*iterador)->weight;
                }
                else {
                    std::advance(iterador, 1);
                }
            }
            throw("Vertices no conectados");
        }
    }

    float density() {
        if (this->vertexes.size() == 0) {
            return 0;
        }

        double vertexCount = this->vertexes.size();
        double edgeCount = 0;
        auto itr_vect = this->vertexes.begin();
        typename list<Edge<TV, TE>*>::iterator itr_list;


        //Contar cuantas aristas hay en el grafo
        while (itr_vect != this->vertexes.end()) {
            itr_list = (*itr_vect).second->edges.begin();
            while (itr_list != (*itr_vect).second->edges.end()) {
                edgeCount = edgeCount + 1;
                std::advance(itr_list, 1);
            }
            std::advance(itr_vect, 1);
        }
        edgeCount = edgeCount / 2; //evitar la redundancia

        //Calcular la densidad
        float result = 0;
        //formula para densidad en grafo NO DIRIGIDO
        result = ((2 * edgeCount) / (vertexCount * (vertexCount - 1)));
        return result;
    }

    bool isDense(float threshold = 0.6) {
        if (this->density() < threshold) {
            return false;
        }
        else {
            return true;
        }
    }

    bool isConnected() {
        Vertex<TV, TE>* aux;
        int visitados = 0;
        queue<Vertex<TV, TE>*> cola;
        typename list<Edge<TV, TE>*>::iterator itr;
        typename unordered_map<string, Vertex<TV, TE>*>::iterator itr_vert;

        std::unordered_map<Vertex<TV, TE>*, bool>  checking;
        cola.push(this->vertexes.begin()->second);

        while (!cola.empty()) {
            aux = cola.front();
            itr = aux->edges.begin();

            while (itr != aux->edges.end()) {

                if (checking.find(aux) == checking.end()) {
                    if ((*itr)->vertexes[0] == aux) {
                        cola.push((*itr)->vertexes[1]);

                    }
                    else if ((*itr)->vertexes[1] == aux) {
                        cola.push((*itr)->vertexes[0]);
                    }
                }
                ++itr;
            }
            checking.insert_or_assign(aux, true);
            cola.pop();
        }

        if (checking.size() == this->vertexes.size()) {
            return true;
        }
        else {
            return false;
        }
    }

    bool isStronglyConnected() {
        Vertex<TV, TE>* aux;
        int visitados = 0;
        queue<Vertex<TV, TE>*> cola;
        typename list<Edge<TV, TE>*>::iterator itr;
        typename unordered_map<string, Vertex<TV, TE>*>::iterator itr_vert;

        std::unordered_map<Vertex<TV, TE>*, bool>  checking;
        cola.push(this->vertexes.begin()->second);

        while (!cola.empty()) {
            aux = cola.front();
            itr = aux->edges.begin();

            while (itr != aux->edges.end()) {

                if (checking.find(aux) == checking.end()) {
                    if ((*itr)->vertexes[0] == aux) {
                        cola.push((*itr)->vertexes[1]);

                    }
                    else if ((*itr)->vertexes[1] == aux) {
                        cola.push((*itr)->vertexes[0]);
                    }
                }
                ++itr;
            }
            checking.insert_or_assign(aux, true);
            cola.pop();
        }

        if (checking.size() == this->vertexes.size()) {
            return true;
        }
        else {
            return false;
        }
    }

    bool empty() {
        if (this->vertexes.size() == 0) {
            return true;
        }
        else {
            return false;
        }
    }

    void clear() {
        auto iterador = this->vertexes.begin();
        for (auto it = this->vertexes.begin(); it != this->vertexes.end(); ) {
            it = this->vertexes.erase(it);
        }
    }

    void displayVertex(string id) {
        auto temp = this->vertexes.find(id);
        Vertex<TV, TE>* temp_vertex = this->vertexes.find(id)->second;
        if (temp != this->vertexes.end()) {
            cout << temp->second->data << ": ";
            for (auto it = temp->second->edges.begin(); it != temp->second->edges.end(); it++) {
                if (temp->second == (*it)->vertexes[0]) {
                    temp_vertex = (*it)->vertexes[1];
                }
                else {
                    temp_vertex = (*it)->vertexes[0];
                }
                cout << "<-[" << (*it)->weight << "]-> " << temp_vertex->data << " ;";
            }
            cout << endl;
        }
    }

    bool findById(string id) {
        //verificar si el nodo existe ig
        auto iterador = this->vertexes.find(id);
        if (iterador == this->vertexes.end()) {
            return false;
        }
        else {
            return true;
        }
    }

    void display() {
        for (auto temp = this->vertexes.begin(); temp != this->vertexes.end(); temp++) {
            displayVertex(temp->first);
        }
    }

    vector<pair<TE, Edge<TV, TE>*>> sortEdges() {
        auto itr1 = this->vertexes.begin();
        std::unordered_map<Edge<TV, TE>*, bool>  visited;
        vector<pair<TE, Edge<TV, TE>*>> lista_aristas;

        while (itr1 != this->vertexes.end()) {
            auto itr2 = itr1->second->edges.begin();
            while (itr2 != itr1->second->edges.end()) {
                visited.insert_or_assign((*itr2), true);
                ++itr2;
            }
            ++itr1;
        }
        auto itr3 = visited.begin();
        while (itr3 != visited.end()) {
            lista_aristas.push_back({ itr3->first->weight,itr3->first });
            ++itr3;
        }
        std::sort(lista_aristas.begin(), lista_aristas.end());
        return lista_aristas;
    }

    vector<Vertex<TV, TE>*> copyVertexes() {

        vector<Vertex<TV, TE>*> retorno;

        auto itr = this->vertexes.begin();
        while (itr != this->vertexes.end()) {
            /*TV value = itr->second->data;
            Vertex<TV,TE> *temp =  new Vertex<TV,TE>(value);*/
            Vertex<TV, TE>* temp = itr->second;
            retorno.push_back(temp);
            ++itr;
        }
        return retorno;
    }

    //****************SHORTEST PATH**************************//
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
                //UndirectedGraph stuff
                if (actual == (*itr_list)->vertexes[0]) {
                    temp = (*itr_list)->vertexes[1];
                }
                else {
                    temp = (*itr_list)->vertexes[0];
                }

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
        cout<<"Juliaca :\n";
        cout<<this->vertexes.find("2792")->second<<endl;
        int asd=vertices_dijkstra.find(this->vertexes.find("2792")->second)->second;
        cout<<asd<<endl;

        cout<<"Puerto Maldonado\n" ;
        cout<<this->vertexes.find("2808")->second<<endl;
        asd=vertices_dijkstra.find(this->vertexes.find("2808")->second)->second;
        cout<<asd<<endl;

        cout<<"Tumbes\n";
        cout<<this->vertexes.find("2796")->second<<endl;
        asd=vertices_dijkstra.find(this->vertexes.find("2796")->second)->second;
        cout<<asd<<endl;

        cout<<"Huanuco\n";
        cout<<this->vertexes.find("6067")->second<<endl;
        asd=vertices_dijkstra.find(this->vertexes.find("6067")->second)->second;
        cout<<asd<<endl;

        cout << "Cajamarca\n";
        cout << this->vertexes.find("6066")->second << endl;
        asd = vertices_dijkstra.find(this->vertexes.find("6066")->second)->second;
        cout << asd << endl;
        cout << endl << endl << distancias[0] << " " << distancias[1] << " " << distancias[2] << " " << distancias[3] << " " << distancias[4] << endl;
        */
        return distancias;
    }


    /*

    //Notas:

    -"distances" sera un vector con pair<TE,Vertex<TV,TE>>
    -visited será bool
    -vertexes será un vector<Vertex<TV,TE>> que guardará en orden los vértices del unordered_map "vertexes" del objeto UndirectedGraph
    -Similar a disjointSets, serán 3 vectores separados pero que están coordinados en los indices, así cuando index=1, se tratará siempre del mismo nodo.
    -para buscar a los vertices adyacentes de cada vertice, se consultará en su lista de adyacencia.
    -Crear funcion getWeight(Vertex<TV,TE>* v1,Vertex<TV,TE>* v2) que retorne el peso de las aristas deseadas. en uso la funcion se verá asi: getWeight(vertexes[i],vertexes[j])
    -Funcion minDistance(vector,vector) que servirá para encontrar un vértice NO VISITADO cuya distancia sea la menor.
    -En lugar de un while(anyFalse), se usará un contador que aumentará cada vez que se coloque un nodo visitado, cuando este contador sea igual a la cantidad de nodos, se terminará el while: while(contador<vertexes.size()+3)
    */



};

#endif