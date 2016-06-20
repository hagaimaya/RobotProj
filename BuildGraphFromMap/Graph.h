/*
 * Graph.h
 *
 *  Created on: Mar 29, 2016
 *      Author: colman
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "Node.h"
#include "Map.h"
#include "Location.h"

class Graph {
private:
	vector<vector<Node *> > nodes;
	unsigned int rows;
	unsigned int cols;

public:
	Graph();
	void buildGraphFromMap(Map& map);
	Node* Get_Node_By_Location(unsigned int row,unsigned int column);
	// get the node from the graph
	vector<vector<Node *> > getNodes();

	unsigned int get_rows();
	unsigned int get_cols();
	void set_Node__g_score(Location* location, double g_score);
	void set_Node__h_score(Location* location, double h_score);
	void set_Node__f_score(Location* location);
	Location* get_Node_Parent(Location* location);
	double get_Node_g_score(Location* location);
	double get_Node_h_score(Location* location);
	double get_Node_f_score(Location* location);
	void Calculate_h_score(Location* endLocation);
	void set_Node_parent(Location* location, Location* parentlocation);
	virtual ~Graph();
};

#endif /* GRAPH_H_ */
