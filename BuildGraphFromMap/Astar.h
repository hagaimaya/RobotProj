/*
 * Astar.h
 *
 *  Created on: Jun 7, 2016
 *      Author: colman
 */

#ifndef ASTAR_H_
#define ASTAR_H_

#include "Graph.h"
#include "Node.h"
#include <vector>
#include "Location.h"

class Astar {
private:
	float Heuristic_cost_estimate(Location startLocation,Location endLocation);
	unsigned int  Get_Node_With_Min_f_Score(Graph &graph,vector<Location *> openset, Location* endLocation);
public:
	Astar();
	virtual ~Astar();

	vector<Location *> RunAStart(Graph& graph,Location* startLocation,Location* endLocation);
	vector<Location *> RunAStart(Graph& graph,Node& startNode,Node& endNode);
};

#endif /* ASTAR_H_ */
