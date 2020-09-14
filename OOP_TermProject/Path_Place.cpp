#include "Place.h"
#include "Path_Place.h"

namespace Parking {
	Path_Place::Path_Place() {
		__super::Place();
		setType(Place::Type::PATH);
	}
}