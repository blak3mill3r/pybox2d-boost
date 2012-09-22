#include <boost/python.hpp>
#include "Common/b2Math.h"
#include "Collision/b2Collision.h"
#include "Dynamics/b2World.h"
#include "Dynamics/b2Body.h"
#include "Collision/Shapes/b2PolygonShape.h"
#include "Collision/Shapes/b2CircleShape.h"
#include "Collision/Shapes/b2Shape.h"

const b2Vec2& get_vertex( const b2PolygonShape& pd, int i ) { return pd.GetVertices()[i]; }

void set_vertex( b2PolygonDef& pd, int i, const b2Vec2& v ) { pd.vertices[i] = v; }

void export_shapes() {
  using namespace boost::python;

	// b2Shape.h
	class_<b2ShapeDef>("shape_def")
		.def_readwrite("density",     &b2ShapeDef::density)
		.def_readwrite("friction",    &b2ShapeDef::friction)
		.def_readwrite("restitution", &b2ShapeDef::restitution)
		.def_readwrite("is_sensor",   &b2ShapeDef::isSensor)
		.def_readwrite("filter_data", &b2ShapeDef::filter)
		;

	class_<b2FilterData>("filter_data")
		.def_readwrite("category_bits",  &b2FilterData::categoryBits)
		.def_readwrite("mask_bits",      &b2FilterData::maskBits)
		.def_readwrite("group_index",    &b2FilterData::groupIndex)
		;

	class_<b2Shape, boost::noncopyable>("shape", no_init)
		.def("next", &b2Shape::GetNext, return_value_policy< reference_existing_object >())
		.def("body", &b2Shape::GetBody, return_value_policy< reference_existing_object >())
		.def("set_filter_data", &b2Shape::SetFilterData, return_value_policy< reference_existing_object >())
	  ;

	// b2CircleShape.h
	class_< b2CircleDef, bases< b2ShapeDef > >("circle_def")
		.def_readwrite("radius", &b2CircleDef::radius)
		.def_readwrite("local_position", &b2CircleDef::localPosition)
		;
		
	class_< b2CircleShape, bases< b2Shape > >("circle_shape", no_init)
		.def("radius", &b2CircleShape::GetRadius )
		.def("local_position", &b2CircleShape::GetLocalPosition, return_value_policy< copy_const_reference >() )
		;

	// b2PolygonShape.h
  typedef void (b2PolygonDef::*grrr)(float32, float32);
	class_<b2PolygonDef, bases<b2ShapeDef> >("polygon_def")
		.def_readwrite( "vertex_count", &b2PolygonDef::vertexCount)
		.def( "set_vertex", set_vertex )
		.def( "set_as_box", (grrr)(&b2PolygonDef::SetAsBox) )
		;
	
	class_<b2PolygonShape, bases< b2Shape > >("polygon_shape", no_init)
		.def_readonly( "vertex_count", &b2PolygonShape::GetVertexCount )
		.def( "get_vertex", get_vertex, return_value_policy< copy_const_reference >() )
		;
}

