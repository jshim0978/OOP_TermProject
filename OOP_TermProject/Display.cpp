#include "Display.h"
#include "Place.h"
#include "ParkingPlace.h"

using namespace std;

namespace Parking {
	//shows 2d array parking lot with route from car to entrance / restroom / elevator
	void Display::print(PlaceArr map) {
		SetConsoleTextAttribute(hConsole, 128);
		cout << "<This is the parking lot>" << endl;
		cout << "  # : Parking place" << endl;
		SetConsoleTextAttribute(hConsole, 138);
		cout << "  # : Parking place for the disabled only" << endl;
		SetConsoleTextAttribute(hConsole, 129);
		cout << "  # : Parking place for the disabled first" << endl;
		SetConsoleTextAttribute(hConsole, 139);
		cout << "  T : Toilet" << endl;
		SetConsoleTextAttribute(hConsole, 141);
		cout << "  E : Elevator" << endl;
		SetConsoleTextAttribute(hConsole, 15);

		printf("\n   ");
		for (int j = 0; j < COLS; j++) {
			printf(" %d ", j);
		}
		printf("\n");
		for (int i = 0; i <= ROWS; i++) {
			printf("  ");
			for (int j = 0; j <= COLS; j++) {
				draw1(map, i, j);
			}
			cout << endl;

			printf("%d ", i);
			for (int j = 0; j <= COLS; j++) {
				draw2(map, i, j);
			}
			cout << endl;
		}
		printf("\x1b[A \n");
	}

	void Display::draw1(PlaceArr map, int i, int j) {
		switch (rel(map, i, j)) {
		case 0:
			cout << "   ";
			break;

		case 1:
			cout << "戎  ";
			break;
		case 2:
			cout << "戌式式";
			break;
		case 4:
			cout << "忙式式";
			break;
		case 8:
			cout << "忖  ";
			break;

		case 3:
			cout << "扛式式";
			break;
		case 6:
			cout << "戍式式";
			break;
		case 12:
			cout << "成式式";
			break;
		case 9:
			cout << "扣  ";
			break;

		default:
			cout << "托式式";
			break;
		}
	}

	void Display::draw2(PlaceArr map, int i, int j) {
		int _rel = rel(map, i, j);
		_rel >>= 2;

		switch (_rel) {
		case 0:
			cout << "   ";
			break;
		case 1:
		case 3:
			cout << "弛 ";
			printOwnerName(map, i, j);
			break;
		case 2:
			cout << "弛  ";
			break;
		}
	}

	void Display::printOwnerName(PlaceArr map, int i, int j) {
		int k = 15;
		char name = map[i][j].getOwnerName()[0];
		Place::Type t = map[i][j].getType();
		switch (t) {
		case Place::Type::PATH:
			name = ' ';
			break;
		case Place::Type::TOILET:
			k = 11;
			name = 'T';
			break;
		case Place::Type::ELEVATOR:
			k = 13;
			name = 'E';
			break;
		default:
			if (map[i][j].getDis() == Place::Dis::DISONLY) {
				k = 10;
			}
			else if (map[i][j].getDis() == Place::Dis::FLEX) {
				k = 9;
			}
			break;
		}
		SetConsoleTextAttribute(hConsole, k);
		cout << name;
		SetConsoleTextAttribute(hConsole, 15);
	}

	int Display::rel(PlaceArr map, int i, int j) {
		int ret = 0;

		if (i >= 1 && j >= 1)
			if (map[i - 1][j - 1].getType() != Place::Type::PATH) ret += 1;

		if (i >= 1 && j < COLS)
			if (map[i - 1][j].getType() != Place::Type::PATH) ret += 2;

		if (i < ROWS && j < COLS)
			if (map[i][j].getType() != Place::Type::PATH) ret += 4;

		if (i < ROWS && j >= 1)
			if (map[i][j - 1].getType() != Place::Type::PATH) ret += 8;

		return ret;
	}
}