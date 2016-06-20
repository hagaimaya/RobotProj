/*
 * Astar.cpp
 *
 *  Created on: Jun 7, 2016
 *      Author: colman
 */

#include "Astar.h"
#include <math.h>

Astar::Astar() {
	// TODO Auto-generated constructor stub

}

Astar::~Astar() {
	// TODO Auto-generated destructor stub
}

unsigned int  Get_Node_With_Min_f_Score(Graph &graph,vector<Location *> openset, Location* endLocation){
	Location* min_location = openset[0];
	unsigned int min_index = 0;
	vector<vector <Node *> > nodes = graph.getNodes();
	double min_f_score = nodes[min_location->get_row()][min_location->get_col()]->get_f_score();
	for(int locationIndex = 0;locationIndex < openset.size(); ++locationIndex){
		if (min_f_score > nodes[openset[locationIndex]->get_row()][openset[locationIndex]->get_col()]->get_f_score()){
			min_location = openset[locationIndex];
			min_f_score = nodes[min_location->get_row()][min_location->get_col()]->get_f_score();
			min_index = locationIndex;
		}
	}

	return min_index;
}

vector<Location *> Get_neigbors(Location* location){
	vector<Location *> neighbors;
	vector<Location *> PossibleNeighbors;

	// down right
	PossibleNeighbors.push_back(new Location(1,1));

	// down left
	PossibleNeighbors.push_back(new Location(1,-1));

	// up right
	PossibleNeighbors.push_back(new Location(-1,1));

	// up left
	PossibleNeighbors.push_back(new Location(-1,-1));

	//down
	PossibleNeighbors.push_back(new Location(1,0));

	// up
	PossibleNeighbors.push_back(new Location(-1,0));

	// left
	PossibleNeighbors.push_back(new Location(0,1));

	// right
	PossibleNeighbors.push_back(new Location(0,-1));

	for (int index = 0;index < PossibleNeighbors.size(); ++index){
		neighbors.push_back(new Location(location->get_row() + PossibleNeighbors[index]->get_row(),
				                         location->get_col() + PossibleNeighbors[index]->get_col()));
	}

	return neighbors;

}
// y - row
// x - col
vector<Node *> Astar::RunAStart(Graph& graph,Location* startLocation,Location* endLocation){
	vector<Node *> pathToEndPoint;
	graph.Calculate_h_score(endLocation);

	// the nodes that need to check
	vector<Location *> openset;

	// The set of nodes already evaluated.
	vector<Location *> closedset;

	graph.set_Node__g_score(startLocation, 0);
	graph.set_Node__f_score(startLocation);

	openset.push_back(startLocation);
	while(!openset.empty()){
		unsigned int min_location_index = Get_Node_With_Min_f_Score(graph, openset,endLocation);
		Location* current = openset[min_location_index];
		if(current->get_col() == endLocation->get_col() && current->get_row() == endLocation->get_row()){
			// to do return the path
			//return reconstruct_path(came_from, goal)
		}
		openset.erase(openset.begin() + min_location_index);
		closedset.push_back(current);

		for each neighbor in neighbor_nodes(current)
			if neighbor in closedset
					continue
			tentative_g_score := g_score[current] + dist_between(current,neighbor)
	 		if neighbor not in openset or tentative_g_score < g_score[neighbor] 			came_from[neighbor] := current
				g_score[neighbor] := tentative_g_score
				f_score[neighbor] := g_score[neighbor] + heuristic_cost_estimate(neighbor, goal)
				if neighbor not in openset
					add neighbor to openset
			return failure
	}




	return pathToEndPoint;
}
vector<Node *> Astar::RunAStart(Graph& graph,Node& startNode,Node& endNode){
	return (this->RunAStart(graph, new Location(startNode.getRow(),startNode.getCol()),new Location(endNode.getRow(),endNode.getCol())));
}
