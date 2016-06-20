/*
 * Node.cpp
 *
 *  Created on: Mar 29, 2016
 *      Author: colman
 */

#include "Node.h"

Node::Node() {

}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

Node::Node(int row,int col,bool data){
	this->row = row;
	this->col = col;
	this->data = data;
	this->g_score = 0;
	this->f_score=0;
	this->h_score=0;
	this->wasVisited = false;
}

bool Node::CompareNodes(Node* node)
{
	return ((this->col == node->col) && (this->row == node->row));
}
unsigned int Node::getRow(){
	return this->row;
}
unsigned int Node::getCol(){
	return this->col;
}

void Node::set_g_score(double g_score){
	this->g_score = g_score;
}

double Node::get_g_score(){
	return this->g_score;
}

/**
 * calculate the f score
 */
void Node::set_f_score(){
	this->f_score = this->g_score + this->h_score;
}
void Node::set_h_score(double h_score){
	this->h_score = h_score;
}
double Node::get_f_score(){
	return this->f_score;
}
double Node::get_h_score(){
	return this->h_score;
}
bool Node::get_data(){
	return this->data;
}

bool Node::isVisted(){
	return this->wasVisited;
}
void Node::visit(){
	this->wasVisited = true;
}
