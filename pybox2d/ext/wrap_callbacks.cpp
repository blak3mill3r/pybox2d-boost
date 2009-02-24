#include <boost/python.hpp>
#include "Common/b2Math.h"
//#include "Collision/b2Collision.h"
//#include "Collision/Shapes/b2Shape.h"
//#include "Dynamics/b2World.h"
//#include "Dynamics/b2Body.h"
//#include "Dynamics/Contacts/b2Body.h"
#include "Dynamics/Contacts/b2Contact.h"
#include "Dynamics/b2WorldCallbacks.h"



// virtual void Add(const b2ContactPoint* point) { B2_NOT_USED(point); }
// http://www.boost.org/doc/libs/1_38_0/libs/python/doc/v2/wrapper.html
// http://www.boost.org/doc/libs/1_38_0/libs/python/doc/tutorial/doc/html/python/exposing.html#python.class_virtual_functions
// http://wiki.python.org/moin/boost.python/OverridableVirtualFunctions

/*
#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/wrapper.hpp>
#include <boost/python/call.hpp>

using namespace boost::python;

// Class with one pure virtual function
struct P
{
    virtual ~P(){}
    virtual char const* f() = 0;
    char const* g() { return "P::g()"; }
};

struct PCallback : P, wrapper<P>
{
    char const* f()
    {
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) // Workaround for vc6/vc7
        return call<char const*>(this->get_override("f").ptr());
#else
        return this->get_override("f")();
#endif
    }
};

// Class with one non-pure virtual function
struct A
{
    virtual ~A(){}
    virtual char const* f() { return "A::f()"; }
};

struct ACallback :  A, wrapper<A>
{
    char const* f()
    {
        if (override f = this->get_override("f"))
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) // Workaround for vc6/vc7
            return call<char const*>(f.ptr());
#else
            return f();
#endif

        return A::f();
    }

    char const* default_f() { return this->A::f(); }
};

BOOST_PYTHON_MODULE_INIT(polymorphism)
{
    class_<PCallback,boost::noncopyable>("P")
        .def("f", pure_virtual(&P::f))
        ;

    class_<ACallback,boost::noncopyable>("A")
        .def("f", &A::f, &ACallback::default_f)
        ;
}
*/

using namespace boost::python;

class DebugDrawWrapper: public b2DebugDraw, public wrapper<b2DebugDraw>
{
public:
    void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
    {
        list vertex_list = list();
    	for (int i=0; i < vertexCount; i++) {
    		vertex_list.append(vertices[i]);
        }
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) // Workaround for vc6/vc7
        call<char const*>(this->get_override("draw_polygon").ptr(vertex_list, &color));
#else
        this->get_override("draw_polygon")(vertex_list, &color);
#endif
    }

    void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
    {
        list vertex_list = list();
    	for (int i=0; i < vertexCount; i++) {
    		vertex_list.append(vertices[i]);
        }
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) // Workaround for vc6/vc7
        call<char const*>(this->get_override("draw_solid_polygon").ptr(vertex_list, &color));
#else
        this->get_override("draw_solid_polygon")(vertex_list, &color);
#endif
    }

    void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
    {
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) // Workaround for vc6/vc7
        call<char const*>(this->get_override("draw_circle").ptr(&center, radius, &color));
#else
        this->get_override("draw_circle")(&center, radius, &color);
#endif
    }

    void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
    {
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) // Workaround for vc6/vc7
        call<char const*>(this->get_override("draw_solid_circle").ptr(&center, radius, &axis, &color));
#else
        this->get_override("draw_solid_circle")(&center, radius, &color);
#endif
    }

    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
    {
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) // Workaround for vc6/vc7
        call<char const*>(this->get_override("draw_segment").ptr(&p1, &p2, &color));
#else
        this->get_override("draw_segment")(&p1, &p2, &color);
#endif
    }

    void DrawXForm(const b2XForm& xf)
    {
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) // Workaround for vc6/vc7
        call<char const*>(this->get_override("draw_xform").ptr(&xf));
#else
        this->get_override("draw_xform")(&xf);
#endif
    }

};

/*
 * We must wrap the Contact Listener in order to redefine its callback methods
 * in Python.
 */
