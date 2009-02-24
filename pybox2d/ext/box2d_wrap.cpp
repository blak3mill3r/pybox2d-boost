#include <boost/python.hpp>

#include "Common/b2Math.h"
#include "Collision/b2Collision.h"
#include "Dynamics/b2World.h"
#include "Dynamics/b2Body.h"

void export_collision();
void export_math();
void export_world();
void export_body();
void export_shapes();
void export_joints();
void export_callbacks();
void export_contact();

BOOST_PYTHON_MODULE(pybox2d_ext)
{
  using namespace boost::python;
	export_math();
	export_collision();
	export_body();
	export_shapes();
	export_world();
	export_joints();
	export_callbacks();
	export_contact();
}

