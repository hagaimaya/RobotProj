/*
 * Map.h
 *
 *  Created on: Mar 22, 2016
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_
#include "Location.h"
#include <vector>
using namespace std;

class Map {
private:
	unsigned int width;
	unsigned int height;
	vector<vector<bool> > map;
	vector<unsigned char> pixels;
	double mapResolution;
	double robotSize;

	bool checkIfCellIsOccupied(int i, int j);


public:
	Map();
	Map(double mapResolution, double robotSize);
	void loadMap(const char* mapFile);
	void inflateObstacles();
	virtual ~Map();
	unsigned int getHeight();
	unsigned int getWidth();
	void set_map_data(unsigned int row, unsigned int col,bool data);
	vector<vector<bool> > Getmap();
	void printMap() const;
};

#endif /* MAP_H_ */
