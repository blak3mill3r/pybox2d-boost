#!/usr/bin/env python2.6

import pygame
import math
import numpy
from random import randint
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *
from pybox2d import *

SCREEN_W = 1280.0
SCREEN_H = 1024.0
#SCREEN_W = 640.0
#SCREEN_H = 480.0

the_mouse_joint = None

def world_init(l, b, r, t, gravity=vec2(0,-10)):
    world_aabb = aabb()
    world_aabb.lower_bound = vec2(l, b)
    world_aabb.upper_bound = vec2(r, t)
    return world(world_aabb, gravity, 1)

w = world_init( -100, -100, 100, 100 )

p, c = ( polygon_def(), circle_def() )

# floor & ceiling
p.set_as_box(60, 1)

floor = w.new_body( vec2(0, -30), p )
w.new_body( vec2(0, 30), p )

# walls
p.set_as_box(1, 60)

w.new_body( vec2(-30, 0), p )
w.new_body( vec2( 30, 0), p )

## prismatic
#p.set_as_box(5,0.5)
#p.density = 2
#
#elevator = w.new_body(vec2(10,0), p)
#elevator.set_mass_from_shapes()
#
#pjd = prismatic_joint_def()
#pjd.init( floor, elevator, vec2(10, 0), vec2(0, 1) )
#pjd.lower = 0
#pjd.upper = 2
#pjd.max_motor_force = 30000
#pjd.motor_speed = 100
#pjd.enable_motor = 1
#pjd.enable_limit = 1
#
#elevator_joint = w.create_joint(pjd)
#elevator_joint.set_motor_speed( 10 )
#elevator_joint.set_max_motor_force( 30000 )
#elevator_joint.set_limits(0, 2)
#elevator_joint.enable_motor(1)
#
# spinning thingy
c.radius = 1.25
c.density = 1
c.restitution = 0.9

p.set_as_box( 8, 0.5 )
p.density=10
p.restitution=0.9

spinbody = w.new_body(vec2(-10, 0), [c,p])
spinbody.set_mass_from_shapes()

spinjdef = revolute_joint_def()
spinjdef.init( floor, spinbody, vec2(-10, 0) )
spinjdef.max_motor_torque = 300000
spinjdef.enable_motor = 1
spinjdef.motor_speed = 3

spinj = w.create_joint(spinjdef)
spinj.motor_enabled = False

# pulleys
#a = 2
#b = 4
#y = 16
#l = 12
#
#sd = polygon_def()
#sd.set_as_box(a,b)
#sd.density = 5.0
#
#bd = body_def()
#bd.position = vec2( -10, y )
#b1 = w.create_body(bd)
#b1.create_shape(sd)
#b1.set_mass_from_shapes()
#
#bd.position = vec2( 10, y )
#b2 = w.create_body(bd)
#b2.create_shape(sd)
#b2.set_mass_from_shapes()
#
#pjd = pulley_joint_def()
#pjd.init( b1, b2, vec2( -10, y+b+l ), vec2( 10, y+b+l ), vec2(-10, y+b), vec2(10, y+b), 2)
#pj = w.create_joint(pjd)

# chain
sd = polygon_def()
sd.set_as_box(0.6, 0.125)
sd.density = 1000
sd.friction = 0.2

jd = revolute_joint_def()
jd.collide_connected = 0
y = 3
prevbody = floor
num_links = 15

for i in range(0, num_links):
  bd = body_def()
  bd.position = vec2( 0.5 + i, y )
  body = w.create_body(bd)
  body.create_shape(sd)
  body.set_mass_from_shapes()
  anchor = vec2( i, y )
  jd.init(prevbody, body, anchor)
  w.create_joint(jd)
  prevbody = body

# ball
dsd = circle_def()
dsd.radius = 1
dsd.density = 1000
dsd.restitution = 0.1

dbd = body_def()
dbd.position = vec2( 0.5 + dsd.radius + num_links, y )

db = w.create_body(dbd)

db.create_shape(dsd)

db.set_mass_from_shapes()

jd.init(prevbody, db, vec2(num_links, y))
w.create_joint(jd)

#for i in range(0,3):
#    sa = polygon_def()
#    sb = polygon_def()
#
#    sa.set_vertices( [
#                                            ( 0,  0),
#                                            ( randint(2, 9),  2),
#                                            (-2,  2)            ] )
#    sb.set_vertices( [
#                                            (-2,  0),
#                                            ( 0,  2),
#                                            (-4,  2)            ] )
#    
#    sa.density=9
#    sa.restitution = 0.9
#    
#    sb.density=9
#    sb.restitution = 0.9
#    
#    w.new_body(vec2(i * 10, 5), [sa, sb]).set_mass_from_shapes()

#for i in range(0,3):
#  dbd = body_def()
#  dbd.position = vec2(i * 10, 5)
#  
#  db = w.create_body(dbd)
#  
#  dsd = polygon_def()
#  dsd.set_as_box(randint(1,5), randint(1,5))
#  dsd.density = randint(1,5)
#  dsd.restitution = randint(1,3)*0.125
#  
#  db.create_shape(dsd)
#  
#  db.set_mass_from_shapes()

for i in range(0,3):
  dbd = body_def()
  dbd.position = vec2(randint(-20, 20), randint(-20,20))
  
  db = w.create_body(dbd)
  
  dsd = circle_def()
  dsd.radius = randint(1,3)
  dsd.density = randint(1,9)
  dsd.restitution = randint(1,7)*0.125
  
  db.create_shape(dsd)
  
  db.set_mass_from_shapes()

