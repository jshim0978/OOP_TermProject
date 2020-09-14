#include "ParkingPlace.h"

using namespace std;

namespace Parking{
	ParkingPlace::ParkingPlace() {
		__super::Place();
		this->setType(Place::Type::PARK);
		this->setCurrentStatus(Place::Status::EMPTY);
		this->setOwnerName("#");
	}
}
