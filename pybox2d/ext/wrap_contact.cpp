#include <boost/python.hpp>
//#include "Common/b2Math.h"
#include "Dynamics/Contacts/b2Contact.h"

void export_contact() {
	using namespace boost::python;

	class_< b2ContactResult >("ContactResult")
		.def_readonly("shape1",            &b2ContactResult::shape1)
		.def_readonly("shape2",            &b2ContactResult::shape2)
		.def_readonly("position",          &b2ContactResult::position)
		.def_readonly("normal",            &b2ContactResult::normal)
		.def_readonly("normal_impulse",    &b2ContactResult::normalImpulse)
		.def_readonly("normal_impulse",    &b2ContactResult::tangentImpulse)
//		.def_readonly("contact_id",        &b2ContactPoint::id) // how to wrap unions?
	  ;

	class_< b2ContactPoint >("ContactPoint")
		.def_readonly("shape1",            &b2ContactPoint::shape1)
		.def_readonly("shape2",            &b2ContactPoint::shape2)
		.def_readonly("position",          &b2ContactPoint::position)
		.def_readonly("velocity",          &b2ContactPoint::velocity)
		.def_readonly("normal",            &b2ContactPoint::normal)
		.def_readonly("separation",        &b2ContactPoint::separation)
		.def_readonly("friction",          &b2ContactPoint::friction)
		.def_readonly("restitution",       &b2ContactPoint::restitution)
//		.def_readonly("contact_id",        &b2ContactPoint::id) // how to wrap unions?
	  ;
}
