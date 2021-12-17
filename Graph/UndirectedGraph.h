#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include "graph.h"
#include <iostream>
#include <queue>
using namespace std;

template<typename TV, typename TE>
class UnDirectedGraph : public Graph<TV, TE>{
  private:
    list<Edge<TV,TE>*> aristas;
  
  public:
    bool insertVertex(string id, TV vertex){
      Vertex<TV,TE> *temp =  new Vertex<TV,TE>(vertex);
      this->vertexes.insert_or_assign(id,temp);
      return true;
    }  

    bool createEdge(string id1, string id2, TE w){
      //Arista no puede tener el mismo vértice en los 2 extremos
      if(id1==id2){
        return false;
      }      
      auto v1 = this->vertexes.find(id1);
      auto v2 = this->vertexes.find(id2);
      //inicializar arista
      Edge<TV,TE>* arista = new Edge<TV,TE>(v1->second,v2->second,w);
      //Insertar la arista en las listas de los vértices correspondientes
      v1->second->edges.push_back(arista);
      v2->second->edges.push_back(arista);
      //this->aristas.push_back(arista);
      return true;
    }

    bool deleteVertex(string id){
        auto temp = this->vertexes.find(id);
        if(temp != this->vertexes.end()){
            for(auto it1 = this->vertexes.begin(); it1 != this->vertexes.end();it1++){
                if(it1->first != id){
                    deleteEdge(it1->first,id);
                }
            }
            this->vertexes.erase(temp);
            return true;
        }
        return false;     
    }
      


    bool deleteEdge(string start,string end){
      auto itr_start = this->vertexes.find(start)->second->edges.begin();
      auto itr_end = this->vertexes.find(end)->second->edges.begin();
      while(itr_start != this->vertexes.find(start)->second->edges.end()){
        if((*itr_start)->vertexes[0] == this->vertexes.find(end)->second || (*itr_start)->vertexes[1]==this->vertexes.find(end)->second){
          this->vertexes.find(start)->second->edges.erase(itr_start);
          break;
        }
        else{          
          std::advance (itr_start,1);          
        }        
      }
      
      while(itr_end != this->vertexes.find(end)->second->edges.end()){
        if((*itr_end)->vertexes[0] == this->vertexes.find(end)->second || (*itr_end)->vertexes[1]==this->vertexes.find(end)->second){
          this->vertexes.find(end)->second->edges.erase(itr_end);
          break;
        }
        else{          
          std::advance (itr_end,1);          
        }        
      }      
      return true;
    }

    TE &operator()(string start, string end){
      Vertex<TV,TE>* v1 = new Vertex<TV,TE>();
      Vertex<TV,TE>* v2 = new Vertex<TV,TE>();
      
      v1=this->vertexes.find(start)->second;
      v2=this->vertexes.find(end)->second;
      //si alguno no existe
      if(this->vertexes.find(start)==this->vertexes.end() || this->vertexes.find(end)==this->vertexes.end()){
        throw("Uno de los vertices no existe en este grafo");
      }
      else{
        
        auto iterador = v1->edges.begin();
        
        while(iterador != v1->edges.end()){
          if((*iterador)->vertexes[0]==v2 || (*iterador)->vertexes[1]==v2){
            
            return (*iterador)->weight;
          }
          else{            
          std::advance(iterador,1);
          }
        }
        throw("Vertices no conectados");
      }  
    }

    float density(){
      if(this->vertexes.size()==0){
        return 0;
      }

      double vertexCount = this->vertexes.size();
      double edgeCount = 0;      
      auto itr_vect = this->vertexes.begin();
      typename list<Edge<TV,TE>*>::iterator itr_list;
      
      
      //Contar cuantas aristas hay en el grafo
      while(itr_vect !=this->vertexes.end()){
        itr_list = (*itr_vect).second->edges.begin();
        while(itr_list != (*itr_vect).second->edges.end()){
        edgeCount = edgeCount + 1;
        std::advance (itr_list,1);
        }
        std::advance (itr_vect,1);
      }      
      edgeCount = edgeCount/2; //evitar la redundancia

      //Calcular la densidad
      float result = 0;
      //formula para densidad en grafo NO DIRIGIDO
      result = ((2*edgeCount)/(vertexCount*(vertexCount-1)));
      return result;
    }

