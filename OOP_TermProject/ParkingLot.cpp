#include <iostream>
#include <time.h>
#include "ParkingLot.h"
#include "Place.h"
#include "ParkingPlace.h"
#include "Path_Place.h"
#include "Display.h"

using namespace std;

namespace Parking {

	/* 00:path, 11:park, 12:park_dis, 13:flexable(you know what i mean),
	 * 22:toilet, 33:elevator
	 * else is blocked place */
	int baseArray[ROWS][COLS] = {
			{22, 11, 11, 11, 11, 11, 33},
			{11, 00, 00, 00, 00, 00, 12},
			{11, 00, 11, 00, 11, 00, 13},
			{11, 00, 11, 00, 11, 00, 13},
			{11, 00, 11, 00, 11, 00, 11},
			{11, 00, 11, 00, 11, 00, 11},
			{22, 11, 11, 00, 11, 11, 33} };

	// constructor
	ParkingLot::ParkingLot() {
		parkingLotMap = ParkingLot::makeParkingLotMap();
	}

	// destructor
	ParkingLot::~ParkingLot() {
		if(parkingLotMap) delete[] parkingLotMap;
	}

	// make map from base int array
	PlaceArr ParkingLot::makeParkingLotMap() {
		Place (*map)[COLS] = new Place[ROWS][COLS];
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				switch (baseArray[i][j]) {
				default: // default is blocked place
					map[i][j] = *new Place();
					break;
				case 00: // path
					map[i][j] = *new Path_Place();
					break;
				case 11: // parking place
					map[i][j] = *new ParkingPlace();
					break;
				case 12: // for disabled people only
					map[i][j] = *new ParkingPlace();
					map[i][j].setDis(Place::Dis::DISONLY);
					break;
				case 13: // for disabled people first
					map[i][j] = *new ParkingPlace();
					map[i][j].setDis(Place::Dis::FLEX);
					break;
				case 22: // toilet
					map[i][j] = *new Place(Place::Type::TOILET);
					break;
				case 33: // elevator
					map[i][j] = *new Place(Place::Type::ELEVATOR);
					break;
				}
			}
		}
		return map;
	}

	//bool ParkingLot::isEmpty(int row, int col) {
	//	if (isAvailable(row, col)) return true;
	//	else return false;
	//}

	void ParkingLot::parkIn(int row, int col, string name) {
		parkingLotMap[row][col].setOwnerName(name);
		parkingLotMap[row][col].setCurrentStatus(ParkingPlace::Status::OCCUPIED);
	}

	void ParkingLot::parkOut(int row, int col) {
		parkingLotMap[row][col].setOwnerName("#");
		parkingLotMap[row][col].setCurrentStatus(ParkingPlace::Status::EMPTY);
	}

	void ParkingLot::printParkingLot() {
		Display d;
		d.print(parkingLotMap);
	}

	// Park in/out
	void ParkingLot::parkCar(int newStatus) {
		int row, col;
		string ownerName;
		char disability;
		bool fail = false;
		cout << "Enter row and col: ";
		cin >> row >> col;

		if (newStatus == 0)
			parkOut(row, col);
		else {
			if (parkingLotMap[row][col].getDis() == Place::Dis::DISONLY) { // 장애인 조건 검사
				cout << "Do you have a disability? (y/n)";
				cin >> disability;
				if (disability == 'n' || disability == 'N') {
					cout << endl << "This place is for the drivers with a disabled person only" << endl << endl;
					system("pause"); 
					return;
				}
			}
			else if (parkingLotMap[row][col].getDis() == Place::Dis::FLEX) {
				if (!isFull()) { // 일반 주차 공간이 다 차지 않으면 장애인만 사용 가능
					cout << "Do you have a disability? (y/n)";
					cin >> disability;
					if (disability == 'n' || disability == 'N') {
						cout << endl << "You can use this place when general spaces are full" << endl << endl;
						system("pause"); 
						return;
					}
				}
			}

			if (isAvailable(row, col, false)) {
				cout << "Your name: ";
				cin >> ownerName;
				parkIn(row, col, ownerName);
				cout << endl << "Parked at (" << row << ", " << col << ")" << endl << endl;
			}
			else cout << endl << "Unavailable parking place" << endl << endl;
		}
		system("pause");
	}

	void ParkingLot::findPlace() {  // 여기서 추가
		bool d_empty = false;
		char dis_t;
		bool dis = false;

		int row = 0;
		cout << "Do you have a disability?(y/n)";
		cin >> dis_t;
		if (dis_t == 'y') dis = true;

		cout << "Enter a row where you want to park: ";
		cin >> row;

		if (!findPlaceRecursion(row, 0, dis))
			cout << "There are no available places on row " << row << endl;

		//else {
		//	for (int i = 0; i < 4; i++) {
		//		if (isAvailable(i, 0, true)) {
		//			printf("The available place is at [%d , %d]\n", i, 0); // 빈 장애인 구역으로 찾아줌
		//			d_empty = true;
		//			break;
		//		}
		//	}
		//	if (!d_empty) { // 장애인 주차 구역이 비어있지 않으면 일반 구역으로 
		//		cout << "Enter a row where you want to park: ";
		//		cin >> row;

		//		if (!findPlaceRecursion(row, 0, dis))
		//			cout << "There are no available places on row " << row << endl;
		//	}
		//}

		system("pause");
	}

	//bool ParkingLot::findPlaceRecursion(int row, int col, char disability) {
	//	if (col == COLS) {
	//		return false;
	//		//end of row
	//	}
	//	else if (isEmpty(row, col)) {
	//		if (row < 4 && col == 0 && disability != 'y') {
	//			if (!(row >= 2 && isFull()))
	//				return findPlaceRecursion(row, col + 1, disability);
	//			else {
	//				printf("The available place is at [%d , %d]\n", row, col);
	//				return true;
	//			}
	//		}
	//		else {
	//			printf("The available place is at [%d , %d]\n", row, col);
	//			return true;
	//		}
	//	}
	//	else {
	//		return findPlaceRecursion(row, col + 1, disability);
	//	}
	//}

	bool ParkingLot::findPlaceRecursion(int row, int col, bool dis) {
		if (col == COLS) { // end of row
			if (dis)  // if there is no place for disabled, find normal place
				findPlaceRecursion(row, col, false);
			else // else return false
				return false;
		}
		else if (isAvailable(row, col, dis)) {
			printf("The available place is at [%d , %d]\n", row, col);
			return true;
		}
		else {
			return findPlaceRecursion(row, col + 1, dis);
		}
	}

	void ParkingLot::findCar() {
		string name = "";
		cout << "Enter your name" << endl;
		cin >> name;

		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				if (parkingLotMap[i][j].getOwnerName() == name) {
					printf("Your car is at [%d, %d].", i, j);
					return;
				}
			}
		}

		printf("WRONG INPUT: Owner name unmatched.");
	}

	bool ParkingLot::isAvailable(int row, int col, bool dis) {
		if (dis) // disabled person
			if (parkingLotMap[row][col].getCurrentStatus() == ParkingPlace::Status::EMPTY)
				return true;
		else { // normal person
			if (parkingLotMap[row][col].getDis() == Place::Dis::DISONLY)
				return false;
			else if (parkingLotMap[row][col].getDis() == Place::Dis::FLEX) {
				if (isFull()) {
					return true;
				}
				else return false;
			}
			else if (parkingLotMap[row][col].getCurrentStatus() == ParkingPlace::Status::EMPTY)
				return true;
		}

		return false;
	}

	bool ParkingLot::isFull() {
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				if (parkingLotMap[i][j].getDis() == Place::Dis::GENERAL) {
					if (parkingLotMap[i][j].getCurrentStatus() == ParkingPlace::Status::EMPTY)
						return false;
				}
			}
		}
		return true;
	}

	void ParkingLot::fee() {
		Place* feeNFloor = new Place;

		int currentFee = feeNFloor->getFee();
		int currentFloor = feeNFloor->getFloor();

		time_t rawTime;
		time(&rawTime);

		struct tm* timeInfo = new tm;
		localtime_s(timeInfo, &rawTime);
		int currentHour = timeInfo->tm_hour;
		int currentMin = timeInfo->tm_min;

		if (currentHour >= 16 && currentHour <= 20) {
			currentFee -= currentFloor * 200;
		}

		printf("Now is %d : %d ,this floor is %d, fee is %d per hour \n",currentHour, currentMin, currentFloor ,currentFee);
	}
}