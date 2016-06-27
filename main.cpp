
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
		pathToLocation[i] = new Location(height - (pathToLocation[i]->get_row() - 1),pathToLocation[i]->get_col() - 1);
	}

	for (unsigned int i = 1; i<pathToLocation.size() - 1;i++){
		double temp1 = atan2(pathToLocation[i]->get_row() - pathToLocation[i - 1]->get_row(),pathToLocation[i]->get_col() - pathToLocation[i - 1]->get_col());
		double temp2 = atan2(pathToLocation[i + 1]->get_row() - pathToLocation[i]->get_row(),pathToLocation[i + 1]->get_col() - pathToLocation[i]->get_col());
		if (temp1 == temp2){
			pathToLocation.erase(pathToLocation.begin() + i);
			i--;
		}

	}
	map->printMap();
	Robot robot("localhost", 6665);
	robot.setOdometry(362  , height - 305 , 20 * 3.14 / 180 );
	//robot.setOdometry(2.175,-2.875, 20);


	robot.read();
	Driver driver(&robot);

	/**vector<Location *> temp2;
		double dX = 362-2.175;
	     double dY = height - 305 + 2.875;
		for (unsigned int i = 0; i < pathToLocation.size();i++){
			temp2.push_back(new Location(pathToLocation[i]->get_row() - dY ,pathToLocation[i]->get_col() -dX));
		}
		pathToLocation = temp2;**/
	/**vector<Location *> temp;
	temp.push_back(pathToLocation[0]);
	for (unsigned int i = 1; i < pathToLocation.size();i++){
		temp.push_back(new Location((pathToLocation[i]->get_row() - pathToLocation[i-1]->get_row()) * 0.025 + pathToLocation[i - 1]->get_row(),(pathToLocation[i]->get_col() - pathToLocation[i-1]->get_col()) * 0.025 + pathToLocation[i - 1]->get_col()));
	}
	pathToLocation = temp;
**/

	for (unsigned int i = 1; i<pathToLocation.size();i++){
		cout << "index: " << i << " size: " << pathToLocation.size() <<" Location: (" << pathToLocation[i]->get_row() << " , "<< pathToLocation[i]->get_col() << ")" << endl;

		driver.moveToNextWaypoint(pathToLocation[i]->get_col(), pathToLocation[i]->get_row());
		if (pathToLocation[i - 1]->get_col() != robot.getX() || pathToLocation[i - 1]->get_row() != robot.getY()){
			robot.setOdometry(pathToLocation[i]->get_col()  , pathToLocation[i]->get_row() , robot.getYaw());
		}

	}




	return 0;
}