    bool isDense(float threshold = 0.5){
      if(this->density()<threshold){
        return false;
      }
      else{
        return true;
      }
    }

    bool isConnected(){
      Vertex<TV,TE>* aux;      
      int visitados=0;
      queue<Vertex<TV,TE>*> cola;
      typename list<Edge<TV,TE>*>::iterator itr;
      typename unordered_map<string, Vertex<TV, TE>*>::iterator itr_vert;
      
      std::unordered_map<Vertex<TV,TE>*, bool>  checking;
      cola.push(this->vertexes.begin()->second);
      
      while(!cola.empty()){
        aux = cola.front();                
        itr = aux->edges.begin();      
        
        while(itr!=aux->edges.end()){       
          
          if(checking.find(aux)== checking.end()){
            if((*itr)->vertexes[0]==aux){
              cola.push((*itr)->vertexes[1]);
              
            }
            else if((*itr)->vertexes[1]==aux){
              cola.push((*itr)->vertexes[0]);              
            }
          }             
          ++itr;
        }
        checking.insert_or_assign(aux,true); 
        cola.pop();            
      }
      
      if(checking.size()==this->vertexes.size()){
        return true;
      }
      else{
        return false;
      }    
    }

    bool isStronglyConnected(){
      Vertex<TV,TE>* aux;      
      int visitados=0;
      queue<Vertex<TV,TE>*> cola;
      typename list<Edge<TV,TE>*>::iterator itr;
      typename unordered_map<string, Vertex<TV, TE>*>::iterator itr_vert;
      
      std::unordered_map<Vertex<TV,TE>*, bool>  checking;
      cola.push(this->vertexes.begin()->second);
      
      while(!cola.empty()){
        aux = cola.front();                
        itr = aux->edges.begin();      
        
        while(itr!=aux->edges.end()){       
          
          if(checking.find(aux)== checking.end()){
            if((*itr)->vertexes[0]==aux){
              cola.push((*itr)->vertexes[1]);
              
            }
            else if((*itr)->vertexes[1]==aux){
              cola.push((*itr)->vertexes[0]);              
            }
          }             
          ++itr;
        }
        checking.insert_or_assign(aux,true); 
        cola.pop();            
      }
      
      if(checking.size()==this->vertexes.size()){
        return true;
      }
      else{
        return false;
      }          
    }
    
    bool empty(){
      if(this->vertexes.size()==0){
        return true;
      }
      else{
        return false;
      }
    }

    void clear(){
      auto iterador = this->vertexes.begin();
      for(auto it = this->vertexes.begin(); it != this->vertexes.end(); ) {        
        it = this->vertexes.erase(it);        
      }
    }

    void displayVertex(string id){
        auto temp = this->vertexes.find(id);
        if(temp != this->vertexes.end()){
            cout<<temp->second->data<<": ";
            for(auto it = temp->second->edges.begin(); it != temp->second->edges.end(); it++){
                cout<<"<-["<<(*it)->weight<<"]-> "<<(*it)->vertexes[1]->data<<" ;";
            }
            cout<<endl;
        }
    }

    bool findById(string id){
      //verificar si el nodo existe ig
      auto iterador = this->vertexes.find(id);
      if(iterador == this->vertexes.end()){
        return false;
      }
      else{
        return true;
      }
    }

    void display(){
        for(auto temp = this->vertexes.begin() ;temp != this->vertexes.end();temp++){
            displayVertex(temp->first);
        }
    }    
    
    

   
};

#endif