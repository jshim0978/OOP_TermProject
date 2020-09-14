#pragma once
#include <vector>
#include <windows.h>
#include "ParkingLot.h"

namespace Parking { class Place; class ParkingLot; }

namespace Parking
{
	class Display {
	public:
		//shows 2d array parking lot with route from car to entrance / restroom / elevator
		virtual void print(PlaceArr map);
	private:
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		void printOwnerName(PlaceArr map, int i, int j);
		void draw1(PlaceArr map, int i, int j);
		void draw2(PlaceArr map, int i, int j);
		int rel(PlaceArr map, int i, int j);
	};
}