#include <boost/python.hpp>
#include "Common/b2Math.h"
#include "Collision/b2Collision.h"
#include "Dynamics/b2World.h"
#include "Dynamics/b2Body.h"
#include "Dynamics/Joints/b2Joint.h"
//#include "Dynamics/Joints/b2LineJoint.h"
#include "Dynamics/Joints/b2RevoluteJoint.h"
#include "Dynamics/Joints/b2PulleyJoint.h"
#include "Dynamics/Joints/b2DistanceJoint.h"
#include "Dynamics/Joints/b2GearJoint.h"
#include "Dynamics/Joints/b2PrismaticJoint.h"
#include "Dynamics/Joints/b2MouseJoint.h"

void export_joints() {
	using namespace boost::python;

	// the baseclass: this covers joints in general
	class_<b2JointDef>("JointDef")
		.def_readwrite("collide_connected",   &b2JointDef::collideConnected)
		.def_readwrite("body1",               &b2JointDef::body1)
		.def_readwrite("body2",               &b2JointDef::body2)
	  ;

	class_< b2Joint, boost::noncopyable >("Joint", no_init)
		.add_property("body1",                make_function(&b2Joint::GetBody1, return_value_policy< reference_existing_object >()))
		.add_property("body2",                make_function(&b2Joint::GetBody2, return_value_policy< reference_existing_object >()))
		//.add_property("collide_connected",    &b2Joint::GetCollideConnected)
		.add_property("next",                 make_function(&b2Joint::GetNext, return_value_policy< reference_existing_object >()))
	  ;

	/*
	 * Now all the joints in their alphabetical order
	 * first b2...JointDef, then Joint
	 */

	// Distance Joints
	class_< b2DistanceJointDef, bases< b2JointDef > >("DistanceJointDef")
		.def_readwrite("length",              &b2DistanceJointDef::length)
		.def_readwrite("response_speed",      &b2DistanceJointDef::frequencyHz)
		.def_readwrite("damping",             &b2DistanceJointDef::dampingRatio)
		.def(          "initialize",          &b2DistanceJointDef::Initialize)
	  ;

	class_< b2DistanceJoint, bases< b2Joint > >("DistanceJoint", init< b2DistanceJointDef * >() )
		.add_property("anchor1",              &b2DistanceJoint::GetAnchor1)
		.add_property("anchor1",              &b2DistanceJoint::GetAnchor1)
		.add_property("reaction_force",       &b2DistanceJoint::GetReactionForce)
		.add_property("reaction_torque",      &b2DistanceJoint::GetReactionTorque)
	  ;

	// Gear Joints
	class_< b2GearJointDef, bases< b2JointDef > >("gear_joint_def")
		.def_readwrite("joint1",              &b2GearJointDef::joint1)
		.def_readwrite("joint2",              &b2GearJointDef::joint2)
		.def_readwrite("gear_ratio",          &b2GearJointDef::ratio)
	  ;

	class_< b2GearJoint, bases< b2Joint > >("GearJoint", init< b2GearJointDef * >() )
		.add_property("anchor1",              &b2GearJoint::GetAnchor1)
		.add_property("anchor1",              &b2GearJoint::GetAnchor1)
		.add_property("reaction_force",       &b2GearJoint::GetReactionForce)
		.add_property("reaction_torque",      &b2GearJoint::GetReactionTorque)
		.add_property("gear_ratio",           &b2GearJoint::GetRatio)
	  ;

	// Line Joint
	//class_< b2LineJointDef, bases< b2JointDef > >("LineJointDef")
	//	.def_readwrite("anchor1",             &b2LineJointDef::localAnchor1)
	//	.def_readwrite("anchor2",             &b2LineJointDef::localAnchor2)
	//	.def_readwrite("limited",             &b2LineJointDef::enableLimit)
	//	.def_readwrite("local_axis1",         &b2LineJointDef::localAxis1)
	//	.def_readwrite("lower_translation",   &b2LineJointDef::lowerTranslation)
	//	.def_readwrite("motorized",           &b2LineJointDef::enableMotor)
	//	.def_readwrite("motor_force",         &b2LineJointDef::maxMotorForce)
	//	.def_readwrite("motor_speed",         &b2LineJointDef::motorSpeed)
	//	.def_readwrite("upper_translation",   &b2LineJointDef::upperTranslation)
	//	.def(          "initialize",          &b2LineJointDef::Initialize)
	//  ;

	//class_< b2LineJoint, bases < b2Joint > >("LineJoint", init< b2LineJointDef * >() )
	//	.add_property("anchor1",              &b2LineJoint::GetAnchor1)
	//	.add_property("anchor1",              &b2LineJoint::GetAnchor1)
	//	.add_property("reaction_force",       &b2LineJoint::GetReactionForce)
	//	.add_property("reaction_torque",      &b2LineJoint::GetReactionTorque)

	//	.add_property("current_speed",        &b2LineJoint::GetJointSpeed)
	//	.add_property("current_translation",  &b2LineJoint::GetJointTranslation)
	//	.add_property("limited",              &b2LineJoint::IsLimitEnabled, &b2PrismaticJoint::EnableLimit)
	//	.add_property("lower_limit",          &b2LineJoint::GetLowerLimit)
  //      	.add_property("motorized",            &b2LineJoint::IsMotorEnabled, &b2PrismaticJoint::EnableMotor)
	//	.add_property("motor_speed",          &b2LineJoint::GetMotorSpeed, &b2PrismaticJoint::SetMotorSpeed)
	//	.add_property("motor_force",          &b2LineJoint::GetMotorForce, &b2PrismaticJoint::SetMaxMotorForce)
	//	.add_property("upper_limit",          &b2LineJoint::GetUpperLimit)
	//	.def(         "set_limits",           &b2LineJoint::SetLimits)

	//  ;

	// Mouse Joint
	class_< b2MouseJointDef, bases< b2JointDef > >("MouseJointDef")
		.def_readwrite("target",              &b2MouseJointDef::target,        "")
		.def_readwrite("max_force",           &b2MouseJointDef::maxForce,      "")
		.def_readwrite("response_speed",      &b2MouseJointDef::frequencyHz,   "")
		.def_readwrite("damping",             &b2MouseJointDef::dampingRatio,  "")
	;

	class_< b2MouseJoint, bases< b2Joint > >("MouseJoint", init< b2MouseJointDef * >() ) // or no_init
		.add_property("anchor1",              &b2MouseJoint::GetAnchor1)
		.add_property("anchor1",              &b2MouseJoint::GetAnchor1)
		.add_property("reaction_force",       &b2MouseJoint::GetReactionForce)
		.add_property("reaction_torque",      &b2MouseJoint::GetReactionTorque)
		.def(         "set_target",           &b2MouseJoint::SetTarget)
	;

	// Prismatic Joint
	class_< b2PrismaticJointDef, bases< b2JointDef > >("PrismaticJointDef")
		.def_readwrite("anchor1",             &b2PrismaticJointDef::localAnchor1)
		.def_readwrite("anchor2",             &b2PrismaticJointDef::localAnchor2)
		.def_readwrite("limited",             &b2PrismaticJointDef::enableLimit)
		.def_readwrite("lower_translation",   &b2PrismaticJointDef::lowerTranslation)
		.def_readwrite("motorized",           &b2PrismaticJointDef::enableMotor)
		.def_readwrite("motor_force",         &b2PrismaticJointDef::maxMotorForce)
		.def_readwrite("motor_speed",         &b2PrismaticJointDef::motorSpeed)
		.def_readwrite("upper_translation",   &b2PrismaticJointDef::upperTranslation)
		.def_readwrite("reference_angle",     &b2PrismaticJointDef::referenceAngle)
		.def(          "initialize",          &b2PrismaticJointDef::Initialize)
	  ;

	class_< b2PrismaticJoint, bases< b2Joint > >("PrismaticJoint", init< b2PrismaticJointDef * >() )
		.add_property("anchor1",              &b2PrismaticJoint::GetAnchor1)
		.add_property("anchor1",              &b2PrismaticJoint::GetAnchor1)
		.add_property("reaction_force",       &b2PrismaticJoint::GetReactionForce)
		.add_property("reaction_torque",      &b2PrismaticJoint::GetReactionTorque)

		.add_property("current_speed",        &b2PrismaticJoint::GetJointSpeed)
		.add_property("current_translation",  &b2PrismaticJoint::GetJointTranslation)
		.add_property("limited",              &b2PrismaticJoint::IsLimitEnabled, &b2PrismaticJoint::EnableLimit)
		.add_property("lower_limit",          &b2PrismaticJoint::GetLowerLimit)
		.add_property("motorized",            &b2PrismaticJoint::IsMotorEnabled, &b2PrismaticJoint::EnableMotor)
		.add_property("motor_speed",          &b2PrismaticJoint::GetMotorSpeed, &b2PrismaticJoint::SetMotorSpeed)
		.add_property("motor_force",          &b2PrismaticJoint::GetMotorForce, &b2PrismaticJoint::SetMaxMotorForce)
		.add_property("upper_limit",          &b2PrismaticJoint::GetUpperLimit)
		.def(         "set_limits",           &b2PrismaticJoint::SetLimits)
	  ;

	// PulleyJoint
	class_< b2PulleyJointDef, bases< b2JointDef > >("PulleyJointDef")
		.def_readwrite("anchor1",             &b2PulleyJointDef::localAnchor1)
		.def_readwrite("anchor2",             &b2PulleyJointDef::localAnchor2)
		.def_readwrite("ground_anchor1",      &b2PulleyJointDef::groundAnchor1)
		.def_readwrite("ground_anchor2",      &b2PulleyJointDef::groundAnchor2)
		.def_readwrite("length1",             &b2PulleyJointDef::length1)
		.def_readwrite("length2",             &b2PulleyJointDef::length2)
		.def_readwrite("maxlength1",          &b2PulleyJointDef::maxLength1)
		.def_readwrite("maxlength2",          &b2PulleyJointDef::maxLength2)
		.def_readwrite("pulley_ratio",        &b2PulleyJointDef::ratio)
		.def(          "initialize",          &b2PulleyJointDef::Initialize)
	  ;

	class_< b2PulleyJoint, bases< b2Joint > >("PulleyJoint", init< b2PulleyJointDef * >() )
		.add_property("anchor1",              &b2PulleyJoint::GetAnchor1)
		.add_property("anchor1",              &b2PulleyJoint::GetAnchor1)
		.add_property("reaction_force",       &b2PulleyJoint::GetReactionForce)
		.add_property("reaction_torque",      &b2PulleyJoint::GetReactionTorque)

		.add_property("ground_anchor1",       &b2PulleyJoint::GetGroundAnchor1)
		.add_property("ground_anchor2",       &b2PulleyJoint::GetGroundAnchor2)
		.add_property("length1",              &b2PulleyJoint::GetLength1)
		.add_property("length2",              &b2PulleyJoint::GetLength2)
		.add_property("pulley_ratio",         &b2PulleyJoint::GetRatio)
	  ;

	// Revolute Joint
	class_< b2RevoluteJoint, bases< b2Joint > >("RevoluteJoint", init< b2RevoluteJointDef * >() )
		.add_property("current_angle",        &b2RevoluteJoint::GetJointAngle)
		.add_property("current_speed",        &b2RevoluteJoint::GetJointSpeed)
		.add_property("limited",              &b2RevoluteJoint::IsLimitEnabled, &b2RevoluteJoint::EnableLimit)
		.add_property("lower_limit",          &b2PrismaticJoint::GetLowerLimit)
		.add_property("motorized",            &b2RevoluteJoint::IsMotorEnabled, &b2RevoluteJoint::EnableMotor)
		.add_property("motor_speed",          &b2RevoluteJoint::GetMotorSpeed, &b2RevoluteJoint::SetMotorSpeed)
		.add_property("motor_torque",         &b2RevoluteJoint::GetMotorTorque, &b2RevoluteJoint::SetMaxMotorTorque)
		.add_property("upper_limit",          &b2PrismaticJoint::GetUpperLimit)
		.def(         "set_limits",           &b2RevoluteJoint::SetLimits)
	  ;

	class_< b2RevoluteJointDef, bases< b2JointDef > >("RevoluteJointDef")
		.def_readwrite("anchor1",             &b2RevoluteJointDef::localAnchor1,   "The local anchor point relative to body1's origin.")
		.def_readwrite("anchor2",             &b2RevoluteJointDef::localAnchor2,   "The local anchor point relative to body2's origin.")
		.def_readwrite("limited",             &b2RevoluteJointDef::enableLimit,    "A flag to enable joint limits.")
		.def_readwrite("lower_limit",         &b2RevoluteJointDef::lowerAngle,     "The lower angle for the joint limit (radians).")
		.def_readwrite("max_motor_torque",    &b2RevoluteJointDef::maxMotorTorque, "Rrrrrmrmmmrrmm :)")
		.def_readwrite("motorized",           &b2RevoluteJointDef::enableMotor,    "A flag to enable the joint motor.")
		.def_readwrite("motor_speed",         &b2RevoluteJointDef::motorSpeed,     "how fast can it spin")
		.def_readwrite("upper_limit",         &b2RevoluteJointDef::upperAngle,     "The upper angle for the joint limit (radians).")
		.def(          "initialize",          &b2RevoluteJointDef::Initialize,     "Initialize the bodies, anchors, and reference angle using the world anchor.")
	  ;

}
