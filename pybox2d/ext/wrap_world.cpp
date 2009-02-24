#include <boost/python.hpp>
#include "Common/b2Math.h"
#include "Collision/b2Collision.h"
#include "Dynamics/b2World.h"
#include "Dynamics/b2Body.h"

using namespace boost::python;

list worldQueryWrap(b2World *world, const b2AABB& aabb, int32 maxCount) {

    // allocate space for the b2Shape pointers
    b2Shape** shapes = new b2Shape*[maxCount];

    // call world->Query()
    int32 count = world->Query(aabb, shapes, maxCount);

    // return results as a python list
    list l = list();

    for( int32 i = 0; i < count; ++i ) {
        reference_existing_object::apply<b2Shape*>::type converter;
        PyObject* obj = converter( shapes[i] );
        l.append( object( handle<>( obj ) ) );
    }

    delete [] shapes;
    return l;
}

void export_world() {
  using namespace boost::python;

    // b2World.h
    class_<b2World>("world", init<b2AABB, b2Vec2, bool>())
        .def("create_body",                &b2World::CreateBody, return_value_policy< reference_existing_object >())
        .def("destroy_body",               &b2World::DestroyBody)
        .def("create_joint",               &b2World::CreateJoint, return_value_policy< reference_existing_object >())
        .def("destroy_joint",              &b2World::DestroyJoint)
        .def("step",                       &b2World::Step)
        .def("first_body",                 &b2World::GetBodyList, return_value_policy< reference_existing_object >())
        .def("set_contact_listener",       &b2World::SetContactListener)
        .def("set_debug_draw",             &b2World::SetDebugDraw)
        .def("query",                      &worldQueryWrap)
      ;
}
