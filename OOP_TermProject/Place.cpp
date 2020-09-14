#include "Place.h"
#include <iostream>

using namespace std;

namespace Parking {
	// set defaults
	Place::Place() :
		type(Place::Type::PARK),
		placeStatus(Place::Status::BLOCKED),
		dis(Place::Dis::GENERAL),
		ownerName(" "),
		//row(-1), 
		//col(-1),
		floor(nextFloor()),
		fee(3900) {}
	Place::Place(Place::Type type) {
		this->Place::Place();
		this->setType(type);
	}
	//Place::Place(int r, int c) {
	//	this->Place::Place();

	//	//this->setRow(r);
	//	//this->setCol(c);
	//}

	/* getter, setter */
	//int Place::getRow() {
	//	return row;
	//}
	//void Place::setRow(int row) {
	//	this->row = row;
	//}

	//int Place::getCol() {
	//	return col;
	//}
	//void  Place::setCol(int col) {
	//	this->col = col;
	//}

	Place::Type Place::getType() {
		return type;
	}
	void Place::setType(Place::Type type) {
		this->type = type;
	}

	int Place::nextFloor() {
		static int s_nextfloor = 0;
		return ++s_nextfloor;
	}
	int Place::getFloor() {
		return floor;
	}
	void Place::setFloor(int floor) {
		this->floor = floor;
	}

	int Place::getFee() {
		return fee;
	}
	void Place::setFee(int fee) {
		this->fee = fee;
	}
	Place::Dis Place::getDis() {
		return dis;
	}
	void Place::setDis(Place::Dis dis) {
		this->dis = dis;
	}

	Place::Status Place::getCurrentStatus() {
		return placeStatus;
	}
	void Place::setCurrentStatus(Status currentStatus) {
		this->placeStatus = currentStatus;
	}

	string Place::getOwnerName() {
		return ownerName;
	}
	void Place::setOwnerName(string ownerName) {
		this->ownerName = ownerName;
	}
	/* end */
}