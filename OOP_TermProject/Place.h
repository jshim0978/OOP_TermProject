#pragma once
#include <iostream>

namespace Parking {
	class Place {
	public:
		enum class Type {
			PATH,
			PARK,
			TOILET,
			ELEVATOR
		};

		enum class Status {
			EMPTY,
			OCCUPIED,
			BLOCKED
		};

		enum class Dis {
			GENERAL,
			DISONLY,
			FLEX
		};

	private:
		Type type = static_cast<Type>(0); // path or parking place or else
		Status placeStatus = static_cast<Status>(0); // parking place's status
		Dis dis = static_cast<Dis>(0); // for disabled or not ~~

		std::string ownerName; // name of the car's owner 
		//int row, col; // place's position (used for 
		int floor;
		int fee;
		
	public:
		Place();
		Place(Place::Type type);
		//Place(int r, int c);

		/* getter, setter */
		//virtual int getRow();
		//virtual void setRow(int row);

		//virtual int getCol();
		//virtual void setCol(int col);

		virtual Place::Type getType();
		virtual void setType(Place::Type type);

		// returns (static int) next floor number and increases it
		virtual int nextFloor(); // used in Place constructor
		virtual int getFloor();
		virtual void setFloor(int floor);

		virtual int getFee();
		virtual void setFee(int fee);

		virtual Place::Dis getDis();
		virtual void setDis(Place::Dis dis);

		virtual Status getCurrentStatus();
		virtual void setCurrentStatus(Status currentStatus);

		virtual std::string getOwnerName();
		virtual void setOwnerName(std::string ownerName);
	};
}