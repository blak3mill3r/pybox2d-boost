#include <boost/python.hpp>
#include "Common/b2Math.h"
#include "Collision/b2Collision.h"
#include "Dynamics/b2World.h"
#include "Dynamics/b2Body.h"

void export_collision() {
  using namespace boost::python;
	// b2Collision.h
	class_<b2AABB>("AABB")
		.def_readwrite("lower_bound", &b2AABB::lowerBound)
		.def_readwrite("upper_bound", &b2AABB::upperBound)
		;

}
