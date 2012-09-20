#include <boost/python.hpp>
#include "Common/b2Math.h"
#include "Collision/b2Collision.h"
#include "Dynamics/b2World.h"
#include "Dynamics/b2Body.h"

using namespace boost::python;

PyObject* get_user_data_wrapper(b2Body *bd)
{
    PyObject *resultobj = 0;
    void *result = 0;
    result = (void*)(bd)->GetUserData();
    
    if (!result) {
        Py_RETURN_NONE;
    } else {
        resultobj = (PyObject*)result;
        return resultobj;
    }
}

void set_user_data_wrapper(b2Body *bd, PyObject *obj)
{
    PyObject* prev_val = 0;
    prev_val = get_user_data_wrapper(bd);
    Py_XDECREF(prev_val);
    
    Py_XINCREF(obj);
    bd->SetUserData(obj);
}

PyObject* del_user_data_wrapper(b2Body *bd)
{
    PyObject* user_data = 0;
    user_data = get_user_data_wrapper(bd);
    if(!(user_data == Py_None)) {
        Py_XDECREF(user_data);
    }
    Py_RETURN_NONE;
}


void sleep_switch(b2Body *bd, bool sleep)
{
    if(sleep) {
        bd->PutToSleep();
    } else {
        bd->WakeUp();
    }
}

void export_body() {
  using namespace boost::python;

	// b2Body.h
	class_< b2Body, boost::noncopyable >("body", no_init)
		.add_property("angular_velocity",     &b2Body::GetAngularVelocity, &b2Body::SetAngularVelocity)
		.add_property("bullet",               &b2Body::IsBullet, &b2Body::SetBullet)
		.add_property("dynamic",              &b2Body::IsDynamic)
		.add_property("frozen",               &b2Body::IsFrozen)
		.add_property("inertia",              &b2Body::GetInertia)
		.add_property("linear_velocity",      &b2Body::GetLinearVelocity, &b2Body::SetLinearVelocity)
		.add_property("local_center",         make_function(&b2Body::GetLocalCenter, return_value_policy< copy_const_reference >()))
		.add_property("mass",                 &b2Body::GetMass, &b2Body::SetMass)
		//.add_property("may_sleep",            &b2Body::CanSleep, &b2Body::AllowSleeping)
		.add_property("position",             make_function(&b2Body::GetPosition, return_value_policy< copy_const_reference >())) // TODO write a function to set the position
		//.add_property("rotation_fixed",       &b2Body::IsRotationFixed)
		.add_property("sleeping",             &b2Body::IsSleeping, &sleep_switch)
		.add_property("static",               &b2Body::IsStatic)
		.add_property("user_data",            &get_user_data_wrapper, &set_user_data_wrapper)
		.add_property("world",                make_function(&b2Body::GetWorld, return_value_policy< reference_existing_object >()))
		.add_property("world_center",         make_function(&b2Body::GetWorldCenter, return_value_policy< copy_const_reference >()))
		.add_property("xform",                make_function(&b2Body::GetXForm, return_value_policy < copy_const_reference >()), &b2Body::SetXForm)
		.def(         "allow_sleeping",       &b2Body::AllowSleeping)
		.def(         "apply_force",          &b2Body::ApplyForce)
		.def(         "apply_impulse",        &b2Body::ApplyImpulse)
		.def(         "apply_torque",         &b2Body::ApplyTorque)
		//.def(         "can_sleep",            &b2Body::CanSleep)
		.def(         "create_shape",         &b2Body::CreateShape, return_value_policy< reference_existing_object >())
		.def(         "destroy_shape",        &b2Body::DestroyShape)
		.def(         "get_angle",            &b2Body::GetAngle)
		.def(         "get_angular_velocity", &b2Body::GetAngularVelocity)
		.def(         "get_intertia",         &b2Body::GetInertia)
		.def(         "get_linear_velocity",  &b2Body::GetLinearVelocity)
		.def(         "get_linear_velocity_from_world_point", &b2Body::GetLinearVelocityFromWorldPoint)
		.def(         "get_linear_velocity_from_local_point", &b2Body::GetLinearVelocityFromLocalPoint)
		.def(         "get_local_center",     &b2Body::GetLocalCenter, return_value_policy< copy_const_reference >())
		.def(         "get_local_point",      &b2Body::GetLocalPoint)
		.def(         "get_local_vector",     &b2Body::GetLocalVector)
		.def(         "get_mass",             &b2Body::GetMass)
        .def(         "get_position",         &b2Body::GetPosition, return_value_policy< copy_const_reference >())
        .def(         "get_user_data",        &get_user_data_wrapper)//, return_value_policy< reference_existing_object >()) <-- COMPILE ERROR
        .def(         "get_world",            &b2Body::GetWorld, return_value_policy< reference_existing_object >())
		.def(         "get_world_center",     &b2Body::GetWorldCenter, return_value_policy< copy_const_reference >())
		.def(         "get_world_point",      &b2Body::GetWorldPoint)
		.def(         "get_world_vector",     &b2Body::GetWorldVector)
		.def(         "get_xform",            &b2Body::GetXForm, return_value_policy< copy_const_reference >())
		.def(         "is_bullet",            &b2Body::IsBullet)
		.def(         "is_dynamic",           &b2Body::IsDynamic)
		.def(         "is_frozen",            &b2Body::IsFrozen)
		//.def(         "is_rotation_fixed",    &b2Body::IsRotationFixed)
		.def(         "is_sleeping",          &b2Body::IsSleeping)
		.def(         "is_static",            &b2Body::IsStatic)
		.def(         "set_angular_velocity", &b2Body::SetAngularVelocity)
		.def(         "set_bullet",           &b2Body::SetBullet)
		.def(         "set_linear_velocity",  &b2Body::SetLinearVelocity)
		.def(         "set_mass",             &b2Body::SetMass)
		.def(         "set_mass_from_shapes", &b2Body::SetMassFromShapes)
        .def(         "set_user_data",        &set_user_data_wrapper)
		.def(         "set_xform",            &b2Body::SetXForm)
		.def(         "wake_up",              &b2Body::WakeUp)
		.def(         "next",                 &b2Body::GetNext, return_value_policy< reference_existing_object >())  // should be get_next to match b2Body.h
		.def(         "first_shape",          &b2Body::GetShapeList, return_value_policy< reference_existing_object >())
		.def(         "__del__",              &del_user_data_wrapper)
		;

	class_<b2BodyDef>("body_def")
		.def_readwrite("angle",               &b2BodyDef::angle)
		.def_readwrite("angular_damping",     &b2BodyDef::angularDamping)
		.def_readwrite("fixed_rotation",      &b2BodyDef::fixedRotation)
		.def_readwrite("initially_sleeping",  &b2BodyDef::isSleeping)
		.def_readwrite("bullet",              &b2BodyDef::isBullet)
		.def_readwrite("linear_damping",      &b2BodyDef::linearDamping)
		.def_readwrite("mass",                &b2BodyDef::massData)
		//.def_readwrite("may_sleep",           &b2BodyDef::allowSleep)
		.def_readwrite("position",            &b2BodyDef::position)
		;
	
}