timestep = 1.0 / 90.0
iterations = 10

def drawvertex(v, m):
  vert = vec2(v.x, v.y)
  vert.multiply(m)
  glVertex3f( vert.x, vert.y, 0 )

def drawpoly(shape, xf):
  numverts = shape.vertex_count
  glBegin(GL_LINE_LOOP)
  glColor3fv( (1,1,1) )
  for i in range(0,numverts):
    drawvertex(shape.get_vertex(i), xf)
  glEnd()

def drawcircle(shape, xf):
  center = shape.local_position()
  center.x = center.x + xf.position.x
  center.y = center.y + xf.position.y
  radius = shape.radius()
  segments = 16
  increment = 2.0 * 3.14159 / segments
  theta = 0
  glBegin(GL_LINE_LOOP)
  for i in range(0,segments):
        v = vec2(center.x + radius*math.cos(theta), center.y + radius*math.sin(theta))
        glVertex3f( v.x, v.y, 0 )
        theta += increment
  glEnd()

def drawshape(shape, body):
  if shape.__class__ == polygon_shape:
    drawpoly(shape, body.get_xform())
  if shape.__class__ == circle_shape:
    drawcircle(shape, body.get_xform())

def drawbody(body):
  current = body.first_shape()
  xf = body.get_xform()
  while current:
        drawshape(current, body)
        current = current.next()

def drawall():
    current = w.first_body()
    while current:
        drawbody( current )
        current = current.next()

# FIXME this is inefficient getting the matrices every time
def screen_to_world(v):
    """Convert screen coordinates to world coordinates"""
    model_matrix = glGetDoublev(GL_MODELVIEW_MATRIX)
    projection_matrix = glGetDoublev(GL_PROJECTION_MATRIX)
    viewport = glGetIntegerv(GL_VIEWPORT)
    tup = gluUnProject(v[0], SCREEN_H-v[1], 0, model_matrix, projection_matrix, viewport)
    return vec2(tup[0], tup[1])

def lmb_up(v):
    #print "UP"
    global the_mouse_joint
    if the_mouse_joint is not None:
        w.destroy_joint(the_mouse_joint)
    the_mouse_joint = None

def lmb_down(v):
    #print "DOWN"
    global the_mouse_joint
    if the_mouse_joint is not None:
        return
    v = screen_to_world(v)              # v = where in the world is the mouse pointer?
    d = vec2(0.001, 0.001)              # make a very small aabb centered at the mouse pointer
    tiny = aabb()
    tiny.lower_bound = v - d
    tiny.upper_bound = v + d

    # query world for shapes which intersect with that tiny aabb (maximum of 10 shapes)
    shapes = w.query( tiny, 10 )
    grabbed_body = None
    for shape in shapes:
        shape_body = shape.body()
        if ((shape_body.is_static() == False) and (shape_body.get_mass() > 0.0)):
            grabbed_body = shape_body               # find the first shape whose body is dynamic
            break

    if grabbed_body:
        mjd = mouse_joint_def()
        mjd.body1 = floor
        mjd.body2 = grabbed_body
        mjd.target = v
        mjd.max_force = 100000.0 * grabbed_body.get_mass()
        the_mouse_joint = w.create_joint(mjd)
        grabbed_body.wake_up()

def lmb_drag(v):
    global the_mouse_joint
    """Handles left mouse button draggage."""
    v = screen_to_world(v)              # v = where in the world is the mouse pointer?
    if the_mouse_joint is not None:
        the_mouse_joint.set_target(v)
        
def main():
        "run the demo"
        #initialize pygame and setup an opengl display
        pygame.init()
        pygame.display.set_mode((SCREEN_W,SCREEN_H), OPENGL|DOUBLEBUF|FULLSCREEN)

        mouse_lb = False

        #setup the camera
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        #ar = 1280.0/1024.0
        ar = SCREEN_W/SCREEN_H
        gluOrtho2D(-30*ar, 30*ar, -30, 30)

        pygame.fastevent.init()

        while 1:
                #check for quit'n events
                #event = pygame.event.poll()
                #event = pygame.fastevent.poll()
                event_list = []
                event_list = pygame.fastevent.get()

                for event in event_list:
                    if event.type == QUIT or (event.type == KEYDOWN and event.key == K_ESCAPE):
                        print "Done"
                        return

                    if event.type == MOUSEMOTION:
                        if mouse_lb == True:
                            lmb_drag(pygame.mouse.get_pos())

                    if event.type == MOUSEBUTTONUP:
                        mouse_lb = False
                        lmb_up(pygame.mouse.get_pos())

                    if event.type == MOUSEBUTTONDOWN:
                        mouse_lb = True
                        lmb_down(pygame.mouse.get_pos())

                    if event.type == KEYDOWN:
                        if event.key == K_KP_PLUS:
                            spinj.motor_enabled = (not spinj.motor_enabled)
                            #elevator_joint.motor_enabled = (not elevator_joint.motor_enabled)
                            #elevator.wake_up()
                            spinbody.wake_up()

                glClear(GL_COLOR_BUFFER_BIT)

                w.step(timestep, iterations)
                drawall()

                pygame.display.flip()
                #pygame.time.Clock()
                
                pygame.time.wait(10)

if __name__ == '__main__': main()
