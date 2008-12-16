#include <boost/python.hpp>
#include "Common/b2Math.h"
#include "Collision/b2Collision.h"
#include "Dynamics/b2World.h"
#include "Dynamics/b2Body.h"

void export_body() {
  using namespace boost::python;

	// b2Body.h
	class_< b2Body, boost::noncopyable >("body", no_init)
		.def("create_shape",         &b2Body::CreateShape, return_value_policy< reference_existing_object >())
		.def("set_mass_from_shapes", &b2Body::SetMassFromShapes)
		.def("set_xform",            &b2Body::SetXForm)
		.def("get_xform",            &b2Body::GetXForm, return_value_policy< copy_const_reference >())
		.def("get_position",         &b2Body::GetPosition, return_value_policy< copy_const_reference >())
		.def("get_angle",            &b2Body::GetAngle)
		.def("get_mass",             &b2Body::GetMass)
		.def("wake_up",              &b2Body::WakeUp)
		.def("is_static",            &b2Body::IsStatic)
		.def("is_dynamic",           &b2Body::IsDynamic)
		.def("next",                 &b2Body::GetNext, return_value_policy< reference_existing_object >())
		.def("first_shape",          &b2Body::GetShapeList, return_value_policy< reference_existing_object >())
		;

	class_<b2BodyDef>("body_def")
		.def_readwrite("position", &b2BodyDef::position)
		.def_readwrite("angle", &b2BodyDef::angle)
		;
	
}

