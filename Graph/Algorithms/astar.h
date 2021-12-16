#ifndef ASTAR_H
#define ASTAR_H

#include "Graph/DirectedGraph.h"
#include <iostream>
#include <priority_queue>
#include <tuple>
using namespace std;

template<typename TV,typename TE>
class AStar{
private:
	DirectedGraph<TV,TE> astarApplied;
public:
	AStar(DirectedGraph<TV,TE> graph,string start,string end,vector<TE> heuristics>){
		priority_queue<string,std::vector<string>,std::greater<string>> orderedVertexes;
		for(auto it = graph.vertexes.begin();it != graph.vertexes.end();it++){
			orderedVertexes.push(it->first);
		}
		
		unordered_map<TV,pair<string,TE>> heur
		for(auto it2 = heuristics.begin();it2 != heuristics.end();it2++){
			heur.insert(graph.vertexes.find(orderedVertexes.front())->second->data,{orderedVertexes.front(),*it2});
			orderedVertexes.pop();
		}
		
		priority_queue<tuple<TE,TV,TV>,std::vector<tuple<TE,TV,TV>>,std::greater<tuple<TE,TV,TV>>> resQ;
		TV aux = graph.vertexes.find(start)->second->data;
		tuple<TE,TV,TV> auxTup = {heur.find(aux)->second->second,aux,aux};
		resQ.push(auxTup);
		unordered_map<TV,TV> resMap;
		string auxS;
		TV dataEnd = graph.vertexes.find(end)->second->data;
		
		while(!resQ.empty()){
			auxTup = resQ.front();
			resQ.pop();
			resMap.insert_or_assign(auxTup.get<1>,auxTup.get<2>);
			auxS = heur.find(auxTup.get<1>)->second->first;
			if(auxS == end)break;
			for(auto it = graph.vertexes.find(auxS)->second->edges.begin();it != graph.vertexes.find(auxS)->second->edges.end();it++){
				aux = (*it)->vertexes[1]->data;
				resQ.push({auxTup.get<0> - heur.find(auxTup.get<1>)->second->second + (*it)->weight + heur.find(aux),aux,auxTup.get<1>})
			}
		}
		
		TV left = auxTup.get<1>;
		TV right = auxTup.get<2>;
		TE lrweight;
		this->astarApplied.insertVertex(heur.find(left)->second->first,left);
		while(right != left){
			this->astarApplied.insertVertex(heur.find(right)->second->first,right);
			auxS = heur.find(right)->second->first;
			for(auto it = graph.vertexes.find(auxS)->second->edges.begin();it != graph.vertexes.find(auxS)->second->edges.end();it++){
				if(right == (*it)->vertexes[1]->data){
					lrweight = (*it)->weight;
					break;
				}
			}
			this->astarApplied.createEdge(heur.find(right)->second->first,heur.find(left)->second->first,lrweight);
			left = right;
			right = *(resMap.find(left));
		}
	}
	~AStar()=default;
	DirectedGraph<TV,TE> apply(){
		return astarApplied;
	}
};

#endif
