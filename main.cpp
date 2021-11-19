#include <iostream>
#include "Graph/UndirectedGraph.h"
#include "Graph/DirectedGraph.h"
#include "tester.h"


using namespace std;

void test_undirected(){
  UnDirectedGraph<int,int> grafo;
  cout<<"\nTesting Undirected Graph Implementation: \n\n";
  ASSERT(grafo.empty() == true, "The function empty is not working");
  grafo.insertVertex("A",1);
  grafo.insertVertex("B",2);
  grafo.insertVertex("C",3);
  grafo.insertVertex("D",4);
  ASSERT(grafo.empty() == false, "The function insertVertex is not working");
  grafo.createEdge("A", "B", 5);
  grafo.createEdge("A", "D", 6);
  ASSERT(grafo.isConnected() == false, "The function isConnected is not working");
  grafo.createEdge("B", "D", 7);
  grafo.createEdge("A", "C", 8);  
  ASSERT(grafo.isConnected() == true, "The function isConnected is not working");
  ASSERT(grafo("A","B") == 5, "The function &operator is not working");
  ASSERT(grafo("B","D") == 7, "The function &operator is not working");  
  grafo.insertVertex("E",4);
  grafo.createEdge("B", "E", 6);
  ASSERT(grafo.density() == 0.5, "The function density is not working");  
  ASSERT(grafo.isDense() == true, "The function isDense is not working");
  grafo.deleteEdge("B", "E");
  ASSERT(grafo.isConnected() == false, "The function deleteEdge is not working");
  grafo.deleteVertex("E");
  ASSERT(grafo.isConnected() == true, "The function deleteVertex is not working");  
  ASSERT(grafo.findById("F") == false, "The function findById is not working");
  grafo.clear();
  ASSERT(grafo.findById("A") == false, "The function clear is not working");
}

void test_directed(){
  DirectedGraph<int,int> grafo;
  cout<<"\n\nTesting Directed Graph Implementation: \n\n";
  ASSERT(grafo.empty() == true, "The function empty is not working");
  grafo.insertVertex("A",1);
  grafo.insertVertex("B",2);
  grafo.insertVertex("C",3);
  grafo.insertVertex("D",4);
  ASSERT(grafo.empty() == false, "The function insertVertex is not working");
  grafo.createEdge("A", "B", 5);
  grafo.createEdge("A", "D", 6);
  ASSERT(grafo.isConnected() == false, "The function isConnected is not working");
  grafo.createEdge("B", "D", 7);
  grafo.createEdge("A", "C", 8);  
  ASSERT(grafo.isConnected() == true, "The function isConnected is not working");
  ASSERT(grafo("A","B") == 5, "The function &operator is not working");
  ASSERT(grafo("B","D") == 7, "The function &operator is not working");  
  grafo.insertVertex("E",4);
  grafo.createEdge("B", "E", 6);
  ASSERT(grafo.density() == 0.25, "The function density is not working");  
  ASSERT(grafo.isDense() == false, "The function isDense is not working");
  grafo.deleteEdge("B", "E");
  ASSERT(grafo.isConnected() == false, "The function deleteEdge is not working");
  grafo.deleteVertex("E");
  ASSERT(grafo.isConnected() == true, "The function deleteVertex is not working");  
  ASSERT(grafo.findById("F") == false, "The function findById is not working");
  grafo.clear();
  ASSERT(grafo.findById("A") == false, "The function clear is not working");
}

int main() {
  test_undirected();
  test_directed(); 
  return 0;
}