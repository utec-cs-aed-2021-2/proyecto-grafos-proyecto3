#ifndef ASTAR_H
#define ASTAR_H

#include "Graph\DirectedGraph.h"
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
#include <unordered_map>

using namespace std;

template<typename TV, typename TE>
class AStar {
private:
	DirectedGraph<TV, TE> astarApplied;
public:
	AStar(DirectedGraph<TV, TE> graph, string start, string end, vector<TE> heuristics) {
		priority_queue<string, std::vector<string>, std::greater<string>> orderedVertexes;
		for (auto it = graph.vertexes.begin(); it != graph.vertexes.end(); it++) {
			orderedVertexes.push(it->first);
		}

		unordered_map<TV, pair<string, TE>> heur;
		pair<string, TE> temp_pair;
		string temp;
		for (int i = 0; i < heuristics.size(); i++) {
			temp = orderedVertexes.top();
			temp_pair = { temp,heuristics[i] };
			heur.insert_or_assign(graph.vertexes.find(temp)->second->data, temp_pair);
			orderedVertexes.pop();
		}

		priority_queue<tuple<TE, TV, TV>, std::vector<tuple<TE, TV, TV>>, std::greater<tuple<TE, TV, TV>>> resQ;
		TV aux = graph.vertexes.find(start)->second->data;
		tuple<TE, TV, TV> auxTup = { heur.find(aux)->second.second,aux,aux };
		resQ.push(auxTup);
		unordered_map<TV, TV> resMap;
		string auxS;
		TV dataEnd = graph.vertexes.find(end)->second->data;


		while (!resQ.empty()) {
			auxTup = resQ.top();
			resQ.pop();
			resMap.insert_or_assign(get<1>(auxTup), get<2>(auxTup));
			auxS = heur.find(get<1>(auxTup))->second.first;
			if (auxS == end)break;
			for (auto it = graph.vertexes.find(auxS)->second->edges.begin(); it != graph.vertexes.find(auxS)->second->edges.end(); it++) {
				aux = (*it)->vertexes[1]->data;
				resQ.push({ get<0>(auxTup) - heur.find(get<1>(auxTup))->second.second + (*it)->weight + heur.find(aux)->second.second,aux,get<1>(auxTup) });
			}
		}
		TV left = get<1>(auxTup);
		TV right = get<2>(auxTup);
		TE lrweight = 0;
		this->astarApplied.insertVertex(heur.find(left)->second.first, left);
		while (left != graph.vertexes.find(start)->second->data) {
			this->astarApplied.insertVertex(heur.find(right)->second.first, right);
			auxS = heur.find(right)->second.first;
			for (auto it = graph.vertexes.find(auxS)->second->edges.begin(); it != graph.vertexes.find(auxS)->second->edges.end(); it++) {
				if (left == (*it)->vertexes[1]->data) {
					lrweight = (*it)->weight;
					break;
				}
			}
			this->astarApplied.createEdge(heur.find(right)->second.first, heur.find(left)->second.first, lrweight);
			left = right;
			right = (resMap.find(left)->second);
		}
	}
	~AStar() = default;
	DirectedGraph<TV, TE> apply() {
		return astarApplied;
	}
};

#endif