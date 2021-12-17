#include <iostream>
#include "Graph/UndirectedGraph.h"
#include "Graph/DirectedGraph.h"
#include "kruskal.h"
#include "prim2.h"
#include "parse_json.h"
#include "tester.h"
#include "astar.h"
#include "bfs.h"

using namespace std;

UnDirectedGraph<string, double> ugrafo_kruskal;


void test_undirected(parser<string, double>* datos) {
    cout << "\nTEST - UNDIRECTED GRAPH\n";
    cout << "\nBasic Methods:\n\n";
    UnDirectedGraph<string, double> ugrafo;
    ASSERT(ugrafo.empty() == true, "The function empty is not working");
    datos->uGraphMake(ugrafo);
    //ugrafo.display();
    ASSERT(ugrafo.empty() == false, "The function empty is not working");
    ASSERT(ugrafo.isConnected() == true, "The function isConnected is not working");
    ASSERT(ugrafo.density() == 0.5, "The function density is not working");
    ASSERT(ugrafo.isDense() == false, "The function isDense is not working");
    ASSERT(ugrafo.findById("1776") == false, "The function findById is not working");

    cout << "\n\nTest - Grafo - Kruskal:\n\n";
    cout << "MST:\n";
    kruskal<string, double> sol_kruskal(&ugrafo);
    UnDirectedGraph<string, double> kruskal_ugrafo = sol_kruskal.apply();
    kruskal_ugrafo.display();

    double* test_dijkstra = new double[5]{ 17,0,7,4,14 };
    cout << "\n\nTest - Shortest Path:\n\n";
    cout << "Dikstra:\n";
    ASSERT((*ugrafo.Dijkstra("2796")) == *test_dijkstra, "The function Dijsktra is not working");
    ugrafo.clear();
    ASSERT(ugrafo.empty() == true, "The function empty is not working");

}

void test_directed(parser<string, double>* datos) {
    DirectedGraph<string, double> dgrafo;
    cout << "\n\nTEST - DIRECTED GRAPH\n\n";
    cout << "\nBasic Methods:\n\n";
    ASSERT(dgrafo.empty() == true, "The function empty is not working");
    datos->dGraphMake(dgrafo);
    dgrafo.display();
    ASSERT(dgrafo.empty() == false, "The function empty is not working");
    ASSERT(dgrafo.isConnected() == true, "The function isConnected is not working");
    ASSERT(dgrafo.density() == 0.5, "The function density is not working");
    ASSERT(dgrafo.isDense() == true, "The function isDense is not working");
    ASSERT(dgrafo.findById("1776") == false, "The function findById is not working");

    double* test_dijkstra = new double[5]{ 21,4,4,0,18 };
    cout << "\n\nTest - Shortest Path:\n\n";
    cout << "Dijkstra:\n";
    ASSERT((*dgrafo.Dijkstra("6066")) == *test_dijkstra, "The function Dijsktra is not working");

    double** floyd = dgrafo.FloydWarshall();
    double* test_floyd_0 = new double[5]{ 0,17,25,21,3 };
    double* test_floyd_1 = new double[5]{ 17,0,8,4,14 };
    double* test_floyd_2 = new double[5]{ 25,8,0,4,22 };
    double* test_floyd_3 = new double[5]{ 21,4,4,0,18 };
    double* test_floyd_4 = new double[5]{ 3,14,22,18,0 };

    cout << "\nFloyd-Warshall:\n\n";
    ASSERT(*floyd[0] == *test_floyd_0, "The function FloydWarshall is not working");
    ASSERT(*floyd[1] == *test_floyd_1, "The function FloydWarshall is not working");
    ASSERT(*floyd[2] == *test_floyd_2, "The function FloydWarshall is not working");
    ASSERT(*floyd[3] == *test_floyd_3, "The function FloydWarshall is not working");
    ASSERT(*floyd[4] == *test_floyd_4, "The function FloydWarshall is not working");

    double* bellmann_ford = new double[5]{ 3,14,22,18,0 };
    cout << "\nBellmann-Ford\n";
    ASSERT((*dgrafo.BellmanFord("2808")) == *bellmann_ford, "The function BellmanFord is not working");


    vector<double> heuristicas;
    heuristicas.push_back(30);
    heuristicas.push_back(25);
    heuristicas.push_back(5);
    heuristicas.push_back(0);
    heuristicas.push_back(5);
    AStar<string, double> AStar(dgrafo, "2792", "6066", heuristicas);
    cout << "\nAlgoritmo A*\n";
    cout << "\nCamino de Juliaca a Cajamarca\n";
    DirectedGraph<string, double> AStar_dgrafo = AStar.apply();
    AStar_dgrafo.display();

    BFS<string, double> BFS(dgrafo, "6067");
    cout << "\nAlgoritmo BFS\n";
    cout << "\nCamino desde Huanuco\n";
    DirectedGraph<string, double> BFS_dgrafo = BFS.apply();
    BFS_dgrafo.display();

    dgrafo.clear();
    ASSERT(dgrafo.empty() == true, "The function empty is not working");
}


int main() {
    cout << "Proyecto Final de Curso - Algoritmos y Estructura de datos\n";
    //Crear los datos en un objeto de la clase parser a partir de los datos del archivo json
    parser<string, double>* datos = new parser<string, double>();
    datos->read_file_Json();
    //Testeos
    test_undirected(datos);
    test_directed(datos);

    return 0;
}