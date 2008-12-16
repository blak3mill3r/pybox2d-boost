#include <boost/python.hpp>
#include "Common/b2Math.h"
#include "Collision/b2Collision.h"
#include "Dynamics/b2World.h"
#include "Dynamics/b2Body.h"

void b2Mul_wrap(b2Vec2& v, const b2XForm& xf) {
	v = b2Mul(xf, v);
}

void export_math() {
  using namespace boost::python;
	class_<b2Vec2>("vec2", init<float32, float32>())
		.def("zero", &b2Vec2::SetZero)
		.def_readwrite("x", &b2Vec2::x)
		.def_readwrite("y", &b2Vec2::y)
		.def("length", &b2Vec2::Length)
		.def("length_sq", &b2Vec2::LengthSquared)
		.def("normalize", &b2Vec2::Normalize)
		.def("multiply", b2Mul_wrap)
		.def(self + self)
		.def(self - self)
		.def(self += self)
		.def(self -= self)
		.def(self *= float32())
		.def(-self)
		;

	class_<b2Mat22>("mat22", init<b2Vec2, b2Vec2>())
		.def(init<float32,float32,float32,float32>())
		.def(init<float32>())
		.def_readwrite("col1", &b2Mat22::col1)
		.def_readwrite("col2", &b2Mat22::col2)
		.def("zero", &b2Mat22::SetZero)
		;

	class_<b2XForm>("xform", init<b2Vec2, b2Mat22>())
		.def("identity", &b2XForm::SetIdentity)
		.def_readwrite("position", &b2XForm::position)
		.def_readwrite("rotation", &b2XForm::R)
		;

}
