
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
#include "Localization/LocalizationManager.h"
using namespace std;
#include <unistd.h>

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

		//map->set_map_data(pathToLocation[i]->get_row()-1,pathToLocation[i]->get_col()-1,true);
		pathToLocation[i] = new Location(4.73  - (pathToLocation[i]->get_row() + 1) * 0.025,
									-6.85 + (pathToLocation[i]->get_col() + 1) * 0.025);
	}

	//10.10.245.63
	map->printMap();
	//Robot robot("10.10.245.63", 6665);
	Robot robot("localhost", 6665);

	for (int i=0; i< 20; i++){
		robot.setOdometry(pathToLocation[0]->get_col()  , pathToLocation[0]->get_row() , 20 * 3.14 / 180 );
		robot.read();
	}
	for (int i=0; i< 20; i++){
		robot.read();
	}
	/**while (robot.getX() != pathToLocation[0]->get_col() || robot.getY() != pathToLocation[0]->get_row() || robot.getYaw() != (20 * 3.14 / 180) ){
		robot.read();
		robot.setOdometry(pathToLocation[0]->get_col()  , pathToLocation[0]->get_row() , 20 * 3.14 / 180 );
		cout << "bla" <<endl;
	}**/
	cout << "lets start"<<endl;

	robot.read();

	robot.read();
	Driver driver(&robot);

	Particle* first_particle = new Particle(pathToLocation[0]->get_col(),pathToLocation[0]->get_row(), 20 * 3.14 / 180 );
	LocalizationManager* lm = new LocalizationManager();
	Particle* particle;
	for (unsigned int i = 1; i<pathToLocation.size();i++){
		//while (abs(robot.getX() - pathToLocation[i]->get_col()) > 0.1 &&
		//		abs(robot.getY() - pathToLocation[i]->get_row()) > 0.1)
		//{
			driver.moveToNextWaypoint(pathToLocation[i]->get_col(), pathToLocation[i]->get_row());
			cout << "(" << robot.getX() << "," << robot.getY() << "," << robot.getYaw() << ")"<< endl;
		/**if ((rand() % 12) >5){
				robot.CalculateDelats();
				lm->update(robot.getDeltaX(),robot.getDeltaY(),robot.getDeltaYaw(),robot.getLaserProxy(),*map);
				lm->resampleParticles(robot);
				 particle = lm->getBestParticle();

				cout << "i am at: " << endl
					 << "X: " << robot.getX() << " Y: " << robot.getY() << " Yaw: " << robot.getYaw() << endl
					 << "I think: " << endl
					 << "X: " << particle->getXPos() << " Y: " << particle->getYPos() << " Yaw: " << particle->getyaw() << endl;




			}**/
		//}
	}





	return 0;
}
