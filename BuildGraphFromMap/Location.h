/*
 * Location.h
 *
 *  Created on: Jun 14, 2016
 *      Author: colman
 */

#ifndef LOCATION_H_
#define LOCATION_H_

class Location {
private:
	double row;
	double col;
public:
	Location(double row, double col);
	double get_row();
	double get_col();
	void set_row(double row);
	void set_col(double col);
	double calc_distance(Location* otherlocation);
	virtual ~Location();
};

#endif /* LOCATION_H_ */
