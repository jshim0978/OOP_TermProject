#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>
#include "Place.h"

namespace Parking {
	static constexpr int ROWS = 7;
	static constexpr int COLS = 7;

	typedef Place(*PlaceArr)[COLS];
	class ParkingLot {
	private:
		Place (*parkingLotMap)[COLS];

		/* make map from base array */
		PlaceArr makeParkingLotMap();

		///* is empty? */
		//bool isEmpty(int row, int col);

		/* set */
		void parkIn(int row, int col, std::string name);

		/* set parking spot empty */
		void parkOut(int row, int col);

		/* check time with floor and calculate fee */
		void fee();
	public:
		ParkingLot();
		~ParkingLot();

		/* visualize parking lot */
		virtual void printParkingLot();

		/* parking car method - in & out */
		virtual void parkCar(int newStatus);

		/* check available spot is existing or not*/
		virtual void findPlace();

		/* check every col of row to see if empty */
		virtual bool findPlaceRecursion(int row, int col, bool dis);

		virtual void findCar();

		/*check row / col for availability*/
		virtual bool isAvailable(int row, int col, bool dis);

		/*check general space is full*/
		virtual bool isFull();
	};
}