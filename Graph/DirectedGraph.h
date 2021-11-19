#ifndef NONDIRECTEDGRAPH_H
#define NONDIRECTEDGRAPH_H

#include "graph.h"
#include <iostream>
#include <queue>
using namespace std;

template<typename TV, typename TE>
class DirectedGraph : public Graph<TV, TE>{
public:
    DirectedGraph(){}
    ~DirectedGraph()=default;

    bool insertVertex(string id, TV vertex){
        Vertex<TV,TE>* temp = new Vertex<TV,TE>;
        temp->data = vertex;
        this->vertexes.insert_or_assign(id,temp);
        return true;
    }

    bool createEdge(string id1, string id2, TE w){
        auto temp1 = this->vertexes.find(id1);
        auto temp2 = this->vertexes.find(id2);
        if(temp1 != this->vertexes.end() && temp2 != this->vertexes.end()){
            Edge<TV,TE>* adding = new Edge<TV,TE>;
            adding->weight = w;
            adding->vertexes[0] = temp1->second;
            adding->vertexes[1] = temp2->second;
            temp1->second->edges.push_back(adding);
            return true;
        }
        return false;
    }

    bool deleteEdge(string start, string end){
        auto temp1 = this->vertexes.find(start);
        auto temp2 = this->vertexes.find(end);
        if(temp1 != this->vertexes.end() && temp2 != this->vertexes.end()){
            for(auto it = temp1->second->edges.begin(); it != temp1->second->edges.end();it++){
                if((*it)->vertexes[1] == temp2->second){
                    temp1->second->edges.erase(it);
                    return true;
                }
            }
        }
        return false;
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

    TE operator()(string start, string end){
        auto temp1 = this->vertexes.find(start);
        auto temp2 = this->vertexes.find(end);
        if(temp1 != this->vertexes.end() && temp2 != this->vertexes.end()){
            for(auto it = temp1->second->edges.begin(); it != temp1->second->edges.end();it++){
                if((*it)->vertexes[1] == temp2->second){
                    return (*it)->weight;
                }
            }
        }
        return 0;
    }

    float density(){
        float v,e;
        v = this->vertexes.size();
        e = 0;
        for(auto it = this->vertexes.begin(); it != this->vertexes.end();it++){
            e += it->second->edges.size();
        }
        return e/(v*(v-1));
    }

    bool isDense(float threshold = 0.5){
        return (density() >= threshold);
    }

    bool isConnected(){
        unordered_map<TV,TV> temp;
        int s = this->vertexes.size();
        auto it1 = this->vertexes.begin();

        temp.insert_or_assign(it1->second->data,it1->second->data);
        auto it2 = it1->second->edges.begin();
        while(it2 != it1->second->edges.end()){
            if(temp.find((*it2)->vertexes[1]->data) == temp.end()){              
                temp.insert_or_assign((*it2)->vertexes[1]->data,(*it2)->vertexes[1]->data);
            }
            it2++;                    
        }
        it1++;

        while(it1 != this->vertexes.end() && temp.size() < s){
            if(temp.find(it1->second->data) == temp.end()){
                it2 = it1->second->edges.begin();
                while(it2 != it1->second->edges.end()){
                    if(temp.find((*it2)->vertexes[1]->data) != temp.end()){              
                        temp.insert_or_assign((*it2)->vertexes[0]->data,(*it2)->vertexes[0]->data);
                        break;                       
                    }
                    it2++;                    
                }                
            }
            if(temp.find(it1->second->data) != temp.end()){
                it2 = it1->second->edges.begin();
                while(it2 != it1->second->edges.end()){
                    if(temp.find((*it2)->vertexes[1]->data) == temp.end()){              
                        temp.insert_or_assign((*it2)->vertexes[1]->data,(*it2)->vertexes[1]->data);
                    }
                    it2++;                    
                }
            }                       
            it1++;
        }
        return (temp.size() == s);
    }

    bool isStronglyConnected(){
        unordered_map<TV,TV> temp;
        queue<Vertex<TV,TE>*> q;
        Vertex<TV,TE>* aux;
        int s = this->vertexes.size();
        for(auto it1 = this->vertexes.begin(); it1 != this->vertexes.end(); it1++){
            q.push(it1->second);
            temp.insert_or_assign(it1->second->data,it1->second->data);
            while(!q.empty()){
                aux = q.front();
                q.pop();
                auto it2 = aux->edges.begin();
                while(it2 != aux->edges.end()){
                    if(temp.find((*it2)->vertexes[1]->data) == temp.end()){
                        q.push((*it2)->vertexes[1]);                        
                        temp.insert_or_assign((*it2)->vertexes[1]->data,(*it2)->vertexes[1]->data);
                    }
                    it2++;                    
                }
            }
            if(temp.size()<s){
                return false;
            }
            temp.clear();          
        }
        return true;
    }

    bool empty(){
        return (this->vertexes.size() == 0);
    }

    void clear(){
        this->vertexes.clear();
    }  
    

    void displayVertex(string id){
        auto temp = this->vertexes.find(id);
        if(temp != this->vertexes.end()){
            cout<<temp->second->data;
            for(auto it = temp->second->edges.begin(); it != temp->second->edges.end(); it++){
                cout<<" -["<<(*it)->weight<<"]-> "<<(*it)->vertexes[1]->data<<" ;";
            }
            cout<<endl;
        }
    }

    bool findById(string id){
        return (this->vertexes.find(id) != this->vertexes.end());
    }

    void display(){
        for(auto temp = this->vertexes.begin() ;temp != this->vertexes.end();temp++){
            displayVertex(temp->first);
        }
    }
};

#endif