class ContactListenerWrapper : public b2ContactListener, public wrapper<b2ContactListener>
{
public:
	// A new contact point is added
	void Add(const b2ContactPoint* point)
	{
        if (override f = this->get_override("add")) {
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) // Workaround for vc6/vc7
            call<void>(f.ptr(point));
#else
            f(point);
#endif
        } else {
        	b2ContactListener::Add(point);
        }
	}

	void default_Add(const b2ContactPoint* p) { this->b2ContactListener::Add(p); }

	// A contact point persists in the next frame
	void Persist(const b2ContactPoint* point)
	{
        if (override f = this->get_override("persist")) {
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) // Workaround for vc6/vc7
            call<void>(f.ptr(point));
#else
            f(point);
#endif
        } else {
        	b2ContactListener::Persist(point);
        }
	}

	void default_Persist(const b2ContactPoint* p) { this->b2ContactListener::Persist(p); }

	// A contact point is not existing any more
	void Remove(const b2ContactPoint* point)
	{
        if (override f = this->get_override("remove")) {
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) // Workaround for vc6/vc7
            call<void>(f.ptr(point));
#else
            f(point);
#endif
        } else {
        	b2ContactListener::Remove(point);
        }
	}

	void default_Remove(const b2ContactPoint* p) { this->b2ContactListener::Remove(p); }

	// A contact point is not existing any more
	void Result(const b2ContactResult* res)
	{
        if (override f = this->get_override("result")) {
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) // Workaround for vc6/vc7
            call<void>(f.ptr(res));
#else
            f(res);
#endif
        } else {
        	b2ContactListener::Result(res);
        }
	}

	void default_Result(const b2ContactResult* res) { this->b2ContactListener::Result(res); }

};

enum drawoptions
{
	e_shapeBit				= 0x0001, ///< draw shapes
	e_jointBit				= 0x0002, ///< draw joint connections
	e_coreShapeBit			= 0x0004, ///< draw core (TOI) shapes
	e_aabbBit				= 0x0008, ///< draw axis aligned bounding boxes
	e_obbBit				= 0x0010, ///< draw oriented bounding boxes
	e_pairBit				= 0x0020, ///< draw broad-phase pairs
	e_centerOfMassBit		= 0x0040, ///< draw center of mass frame
	e_controllerBit			= 0x0080, ///< draw controllers
};

void export_callbacks() {
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

	enum_<drawoptions>("DebugDrawOptions")
		.value("shapes",                   e_shapeBit)
		.value("joints",                   e_jointBit)
		.value("toi_shapes",               e_coreShapeBit)
		.value("aabb",                     e_aabbBit)
		.value("obb",                      e_obbBit)
		.value("broad_phase_pairs",        e_pairBit)
		.value("center_of_mass",           e_centerOfMassBit)
		.value("controllers",              e_controllerBit)
	  ;

	class_< b2Color >("DebugDrawColor")
		.def_readwrite("r",                &b2Color::r)
		.def_readwrite("g",                &b2Color::g)
		.def_readwrite("b",                &b2Color::b)
	  ;

	class_< DebugDrawWrapper,boost::noncopyable >("DebugDraw")
		.add_property("flags",             &b2DebugDraw::GetFlags, &b2DebugDraw::SetFlags)
		.def("draw_polygon",               pure_virtual(&b2DebugDraw::DrawPolygon))
		.def("draw_solid_polygon",         pure_virtual(&b2DebugDraw::DrawSolidPolygon))
		.def("draw_circle",                pure_virtual(&b2DebugDraw::DrawCircle))
		.def("draw_solid_circle",          pure_virtual(&b2DebugDraw::DrawSolidCircle))
		.def("draw_segment",               pure_virtual(&b2DebugDraw::DrawSegment))
		.def("draw_xform",                 pure_virtual(&b2DebugDraw::DrawXForm))
	  ;

	class_< ContactListenerWrapper,boost::noncopyable >("ContactListener")
		.def("add",                        &b2ContactListener::Add, &ContactListenerWrapper::default_Add)
		.def("persist",                    &b2ContactListener::Persist, &ContactListenerWrapper::default_Persist)
		.def("remove",                     &b2ContactListener::Remove, &ContactListenerWrapper::default_Remove)
		.def("result",                     &b2ContactListener::Result, &ContactListenerWrapper::default_Result)
	  ;

}
