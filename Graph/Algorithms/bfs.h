#ifndef BFS_H
#define BFS_H

#include "Graph/DirectedGraph.h"
#include <queue>
#include <unordered_map>
using namespace std;

template<TV,TE>
class BFS{
private:
	DirectedGraph<TV,TE> BFSapplied;
public:
	BFS(DirectedGraph<TV,TE> graph,string start){
		unordered_map<TV,string> help;
		for(auto it = graph.vertexes.begin();it != graph.vertexes.end();it++){
			help.insert(it->second->data,it->first);
		}
		
		unordered_map<TV,TV> visited;
		queue<TV> resQ;
		TV aux = graph.vertexes.find(start)->second->data;
		resQ.push(aux);
		visited.insert(aux,aux);
		string auxS = help.find(aux)->second;
		this->BFSapplied.insertVertex(auxS,aux);
		TV aux2;
		while(!resQ.empty()){
			aux = resQ.front();
			resQ.pop();
			auxS = help.find(aux)->second;
			for (auto it2 = graph.vertexes.find(auxS)->second->edges.begin();it2 != graph.vertexes.find(auxS)->second->edges.end();it2++){
				aux2 = (*it2)->vertexes[1]->data;
				if (visited.find(aux2) == visited.end()){
					visited.insert(aux2,aux2);
					queue.push_back(aux2);
					this->BFSapplied.insertVertex(help.find(aux2)->second,aux2);
					this->BFSapplied.createEdge(auxS,help.find(aux2)->second,(*it2)->weight);
				}
			}
		}
	}
	
	~BFS()=default;
	DirectedGraph<TV,TE>.apply(){
		return BFSapplied;
	}
};

#endif
