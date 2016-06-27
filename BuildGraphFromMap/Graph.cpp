/*
 * Graph.cpp
 *
 *  Created on: Mar 29, 2016
 *      Author: colman
 */

#include "Graph.h"
#include <math.h>

Graph::Graph() {
	// TODO Auto-generated constructor stub
	this->nodes = vector<vector<Node *> >();
}

Graph::~Graph() {
	// TODO Auto-generated destructor stub
}
void Graph::buildGraphFromMap(Map& map)
{

	this->rows = map.getHeight()+2;
	this->cols = map.getWidth()+2;

	 int rows = this->rows;
	 int columns = this->cols;
	 vector<vector<bool> > mapArray = map.Getmap();

   nodes.resize(rows);

   for(int i=0;i<rows;++i){
	   nodes[i].resize(columns);
	   nodes[i][0] = new Node(i,0,true);
	   nodes[i][columns - 1] = new Node(i,columns - 1,true);
   }

   for(int j=0;j<columns;++j){
	   nodes[0][j] = new Node(0,j,true);
   	   nodes[rows-1][j] = new Node(rows ,j,true);
      }

	for (int i=1;i<rows-1;++i){

		for (int j=1;j < columns-1;++j){
			this->nodes[i][j]= new Node(i,j,mapArray[i-1][j-1]);
		}
	}

}
vector<vector<Node *> > Graph::getNodes(){
	return this->nodes;
}

Node* Graph::Get_Node_By_Location(unsigned int row,unsigned int column){
	// I added one because  of the barrier
	return this->nodes[row+1][column+1];
}

unsigned int Graph::get_rows(){
	return this->rows;
}
unsigned int Graph::get_cols(){
	return this->cols;
}
double heuristic_cost_estimate(Location* startLocation,Location* endLocation){
	return sqrt(pow(startLocation->get_row() - endLocation->get_row(), 2) + pow(startLocation->get_col() - endLocation->get_col(), 2));

}
void Graph::set_Node__g_score(Location* location, double g_score){
	this->nodes[location->get_row()][location->get_col()]->set_g_score(g_score);
}
void Graph::set_Node__h_score(Location* location, double h_score){
	this->nodes[location->get_row()][location->get_col()]->set_h_score(h_score);
}
void Graph::set_Node__f_score(Location* location){
	this->nodes[location->get_row()][location->get_col()]->set_f_score();
}
void Graph::Calculate_h_score(Location* endLocation){
	for (int rowindex = 0;rowindex < rows; ++rowindex){
		for (int colindex = 0;colindex < cols; ++colindex ){
			if (!nodes[rowindex][colindex]->get_data()){
				nodes[rowindex][colindex]->set_h_score(heuristic_cost_estimate(new Location(rowindex, colindex),endLocation));
			}
		}
	}
}

void Graph::set_Node_parent(Location* location, Location* parentlocation){
	this->nodes[location->get_row()][location->get_col()]->set_parentLocation(parentlocation);
}

double Graph::get_Node_g_score(Location* location){
	return this->nodes[location->get_row()][location->get_col()]->get_g_score();
}
double Graph::get_Node_h_score(Location* location){
		return this->nodes[location->get_row()][location->get_col()]->get_h_score();
}
double Graph::get_Node_f_score(Location* location){
	return this->nodes[location->get_row()][location->get_col()]->get_f_score();
}

Location* Graph::get_Node_Parent(Location* location){
	return this->nodes[location->get_row()][location->get_col()]->parentLocation;
}
