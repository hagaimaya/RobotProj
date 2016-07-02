
#include <iostream>
#include "BuildGraphFromMap/Astar.h"
#include "BuildGraphFromMap/Graph.h"
#include "BuildGraphFromMap/Map.h"
#include "BuildGraphFromMap/Location.h"
#include "BuildGraphFromMap/lodepng.h"
#include "Driver/Driver.h"
#include "Driver/Robot.h"
#include <vector>
#include <math.h>

using namespace std;

int main() {
	Map* map = new Map(2.5,30);
	///home/colman/Desktop/my proj/RoboticProj/BuildGraphFromMap
	map->loadMap("/home/colman/Desktop/PcBotWorld/PcBotWorld/roboticLabMap.png");
	//map->loadMap("/home/colman/Desktop/my proj/RoboticProj/BuildGraphFromMap/roboticLabMap.png");
	map->inflateObstacles();
	Graph* graph = new Graph();

	graph->buildGraphFromMap(*map);
	unsigned int height = map->getHeight();
	unsigned int width = map->getWidth();
	Location* endLocation = new Location(138,169);
	Location* startLocation = new Location(305, 362);
	graph->Calculate_h_score(endLocation);

	Astar* astar = new Astar();
	vector<Location*> pathToLocation = astar->RunAStart(*graph, startLocation, endLocation);


	for (unsigned int i = 0; i<pathToLocation.size();i++){
		cout << "Location: (" << pathToLocation[i]->get_col() << " , "<< height - pathToLocation[i]->get_row() << ")" << endl;
		map->set_map_data(pathToLocation[i]->get_row()-1,pathToLocation[i]->get_col()-1,true);
		pathToLocation[i] = new Location(4.73  - (pathToLocation[i]->get_row() + 1) * 0.025,
									-6.85 + (pathToLocation[i]->get_col() + 1) * 0.025);
	}


	map->printMap();
	Robot robot("localhost", 6665);
	robot.setOdometry(pathToLocation[0]->get_col()  , pathToLocation[0]->get_row() , 20 * 3.14 / 180 );



	robot.read();
	Driver driver(&robot);



	for (unsigned int i = 1; i<pathToLocation.size();i++){
		cout << "index: " << i << " size: " << pathToLocation.size() <<" Location: (" << pathToLocation[i]->get_row() << " , "<< pathToLocation[i]->get_col() << ")" << endl;

		driver.moveToNextWaypoint(pathToLocation[i]->get_col(), pathToLocation[i]->get_row());
		//if (pathToLocation[i - 1]->get_col() != robot.getX() || pathToLocation[i - 1]->get_row() != robot.getY()){
			//robot.setOdometry(pathToLocation[i]->get_col()  , pathToLocation[i]->get_row() , robot.getYaw());
		//}

	}




	return 0;
}
