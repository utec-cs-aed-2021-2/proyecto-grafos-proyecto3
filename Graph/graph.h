#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <unordered_map>

using namespace std;

template<typename TV, typename TE>
struct Edge;

template<typename TV, typename TE>
struct Vertex;

template<typename TV, typename TE>
class Graph;

//////////////////////////////////////////////////////

template<typename TV, typename TE>
struct Edge {
  public:
    Vertex<TV, TE>* vertexes[2];
    TE weight;

    Edge(){
      this->vertexes[0]=nullptr;
      this->vertexes[1]=nullptr;
      this->weight=0;
    }
    Edge(Vertex<TV,TE>* Start, Vertex<TV,TE>* End,TE peso){
      this->vertexes[0]=Start;
      this->vertexes[1]=End;
      this->weight=peso;
    }
};

template<typename TV, typename TE>
struct Vertex {
  public:
    TV data;
    std::list<Edge<TV, TE>*> edges;
    Vertex(){
      this->data=0;
    };
    Vertex(TV dato){
      this->data=dato;
    }
};

template<typename TV, typename TE>
class Graph{
public: //protected:    
    std::unordered_map<string, Vertex<TV, TE>*>  vertexes;
    //added
    //vector<Edge<TV,TE>*> edges;
    
public:
    virtual bool insertVertex(string id, TV vertex)=0;   //done
    virtual bool createEdge(string id1, string id2, TE w)=0;   //done  
    virtual bool deleteVertex(string id)=0;     //done
    virtual bool deleteEdge(string start,string end)=0; //done  
    virtual TE &operator()(string start, string end)=0; //done
    virtual float density()=0;  //done
    virtual bool isDense(float threshold = 0.5)=0;//done
    virtual bool isConnected()=0; //in progess
    virtual bool isStronglyConnected()=0;//not needed
    virtual bool empty()=0;//done
    
    virtual void clear()=0;  //done
      
    virtual void displayVertex(string id)= 0; //not needed
    virtual bool findById(string id)=0;//done
    virtual void display() = 0;//not needed
};

#endif