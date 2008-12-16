"""\
PyBox2D - A Boost.Python wrapper around Box2D

Might be useful for 2D physics in games or such.
"""

# import the raw extension ... the wrapped C++
from pybox2d_ext import *

# extend it with python
def fuckshit(self, name, bases, dict):
    for b in bases:
        if type(b) not in (self, type):
            for k,v in dict.items():
                setattr(b,k,v)
    return type.__init__(self, name, bases, dict)

class polygon_def_injector(object):
    class __metaclass__(polygon_def.__class__):
        __init__ = fuckshit

class body_injector(object):
    class __metaclass__(body.__class__):
        __init__ = fuckshit

class world_injector(object):
    class __metaclass__(world.__class__):
        __init__ = fuckshit

class vec2_injector(object):
    class __metaclass__(vec2.__class__):
        __init__ = fuckshit

class extend_body(body_injector, body):
    def __repr__(self):
        return "Body with mass %6.1f" % self.get_mass()

class extend_world(world_injector, world):
    def __repr__(self):
        return 'World'
    def new_body(self, position, shape_or_shapes, angle=0):
        bd = body_def()
        bd.position = position
        bd.angle = angle
        b = self.create_body(bd)
        if shape_or_shapes.__class__ == list:
            for s in shape_or_shapes:
                b.create_shape(s)
        else:
            b.create_shape(shape_or_shapes)
        return b

class extend_polygon_def(polygon_def_injector, polygon_def):
    def set_vertices(self, vlist):
        i=0
        for v in vlist:
            self.set_vertex(i, vec2( v[0], v[1] ))
            i += 1
        self.vertex_count = i
    def __repr__(self):
        return 'Polygon shape'

class extend_vec2(vec2_injector, vec2):
    def __repr__(self):
        return "vec2(%6.4f, %6.4f)" % (self.x, self.y)
