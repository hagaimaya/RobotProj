/*
 * Astar.cpp
 *
 *  Created on: Jun 7, 2016
 *      Author: colman
 */

#include "Astar.h"
#include <math.h>
#include <iostream>

Astar::Astar() {
	// TODO Auto-generated constructor stub

}

Astar::~Astar() {
	// TODO Auto-generated destructor stub
}

unsigned int  Astar::Get_Node_With_Min_f_Score(Graph &graph,vector<Location *> openset, Location* endLocation){
	Location* min_location = openset[0];
	unsigned int min_index = 0;
	vector<vector <Node *> > nodes = graph.getNodes();
	double min_f_score = nodes[min_location->get_row()][min_location->get_col()]->get_f_score();
	for(unsigned int locationIndex = 0;locationIndex < openset.size(); ++locationIndex){
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

	for (unsigned int index = 0;index < PossibleNeighbors.size(); ++index){
		neighbors.push_back(new Location(location->get_row() + PossibleNeighbors[index]->get_row(),
				                         location->get_col() + PossibleNeighbors[index]->get_col()));
	}

	return neighbors;

}

bool is_location_in_vector(vector<Location *> locactionvector, Location* location){
	bool isLocationFound = false;

	for (unsigned int locationindex = 0; locationindex < locactionvector.size() && !isLocationFound; ++locationindex){
		if (location->get_col() == locactionvector[locationindex]->get_col() &&  location->get_row() == locactionvector[locationindex]->get_row()){
			isLocationFound = true;
		}

	}

	return isLocationFound;
}

vector<Location *> reconstruct_path(Graph& graph, Location* endlocation){
	Location* current = endlocation;
	vector<Location *> temppath;
	vector<Location *> path;
	while (graph.get_Node_Parent(current) != NULL){
			temppath.push_back(current);
			current = graph.get_Node_Parent(current);
	}

	for (int index = temppath.size() - 1; index >= 0; --index){
		path.push_back(temppath[index]);
	}

	return path;
}
// y - row
// x - col
vector<Location *> Astar::RunAStart(Graph& graph,Location* startLocation,Location* endLocation){
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
			return reconstruct_path(graph, endLocation);
		}
		openset.erase(openset.begin() + min_location_index);
		closedset.push_back(current);

		vector<Location *> neighbors = Get_neigbors(current);

		for (unsigned int neighborindex = 0; neighborindex < neighbors.size(); ++neighborindex){
			if (is_location_in_vector(closedset ,neighbors[neighborindex])){
				continue;
			}

		    double tentative_g_score = graph.get_Node_g_score(current) + current->calc_distance(neighbors[neighborindex]);

		    bool is_neighbor_in_openset = is_location_in_vector(openset, neighbors[neighborindex]);
		    if (!is_neighbor_in_openset ||
		    	tentative_g_score < graph.get_Node_g_score(neighbors[neighborindex])){
		    	graph.set_Node_parent(neighbors[neighborindex], current);
		    	graph.set_Node__g_score(neighbors[neighborindex], tentative_g_score);
		    	graph.set_Node__f_score(neighbors[neighborindex]);

		    	if(!is_neighbor_in_openset){
		    		openset.push_back(neighbors[neighborindex]);
		    	}
		    }


		}

	}

	return pathToEndPoint;
}
vector<Location *> Astar::RunAStart(Graph& graph,Node& startNode,Node& endNode){
	return (this->RunAStart(graph, new Location(startNode.getRow(),startNode.getCol()),new Location(endNode.getRow(),endNode.getCol())));
}
