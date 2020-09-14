#include <iostream>
#include "Main.h"
#include "ParkingLot.h"

using namespace std;

int main() {
	int choice = 0;
	string name = "";
	Parking::ParkingLot p;

	do {
		p.printParkingLot();
		cout << "Choose 1 to park in" << endl;
		cout << "Choose 2 to park out" << endl;
		cout << "Choose 3 to find available place" << endl;
		cout << "Choose 4 to find your car" << endl;
		cout << "Choose 0 for exit" << endl;

		cout << endl << "What's your choice? ";
		cin >> choice;

		switch (choice) {
		case PARK_IN: // 1
			p.parkCar(1);
			break;

		case PARK_OUT: // 2
			p.parkCar(0);
			break;

		case FIND_PLACE: // 3 
			p.findPlace();
			break;

		case FIND_CAR:
			p.findCar();
			break;

		case EXIT:
			cout << "\nThank you for using our service\nGoodbye" << endl;
			break;

		default:
			cout << "\nERROR : Wrong input" << endl;
			break;
		}

	} while (choice != 0);

	return 0;
}