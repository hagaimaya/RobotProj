
#include <iostream>
#include "BuildGraphFromMap/Astar.h"
#include "BuildGraphFromMap/Graph.h"
#include "BuildGraphFromMap/Map.h"
#include "BuildGraphFromMap/Location.h"
#include "BuildGraphFromMap/lodepng.h"
#include "Driver/Driver.h"
#include "Driver/Robot.h"
#include <vector>

using namespace std;

int main() {
	Map* map = new Map(2.5,30.0);
	///home/colman/Desktop/my proj/RoboticProj/BuildGraphFromMap
	map->loadMap("/home/colman/Desktop/my proj/RoboticProj/BuildGraphFromMap/roboticLabMap.png");
	map->inflateObstacles();
	Graph* graph = new Graph();

	graph->buildGraphFromMap(*map);
	Location* endLocation = new Location(138,169);
	Location* startLocation = new Location(305, 362);
	graph->Calculate_h_score(endLocation);

	Astar* astar = new Astar();
	vector<Location*> pathToLocation = astar->RunAStart(*graph, startLocation, endLocation);

	for (unsigned int i = 0; i<pathToLocation.size();i++){
		cout << "Location: (" << pathToLocation[i]->get_row() << " , "<< pathToLocation[i]->get_col() << ")" << endl;
		map->set_map_data(pathToLocation[i]->get_row()-1,pathToLocation[i]->get_col()-1,true);
	}
	map->printMap();
	Robot robot("localhost", 6665);
	robot.setOdometry(305, 362, 20 * 3.14 / 180 );
	robot.read();
	Driver driver(&robot);

	for (unsigned int i = 0; i<pathToLocation.size();i++){
		cout << "Location: (" << pathToLocation[i]->get_row() << " , "<< pathToLocation[i]->get_col() << ")" << endl;

		driver.moveToNextWaypoint(pathToLocation[i]->get_row(), pathToLocation[i]->get_col());
	}




	return 0;
}
