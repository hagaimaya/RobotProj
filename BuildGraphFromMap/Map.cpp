/*
 * Map.cpp
 *
 *  Created on: Mar 22, 2016
 *      Author: colman
 */

#include "Map.h"
#include "lodepng.h"
#include <iostream>

Map::Map() {
	// TODO Auto-generated constructor stub

}

void Map::loadMap(const char* mapFile) {

	lodepng::decode(pixels, width, height, mapFile);
	map.resize(height);
	for (int i = 0; i < height; i++) {
		map[i].resize(width);
	}


	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			map[i][j] = checkIfCellIsOccupied(i, j);
		}
	}

	printMap();
}

void Map::inflateObstacles() {
	int robotSizeInPixels = robotSize / mapResolution;
	int inflationRadius = 0.3 * robotSizeInPixels;
		vector<vector<bool> > InflatedMap (map);
		int startobstacle=0;
		int endobstacle=0;
		int maxUp;
		int maxdown;
		int maxleft;
		int maxright;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if(map[i][j] == 1){
					for (int k=1;k < inflationRadius;k++){
							if(i - k >= 0){
								maxUp = i - k;
							}
							if(i + k < height){
								maxdown = i + k;
							}

							if ( j -k >= 0){
							  maxleft = j -k;
							}
							if (j +k < width){
								maxright = j +k;
							}
					}

					for (;maxUp < maxdown; maxUp++){
						for(int k=maxleft;k < maxright; k++){
							InflatedMap[maxUp][k] = 1;
						}
					}
				}
			}
		}

		map = InflatedMap;
}

bool Map::checkIfCellIsOccupied(int i, int j) {
	int c = (i * width + j) * 4;
	int r = pixels[c];
	int g = pixels[c + 1];
	int b = pixels[c + 2];

	if (r == 0 && g == 0 && b == 0)
		return true;
	return false;
}

void Map::printMap() const {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << (map[i][j] ? "*" : " ");
		}
		cout << endl;
	}
}

unsigned int Map::getHeight(){
	return height;
}
unsigned int Map::getWidth(){
return width;
}

vector<vector<bool> > Map::Getmap(){
	return map;
}
Map::~Map() {
	// TODO Auto-generated destructor stub
}

