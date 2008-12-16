#include <boost/python.hpp>
#include "Common/b2Math.h"
#include "Collision/b2Collision.h"
#include "Dynamics/b2World.h"
#include "Dynamics/b2Body.h"
#include "Dynamics/Joints/b2Joint.h"
#include "Dynamics/Joints/b2RevoluteJoint.h"
#include "Dynamics/Joints/b2PulleyJoint.h"
#include "Dynamics/Joints/b2DistanceJoint.h"
#include "Dynamics/Joints/b2GearJoint.h"
#include "Dynamics/Joints/b2PrismaticJoint.h"
#include "Dynamics/Joints/b2MouseJoint.h"

void export_joints() {
  using namespace boost::python;

	class_< b2Joint, boost::noncopyable >("joint", no_init)
		.def("body1", &b2Joint::GetBody1, return_value_policy< reference_existing_object >())
		.def("body2", &b2Joint::GetBody2, return_value_policy< reference_existing_object >())
	  ;

	class_<b2JointDef>("joint_def")
		.def_readwrite("collide_connected", &b2JointDef::collideConnected)
		.def_readwrite("body1", &b2JointDef::body1)
		.def_readwrite("body2", &b2JointDef::body2)
	  ;

	class_< b2RevoluteJoint, bases< b2Joint > >("revolute_joint", init< b2RevoluteJointDef * >() )
        .add_property("motor_enabled",      &b2RevoluteJoint::IsMotorEnabled,   &b2RevoluteJoint::EnableMotor)
        .add_property("limit_enabled",      &b2RevoluteJoint::IsLimitEnabled,   &b2RevoluteJoint::EnableLimit)
        .add_property("motor_speed",        &b2RevoluteJoint::GetMotorSpeed,    &b2RevoluteJoint::SetMotorSpeed)
        .add_property("max_motor_torque",   &b2RevoluteJoint::SetMaxMotorTorque)
        .def(         "set_limits",         &b2RevoluteJoint::SetLimits)
	  ;

	class_< b2RevoluteJointDef, bases< b2JointDef > >("revolute_joint_def")
		.def_readwrite("max_motor_torque",  &b2RevoluteJointDef::maxMotorTorque, "Rrrrrmrmmmrrmm :)")
		.def_readwrite("enable_motor",      &b2RevoluteJointDef::enableMotor,    "A flag to enable the joint motor.")
		.def_readwrite("enable_limit",      &b2RevoluteJointDef::enableLimit,    "A flag to enable joint limits.")
		.def_readwrite("limit_lower",       &b2RevoluteJointDef::lowerAngle,     "The lower angle for the joint limit (radians).")
		.def_readwrite("limit_upper",       &b2RevoluteJointDef::upperAngle,     "The upper angle for the joint limit (radians).")
		.def_readwrite("local_anchor_1",    &b2RevoluteJointDef::localAnchor1,   "The local anchor point relative to body1's origin.")
		.def_readwrite("local_anchor_2",    &b2RevoluteJointDef::localAnchor2,   "The local anchor point relative to body2's origin.")
		.def_readwrite("motor_speed",       &b2RevoluteJointDef::motorSpeed,     "how fast can it spin")
		.def(          "init",              &b2RevoluteJointDef::Initialize,     "Initialize the bodies, anchors, and reference angle using the world anchor.")
	  ;

	class_< b2PulleyJointDef, bases< b2JointDef > >("pulley_joint_def")
		.def("init", &b2PulleyJointDef::Initialize)
	  ;

	class_< b2DistanceJointDef, bases< b2JointDef > >("distance_joint_def")
		.def_readwrite("length", &b2DistanceJointDef::length)
		.def_readwrite("damping_ratio", &b2DistanceJointDef::dampingRatio)
		.def("init", &b2DistanceJointDef::Initialize)
	  ;

	class_< b2GearJointDef, bases< b2JointDef > >("gear_joint_def")
		.def_readwrite("joint1", &b2GearJointDef::joint1)
		.def_readwrite("joint2", &b2GearJointDef::joint2)
		.def_readwrite("gear_ratio", &b2GearJointDef::ratio)
	  ;

	class_< b2PrismaticJoint, bases< b2Joint > >("prismatic_joint", no_init)
        .add_property("motor_enabled", &b2PrismaticJoint::IsMotorEnabled,   &b2PrismaticJoint::EnableMotor)
		.def("set_motor_speed",        &b2PrismaticJoint::SetMotorSpeed)
		.def("enable_motor",           &b2PrismaticJoint::EnableMotor)
		.def("set_max_motor_force",    &b2PrismaticJoint::SetMaxMotorForce)
		.def("set_limits",             &b2PrismaticJoint::SetLimits)
	  ;

	class_< b2PrismaticJointDef, bases< b2JointDef > >("prismatic_joint_def")
		.def_readwrite("local_anchor_1", &b2PrismaticJointDef::localAnchor1)
		.def_readwrite("local_anchor_2", &b2PrismaticJointDef::localAnchor2)
		.def_readwrite("reference_angle", &b2PrismaticJointDef::referenceAngle)
		.def_readwrite("lower_translation", &b2PrismaticJointDef::lowerTranslation)
		.def_readwrite("upper_translation", &b2PrismaticJointDef::upperTranslation)
		.def_readwrite("max_motor_force", &b2PrismaticJointDef::maxMotorForce)
		.def_readwrite("motor_speed", &b2PrismaticJointDef::motorSpeed)
		.def_readwrite("enable_motor", &b2PrismaticJointDef::enableMotor)
		.def_readwrite("enable_limit", &b2PrismaticJointDef::enableLimit)
		.def("init", &b2PrismaticJointDef::Initialize)
	  ;

    class_< b2MouseJointDef, bases< b2JointDef > >("mouse_joint_def")
        .def_readwrite("target",        &b2MouseJointDef::target,        "")
        .def_readwrite("max_force",     &b2MouseJointDef::maxForce,      "")
        .def_readwrite("frequency",     &b2MouseJointDef::frequencyHz,   "")
        .def_readwrite("damping_ratio", &b2MouseJointDef::dampingRatio,  "")
        .def_readwrite("time_step",     &b2MouseJointDef::timeStep,      "Why the fuck does this struct contain timeStep? It does, though.")
      ;

    class_< b2MouseJoint, bases< b2Joint > >("mouse_joint", no_init)
        .def("set_target", &b2MouseJoint::SetTarget)
      ;
}


