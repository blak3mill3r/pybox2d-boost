from pybox2d_ext import *

def fuckshit(self, name, bases, dict):
    for b in bases:
        if type(b) not in (self, type):
            for k,v in dict.items():
                setattr(b,k,v)
    return type.__init__(self, name, bases, dict)

class world_injector(object):
    class __metaclass__(world.__class__):
        __init__ = fuckshit

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

class MyDebugDraw(DebugDraw):
    def draw_solid_polygon(self, *args):
        print args
    
    def draw_solid_circle(self, *args):
        print args

class MyContactListener(ContactListener):
    def result(self, *args):
        print 'Result', args
    
    def add(self, *args):
        print 'Add', args
        print dir(args[0]), args[0].normal
    
    def persist(self, *args):
        print 'Persist', args
    
    def remove(self, *args):
        print 'Remove', args

def world_init(l, b, r, t, gravity=vec2(0,-10)):
    world_aabb = aabb()
    world_aabb.lower_bound = vec2(l, b)
    world_aabb.upper_bound = vec2(r, t)
    return world(world_aabb, gravity, 1)

dbd = MyDebugDraw()
dbd.flags = DebugDrawOptions.shapes
conlis = MyContactListener()
w = world_init( -100, -100, 100, 100 )
w.set_debug_draw(dbd)
#w.set_contact_listener(conlis)

# floor & ceiling
p, c = ( polygon_def(), circle_def() )
p.set_as_box(60, 1)

floor = w.new_body(vec2(0, -30), p)
#ceiling = w.new_body( vec2(0, 30), p )

p.set_as_box(20, 20)
p.density = 1.0
box1 = w.new_body(vec2(0, -20), p)
box1.set_mass_from_shapes()
box2 = w.new_body(vec2(0,  50), p)
box2.set_mass_from_shapes()
print box2.first_shape()

for i in xrange(300):
    w.step(1./60, 10, 8)
    print box1.position.x, box1.position.y
    print box2.position.x, box2.position.y

# walls
p.set_as_box(1, 60)

w.new_body( vec2(-30, 0), p )
w.new_body( vec2( 30, 0), p )