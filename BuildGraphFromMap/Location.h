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
	unsigned int row;
	unsigned int col;
public:
	Location(unsigned int row, unsigned int col);
	unsigned int get_row();
	unsigned int get_col();
	void set_row(unsigned int row);
	void set_col(unsigned int col);
	virtual ~Location();
};

#endif /* LOCATION_H_ */
