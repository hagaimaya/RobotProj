/*
 * Map.h
 *
 *  Created on: Mar 22, 2016
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_

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
	void printMap() const;

public:
	Map();
	Map(double mapResolution, double robotSize);
	void loadMap(const char* mapFile);
	void inflateObstacles();
	virtual ~Map();
	unsigned int getHeight();
	unsigned int getWidth();
	vector<vector<bool> > Getmap();
};

#endif /* MAP_H_ */
