
#include <iostream>
#include "BuildGraphFromMap/Astar.h"
#include "BuildGraphFromMap/Graph.h"
#include "BuildGraphFromMap/Map.h"
#include "BuildGraphFromMap/Location.h"
#include "BuildGraphFromMap/lodepng.h"
#include <vector>

using namespace std;

int main() {
	Map* map = new Map(2.5,30.0);
	///home/colman/Desktop/my proj/RoboticProj/BuildGraphFromMap
	map->loadMap("/home/colman/Desktop/my proj/RoboticProj/BuildGraphFromMap/roboticLabMap.png");
	map->inflateObstacles();
	Graph* graph = new Graph();

	graph->buildGraphFromMap(*map);
	Location* endLocation = new Location(169,138);
	Location* startLocation = new Location(362, 305);
	graph->Calculate_h_score(endLocation);

	Astar* astar = new Astar();
	vector<Location*> pathToLocation = astar->RunAStart(*graph, startLocation, endLocation);

	for (int i = 0; i<pathToLocation.size();i++){
		cout << "Location: (" << pathToLocation[i]->get_row() << " , "<< pathToLocation[i]->get_col() << ")" << endl;
	}

	map->


	return 0;
}
