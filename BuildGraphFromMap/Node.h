/*
 * Node.h
 *
 *  Created on: Mar 29, 2016
 *      Author: colman
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include "Location.h"
using namespace std;

enum Direction { LEFT, RIGHT, UP, DOWN };
#define DIRECTIONS_NUM 4

class Node {
private:
	unsigned int row;
	unsigned int col;
	// score from start
	double g_score;

	// estimated cost to destination
	double h_score;

	// estimated cost + cost from start
	double f_score;

	bool data;

	bool wasVisited;


public:

	Location* parentLocation;
	Node();
	Node(int row,int col,bool data);
	bool CompareNodes(Node* node);
	unsigned int getRow();
	unsigned int getCol();
	void set_g_score(double g_score);
	void set_f_score();
	void set_h_score(double h_score);
	void set_parentLocation(Location* location);
	double get_g_score();
	double get_f_score();
	double get_h_score();
	bool get_data();
	bool isVisted();
	void visit();
	virtual ~Node();
};

#endif /* NODE_H_ */
