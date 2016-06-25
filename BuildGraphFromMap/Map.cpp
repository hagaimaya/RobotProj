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
Map::Map(double mapResolution, double robotSize){
	this->mapResolution = mapResolution;
	this->robotSize = robotSize;
	this->width = 0;
	this->height = 0;
}
void Map::loadMap(const char* mapFile) {

	lodepng::decode(pixels, width, height, mapFile);
	map.resize(height);
	for (unsigned int i = 0; i < height; i++) {
		map[i].resize(width);
	}


	for (unsigned int i = 0; i < height; i++) {
		for (unsigned int j = 0; j < width; j++) {
			map[i][j] = checkIfCellIsOccupied(i, j);
		}
	}

	//printMap();
}

void Map::inflateObstacles() {
	int robotSizeInPixels = robotSize / mapResolution;
	int inflationRadius = 0.3 * robotSizeInPixels;
		vector<vector<bool> > InflatedMap (map);
		int maxUp;
		int maxdown;
		int maxleft;
		int maxright;
		for ( int i = 0; i < height; i++) {
			for ( int j = 0; j < width; j++) {
				if(map[i][j] == true){
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
							InflatedMap[maxUp][k] = true;
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
	for (unsigned int i = 0; i < height; i++) {
			for (unsigned int j = 0; j < width; j++) {
				cout << (map[i][j] ? "*" : " ");
			}
			cout << endl;
		}

		vector<unsigned char> newPixels;
		newPixels.resize(pixels.size());
		for (unsigned int i = 0; i < height; i++) {
			for (unsigned int j = 0; j < width; j++) {
				int c = (i * width + j) * 4;
				if (map[i][j] == 1){

					newPixels[c] = 0;
					newPixels[c + 1] = 0;
					newPixels[c + 2] = 0;
					newPixels[c + 3] = 255;
				}
				else {
				  newPixels[c] = 255;
				  newPixels[c+1] = 255;
				  newPixels[c+2] = 255;
				  newPixels[c+3] = 255;
				}
			}
		}
		vector<unsigned char> ImageBuffer;
		lodepng::encode(ImageBuffer,newPixels,width,height);
		lodepng::save_file(ImageBuffer, "mynewimage.png");
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
void Map::set_map_data(unsigned int row, unsigned int col,bool data){
	this->map[row][col]=data;
}
