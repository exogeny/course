/*
-----------------------------------------------------------------------
This source file is part of "cgcourse-examples"
(Examples for Computer Graphics Course of CCCE GUCAS.)
Copyright (C) 2011 Xue Jian (jian.xue.cn@gmail.com)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------
*/

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <time.h>

#include "glinc.h"
#include "trackball.h"
#include "quaternion.h"
#include "camera.h"
#include "cpucounter.h"

using namespace std;

typedef double value_type;
typedef Vector<value_type> vector_type;
typedef Matrix<value_type> matrix_type;

value_type const EPS = (value_type)0.000001;
value_type const ZERO = (value_type)0.0000000001;
value_type const DENSITY = (value_type)500.0;
value_type const MASS_MIN = (value_type)1.0;
value_type const MASS_MAX = (value_type)10.0;
value_type const RADIUS_MIN = (value_type)0.2;
value_type const RADIUS_MAX = (value_type)0.25;
value_type const GRID_SIZE = RADIUS_MAX * (value_type)2.0;
value_type const WALL_SIZE = (value_type)4.0;
unsigned int const GRID_NUM_AXIS = (unsigned int)(WALL_SIZE*2/GRID_SIZE) + 1;
unsigned int const SHOW_TIMES = 80;


float g_light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
float g_light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
float g_light_position[] = { -10.0f, 10.0f, 10.0f, 1.0f };
float g_light_direction[] = { 1.0f, -1.0f, -1.0f, 0.0f };

float g_material_ambient[]  = { 1.0f, 0.57f, 0.04f, 1.0f };
float g_material_diffuse[]  = { 1.0f, 0.57f, 0.04f, 1.0f };
float g_material_specular[]  = { 0.33f, 0.33f, 0.52f, 1.0f };
float g_material_emission[]  = { 0.0f, 0.0f, 0.0f, 0.0f };
float g_material_specular_power = 80.0f;

value_type g_cube_v[][3] = {
    {-WALL_SIZE, -WALL_SIZE,  WALL_SIZE},
    { WALL_SIZE, -WALL_SIZE,  WALL_SIZE},
    { WALL_SIZE,  WALL_SIZE,  WALL_SIZE},
    {-WALL_SIZE,  WALL_SIZE,  WALL_SIZE},
    {-WALL_SIZE, -WALL_SIZE, -WALL_SIZE},
    {-WALL_SIZE,  WALL_SIZE, -WALL_SIZE},
    { WALL_SIZE,  WALL_SIZE, -WALL_SIZE},
    { WALL_SIZE, -WALL_SIZE, -WALL_SIZE}
};
unsigned int g_cube_f[][5] = {
    { 0, 1, 2, 3, 0 }, // front face
    { 4, 5, 6, 7, 0 }, // back face
    { 4, 0, 3, 5, 0 }, // left face
    { 7, 6, 2, 1, 0 }, // right face
    { 5, 3, 2, 6, 0 }, // top face
    { 4, 7, 1, 0, 0 }  // bottom face
};
float g_cube_fn[][3] = {
    { 0.0f, 0.0f, 1.0f }, // front face
    { 0.0f, 0.0f,-1.0f }, // back face
    {-1.0f, 0.0f, 0.0f }, // left face
    { 1.0f, 0.0f, 0.0f }, // right face
    { 0.0f, 1.0f, 0.0f }, // top face
    { 0.0f,-1.0f, 0.0f }  // bottom face
};
unsigned int g_cube_e[] = { 0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6, 6, 7, 7, 4, 0, 4, 1, 7, 2, 6, 3, 5 };

unsigned int const FACE_FRONT = 0;
unsigned int const FACE_BACK = 1;
unsigned int const FACE_LEFT = 2;
unsigned int const FACE_RIGHT = 3;
unsigned int const FACE_TOP = 4;
unsigned int const FACE_BOTTOM = 5;

bool g_left_button_down = false;
bool g_middle_button_down = false;
bool g_right_button_down = false;

bool g_pause = false;

GLint g_viewport[4];
TrackBall<value_type> g_trackball;
matrix_type g_rotm;
Camera<value_type> g_cam;
value_type g_fov = (value_type)45;

CPUCounter g_timer;
double g_elapsed_seconds;

value_type g_dt = (value_type)0.2;
value_type g_recover_f = (value_type)0.5;
value_type g_kf = (value_type)0.75;
vector_type g_force(0.0, 0.0, 0.0, 0.0);
vector_type const GRAVITATION(0.0, -0.49, 0.0, 0.0);
vector_type g_spos(0.0, 1.0, 0.0, 1.0);
vector_type g_svel(1.0, 0.0, 1.5, 0.0);

inline void glMultMatrix(Matrix<float> const &mat) { glMultMatrixf(mat); }
inline void glMultMatrix(Matrix<double> const &mat) { glMultMatrixd(mat); }
inline void glVertex3v(float const *v) { glVertex3fv(v); }
inline void glVertex3v(double const *v) { glVertex3dv(v); }

inline void set_material()
{
    GLenum face = GL_FRONT_AND_BACK;
    //glMaterialfv(face, GL_AMBIENT, g_material_ambient);
    glMaterialfv(face, GL_AMBIENT, g_material_diffuse);
    glMaterialfv(face, GL_DIFFUSE, g_material_diffuse);
    glMaterialfv(face, GL_SPECULAR, g_material_specular);
    glMaterialfv(face, GL_EMISSION, g_material_emission);
    glMaterialf(face, GL_SHININESS, g_material_specular_power);
}

inline void set_color(float c[4])
{
    g_material_diffuse[0] = c[0];
    g_material_diffuse[1] = c[1];
    g_material_diffuse[2] = c[2];
    g_material_diffuse[3] = c[3];
    set_material();
}

class Particle
{
public:
    value_type mass;
    vector_type force;
    vector_type position;
    vector_type velocity;

    Particle(value_type m) : mass(m) { }

    void init() { force.ele[0] = force.ele[1] = force.ele[2] = force.ele[3] = 0; }

    void apply_force(vector_type const &f) { force += f; }

    void update_velocity(value_type dt) {
        velocity += force * (dt / mass);
    }

    virtual void update_position(value_type dt) {
        position += velocity * dt;
    }

    void render() {
        glPushMatrix();
        glTranslated(position.ele[0], position.ele[1], position.ele[2]);
        draw_something();
        glPopMatrix();
    }

protected:
    virtual void draw_something() = 0;
};

class Ball : public Particle
{
public:
    value_type radius;
    float color[4];

    Ball(value_type m, value_type r) : Particle(m), radius(r) { }

    virtual void update_position(value_type dt) {
        Particle::update_position(dt);
    }

protected:
    virtual void draw_something() {
        set_color(color);
        glutSolidSphere(radius, 50, 50);
    }
};

typedef vector<Ball> BallArray;
BallArray g_balls;

vector< vector< vector< vector<size_t> > > > g_grids;

void init_grids()
{
    g_grids.resize(GRID_NUM_AXIS);
    for (size_t x=0; x<GRID_NUM_AXIS; ++x) {
        g_grids[x].resize(GRID_NUM_AXIS);
        for (size_t y=0; y<GRID_NUM_AXIS; ++y) {
            g_grids[x][y].resize(GRID_NUM_AXIS);
        }
    }
}

void init_balls()
{
    srand((unsigned int)(time(0)));
    value_type space = 0.25;
    value_type bias = 0.01;
    unsigned int num = (unsigned int)(WALL_SIZE / (RADIUS_MAX+space));
    for (unsigned int i=0; i<num; ++i) {
        for (unsigned int j=0; j<num; ++j) {
            for (unsigned int k=0; k<num/2; ++k) {
                //value_type mi = static_cast<value_type>(MASS_MIN + (MASS_MAX-MASS_MIN) * (rand() % 999 + 1) / 1000.0);
                value_type ri = static_cast<value_type>(RADIUS_MIN + (RADIUS_MAX-RADIUS_MIN) * (rand() % 1000) / 1000.0);
                value_type mi = DENSITY * ri * ri * ri;
                Ball bi(mi, ri);
                bi.position.ele[0] = static_cast<value_type>(-WALL_SIZE+(2*i+1)*(RADIUS_MAX+space)+bias*(rand() % 1000) / 1000.0);
                bi.position.ele[1] = static_cast<value_type>(WALL_SIZE-(2*k+1)*(RADIUS_MAX+space));
                bi.position.ele[2] = static_cast<value_type>(-WALL_SIZE+(2*j+1)*(RADIUS_MAX+space)+bias*(rand() % 1000) / 1000.0);

                bi.color[0] = (float)((rand() % 256) / 256.0);
                bi.color[1] = (float)((rand() % 256) / 256.0);
                bi.color[2] = (float)((rand() % 256) / 256.0);
                bi.color[3] = 1.0f;

                g_balls.push_back(bi);
            }
        }
    }
}

bool init()
{
    glEnable(GL_NORMALIZE);
    //glEnable(GL_AUTO_NORMAL);
    //glEnable(GL_TEXTURE_2D);                          // Enable Texture Mapping
    glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);               // Black Background
    glClearDepth(1.0f);                                 // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                             // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Really Nice Perspective Calculations

    glLightfv(GL_LIGHT0, GL_AMBIENT, g_light_ambient);      // Setup The Ambient Light
    glLightfv(GL_LIGHT0, GL_DIFFUSE, g_light_diffuse);      // Setup The Diffuse Light
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.0f);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60.0f);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_LIGHT0);                                // Enable Light One

    g_rotm.IdentityMatrix();

    init_grids();
    init_balls();

    printf("grids: %d x %d x %d\n", GRID_NUM_AXIS, GRID_NUM_AXIS, GRID_NUM_AXIS);
    printf("particle number: %d\n", g_balls.size());

    g_elapsed_seconds = 0;
    g_timer.CounterStart();

    return true;
}

void update_timer()
{
    g_elapsed_seconds = g_timer.GetCounts() / g_timer.GetFrequence();
    g_timer.CounterStart();
}

/*
* version (1): based on accurate displacement computing
*/

bool ball_collision(value_type &dt, size_t &bi, size_t &bj)
{
    if (g_balls.size()<=0) return false;

    dt = g_dt + 1;
    value_type step = g_dt / (value_type)10.0;

    for (size_t i=0; i<g_balls.size()-1; ++i) {
        Ball &parti = g_balls[i];

        for (size_t j=i+1; j<g_balls.size(); ++j) {
            Ball &partj = g_balls[j];

            vector_type rv = parti.velocity - partj.velocity;
            vector_type rp = partj.position - parti.position;
            value_type vmag = rv.Length();

            if (vmag <= ZERO) continue;

            rv.Normalize();
            value_type dot = rp * rv;
            if (dot < 0) continue;

            value_type vlen = (rp-rv*dot).Length();
            value_type blen = parti.radius+partj.radius;
            if (vlen >= blen) continue;

            value_type curtime = 0;
            while (curtime < g_dt) {
                curtime += step;
                vector_type curpos = rv * curtime;
                if ((curpos-rp).Length()<=blen) {
                    if (dt>curtime-step) dt=curtime-step;
                    bi = i;
                    bj = j;
                    break;
                }
            }


        }
    }

    if (dt <= g_dt) return true;
    else return false;
}

void update_position()
{
    value_type resttime = g_dt;

    while (resttime > 0) {

        size_t bi;
        value_type lamda = g_dt + 1, rt = g_dt + 2;
        int vi=-1, fi=-1;
        for (size_t i=0; i<g_balls.size(); ++i) {

            Ball &parti = g_balls[i];
            if (parti.velocity.Length()<EPS) continue;
            vector_type newpos = parti.position + parti.velocity * resttime;

            if (fabs(newpos.ele[0]) > WALL_SIZE-parti.radius) {
                rt = (WALL_SIZE - fabs(parti.position.ele[0]) - parti.radius) / fabs(parti.velocity.ele[0]);
                if (rt<lamda) {
                    if (rt<0) {
                        parti.update_position(rt);
                        rt=-rt;
                    }
                    lamda = rt;
                    vi = 0;
                    bi = i;
                }
                if (newpos.ele[0]>0) {
                    fi = FACE_RIGHT;
                } else {
                    fi = FACE_LEFT;
                }
            }

            if (fabs(newpos.ele[1]) > WALL_SIZE-parti.radius) {
                rt = (WALL_SIZE - fabs(parti.position.ele[1]) - parti.radius) / fabs(parti.velocity.ele[1]);
                if (rt < lamda) {
                    if (rt<0) {
                        parti.update_position(rt);
                        rt=-rt;
                    }
                    lamda = rt;
                    vi = 1;
                    bi = i;
                }
                if (newpos.ele[1]>0) {
                    fi = FACE_TOP;
                } else {
                    fi = FACE_BOTTOM;
                }
            }

            if (fabs(newpos.ele[2]) > WALL_SIZE-parti.radius) {
                rt = (WALL_SIZE - fabs(parti.position.ele[2]) - parti.radius) / fabs(parti.velocity.ele[2]);
                if (rt < lamda) {
                    if (rt<0) {
                        parti.update_position(rt);
                        rt=-rt;
                    }
                    lamda = rt;
                    vi = 2;
                    bi = i;
                }
                if (newpos.ele[2]>0) {
                    fi = FACE_FRONT;
                } else {
                    fi = FACE_BACK;
                }
            }
        }

        size_t cbi, cbj;
        if (ball_collision(rt, cbi, cbj)) {

            if (lamda>rt) {
                if (rt<0) rt=0;
                resttime -= rt;


                for (size_t i=0; i<g_balls.size(); ++i) g_balls[i].update_position(rt);

                Ball &parti = g_balls[cbi];
                Ball &partj = g_balls[cbj];

                vector_type uaxis = partj.position - parti.position;
                uaxis.Normalize();

                value_type ui = parti.velocity * uaxis;
                value_type uj = partj.velocity * uaxis;
                value_type mi = parti.mass;
                value_type mj = partj.mass;

                value_type vi = g_recover_f*((mi-mj)*ui+(mj+mj)*uj)/(mi+mj);
                //if (fabs(vi)<(value_type)0.01) vi = 0;
                value_type vj = g_recover_f*((mj-mi)*uj+(mi+mi)*ui)/(mi+mj);
                //if (fabs(vj)<(value_type)0.01) vj = 0;

                parti.velocity = vi*uaxis + (parti.velocity-ui*uaxis);
                partj.velocity = vj*uaxis + (partj.velocity-uj*uaxis);

                //printf("(%f, %f, %f)\n", parti.velocity.ele[0], parti.velocity.ele[1], parti.velocity.ele[2]);
                //printf("(%f, %f, %f)\n", partj.velocity.ele[0], partj.velocity.ele[1], partj.velocity.ele[2]);

                continue;                
            }
        }

        if (lamda <= g_dt) {
            //if (lamda<0) lamda=0;
            resttime -= lamda;
            for (size_t i=0; i<g_balls.size(); ++i) g_balls[i].update_position(lamda);
            g_balls[bi].velocity.ele[vi] = -g_balls[bi].velocity.ele[vi] * g_recover_f;
            //if (fabs(g_balls[bi].velocity.ele[vi]) < (value_type)0.01) g_balls[bi].velocity.ele[vi] = 0;
            g_cube_f[fi][4] = SHOW_TIMES;

        } else {
            for (size_t i=0; i<g_balls.size(); ++i) g_balls[i].update_position(resttime);
            resttime = 0;
        }
        //printf("resttime=%f\n", resttime);
    }

}

void draw_something()
{
    if (!g_pause) {
        // (1) apply force & update velocity
        for (size_t i=0; i<g_balls.size(); ++i) {
            Ball &parti = g_balls[i];
            parti.init();
            if (g_right_button_down) parti.apply_force(vector_type(10.0, 30.0, 17.0, 0.0));
            if (fabs(parti.position.ele[1]+WALL_SIZE-parti.radius)<ZERO) parti.apply_force(-g_kf*parti.mass*(parti.velocity-vector_type(0.0, parti.velocity.ele[1], 0.0, 0.0)));
            parti.apply_force(GRAVITATION * parti.mass);
            parti.update_velocity(g_dt);
        }

        // (2) update position (use the Euler Method to solve the equations)
        update_position();
    }

    // (3) render object
    for (size_t i=0; i<g_balls.size(); ++i) {
        g_balls[i].render();
    }
}

/*
* version (2): based on discrete element method (DEM)
*/

value_type const COLLISION_SPRING = (value_type)2000;
value_type const COLLISION_DAMPING = (value_type)10;
value_type const COLLISION_FRICTION = (value_type)3;
value_type const COLLISION_ATTRACTION = (value_type)0;

bool ball_collision(Ball &bi, Ball &bj, vector_type &force)
{
    vector_type rp = bj.position - bi.position;
    value_type blen = bi.radius + bj.radius;

    if (rp.ele[0]<-blen || rp.ele[0]>blen
        || rp.ele[1]<-blen || rp.ele[1]>blen
        || rp.ele[2]<-blen || rp.ele[2]>blen)
        return false;

    value_type dist = rp.Length();
    if (dist<blen) {
        vector_type rv = bj.velocity - bi.velocity;
        vector_type rpn = rp; rpn.Normalize();
        vector_type tanv = rv - rv*rpn*rpn;
        force = vector_type(0, 0, 0, 0);
        force += - COLLISION_SPRING * (blen-dist) * rpn;
        force += COLLISION_DAMPING * rv;
        force += COLLISION_FRICTION * tanv;
        force += COLLISION_ATTRACTION * rp;
        return true;
    }

    return false;
}

void ball_collision()
{
    if (g_balls.size()<=0) return;
    for (size_t i=0; i<g_balls.size(); ++i) { g_balls[i].init(); }

    for (size_t i=0; i<g_balls.size(); ++i) {
        Ball &parti = g_balls[i];

        for (size_t j=i+1; j<g_balls.size(); ++j) {
            Ball &partj = g_balls[j];

            vector_type f;
            if (ball_collision(parti, partj, f)) {
                parti.apply_force(f);
                partj.apply_force(-f);
            }
        }

        parti.update_velocity(0.0001);
    }
}

void integrate()
{
    for (size_t i=0; i<g_balls.size(); ++i) {
        Ball &parti = g_balls[i];
        parti.init();
        if (g_right_button_down) parti.apply_force(vector_type(5.0, 15.0, 8.70, 0.0));
        if (fabs(parti.position.ele[1]+WALL_SIZE-parti.radius)<ZERO) parti.apply_force(-g_kf*parti.mass*(parti.velocity-vector_type(0.0, parti.velocity.ele[1], 0.0, 0.0)));
        matrix_type m = g_rotm;
        m.Inverse();
        vector_type gf = m * GRAVITATION * parti.mass;
        //g_force += gf;
        parti.apply_force(gf);
        parti.update_velocity(g_elapsed_seconds);
        parti.update_position(g_elapsed_seconds);

        vector_type &pos = parti.position;
        vector_type &vel = parti.velocity;
        value_type rad = parti.radius;        

        if (pos.ele[0]<-WALL_SIZE+rad) {
            pos.ele[0] = -WALL_SIZE+rad+EPS;
            vel.ele[0] *= -g_recover_f;
            g_cube_f[FACE_LEFT][4] = SHOW_TIMES;
        } if (pos.ele[0]>WALL_SIZE-rad) {
            pos.ele[0] = WALL_SIZE-rad-EPS;
            vel.ele[0] *= -g_recover_f;
            g_cube_f[FACE_RIGHT][4] = SHOW_TIMES;
        }

        if (pos.ele[1]<-WALL_SIZE+rad) {
            pos.ele[1] = -WALL_SIZE+rad+EPS;
            vel.ele[1] *= -g_recover_f;
            g_cube_f[FACE_BOTTOM][4] = SHOW_TIMES;
        } if (pos.ele[1]>WALL_SIZE-rad) {
            pos.ele[1] = WALL_SIZE-rad-EPS;
            vel.ele[1] *= -g_recover_f;
            g_cube_f[FACE_TOP][4] = SHOW_TIMES;
        }

        if (pos.ele[2]<-WALL_SIZE+rad) {
            pos.ele[2] = -WALL_SIZE+rad+EPS;
            vel.ele[2] *= -g_recover_f;
            g_cube_f[FACE_BACK][4] = SHOW_TIMES;
        } if (pos.ele[2]>WALL_SIZE-rad) {
            pos.ele[2] = WALL_SIZE-rad-EPS;
            vel.ele[2] *= -g_recover_f;
            g_cube_f[FACE_FRONT][4] = SHOW_TIMES;
        }
    }
}

void draw_something2()
{
    if (!g_pause) {
        // (1) apply force, update velocity and position
        integrate();

        // (2) collision detection and processing
        ball_collision();
    }

    // (3) render object
    for (size_t i=0; i<g_balls.size(); ++i) {
        g_balls[i].render();
    }
}

/*
* version (3): based on version (2), using space subdivision to accelerate collision computing
*/

void update_grids()
{
    for (size_t x=0; x<GRID_NUM_AXIS; ++x) {
        for (size_t y=0; y<GRID_NUM_AXIS; ++y) {
            for (size_t z=0; z<GRID_NUM_AXIS; ++z) {
                g_grids[x][y][z].clear();
            }
        }
    }
    for (size_t i=0; i<g_balls.size(); ++i) {
        unsigned int xi = (unsigned int)((g_balls[i].position.ele[0] + WALL_SIZE) / GRID_SIZE);
        unsigned int yi = (unsigned int)((g_balls[i].position.ele[1] + WALL_SIZE) / GRID_SIZE);
        unsigned int zi = (unsigned int)((g_balls[i].position.ele[2] + WALL_SIZE) / GRID_SIZE);
        g_grids[xi][yi][zi].push_back(i);
    }
}

void grid_ball_collision()
{
    update_grids();

    for (size_t i=0; i<g_balls.size(); ++i) {
        Ball &parti = g_balls[i];
        unsigned int x = (unsigned int)((parti.position.ele[0] + WALL_SIZE) / GRID_SIZE);
        unsigned int y = (unsigned int)((parti.position.ele[1] + WALL_SIZE) / GRID_SIZE);
        unsigned int z = (unsigned int)((parti.position.ele[2] + WALL_SIZE) / GRID_SIZE);

        unsigned int x1 = x==0 ? x : x-1;
        unsigned int x2 = x==GRID_NUM_AXIS-1 ? x : x+1;
        unsigned int y1 = y==0 ? y : y-1;
        unsigned int y2 = y==GRID_NUM_AXIS-1 ? y : y+1;
        unsigned int z1 = z==0 ? z : z-1;
        unsigned int z2 = z==GRID_NUM_AXIS-1 ? z : z+1;
        for (size_t xi=x1; xi<=x2; ++xi) {
            for (size_t yi=y1; yi<=y2; ++yi) {
                for (size_t zi=z1; zi<=z2; ++zi) {
                    vector<size_t> &curgrid = g_grids[xi][yi][zi];
                    for (size_t cbi=0; cbi<curgrid.size(); ++cbi) {
                        if (curgrid[cbi] == i) continue;
                        Ball &partj = g_balls[curgrid[cbi]];

                        vector_type f;
                        if (ball_collision(parti, partj, f)){
                            parti.apply_force(f);
                        }
                    }
                }
            }
        }
        parti.update_velocity(g_elapsed_seconds);
    }
}

void draw_something3()
{
    if (!g_pause) {
        // (1) apply force, update velocity and position
        integrate();

        // (2) collision detection and processing
        grid_ball_collision();
    }

    // (3) render object
    for (size_t i=0; i<g_balls.size(); ++i) {
        g_balls[i].render();
    }
}

void draw_walls()
{
    glPushMatrix();

    //glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
    int face;
    face = 5;
    g_material_diffuse[0] = 5.0f/255.0f;
    g_material_diffuse[1] = 5.0f/255.0f;
    g_material_diffuse[2] = 240.0f/255.0f;
    g_material_diffuse[3] = 1.0f;
    set_material();
    glNormal3fv(g_cube_fn[face]);
    glVertex3v(g_cube_v[g_cube_f[face][0]]);
    glVertex3v(g_cube_v[g_cube_f[face][1]]);
    glVertex3v(g_cube_v[g_cube_f[face][2]]);
    glVertex3v(g_cube_v[g_cube_f[face][3]]);

    //for (face=0; face<5; ++face) {
    //  if (g_cube_f[face][4]>0) {
    //      g_material_diffuse[3] = 0.6f*(float)(g_cube_f[face][4])/(float)(SHOW_TIMES);
    //      set_material();
    //      glNormal3fv(g_cube_fn[face]);
    //      glVertex3fv(g_cube_v[g_cube_f[face][0]]);
    //      glVertex3fv(g_cube_v[g_cube_f[face][1]]);
    //      glVertex3fv(g_cube_v[g_cube_f[face][2]]);
    //      glVertex3fv(g_cube_v[g_cube_f[face][3]]);
    //      g_cube_f[face][4] --;
    //  }
    //}
    glEnd();

    glDisable(GL_LIGHTING);
    //glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    for (unsigned int edge=0; edge<24; edge+=2) {
        glVertex3v(g_cube_v[g_cube_e[edge]]);
        glVertex3v(g_cube_v[g_cube_e[edge+1]]);
    }
    glEnd();

    glPopMatrix();
}

void display()
{
    CPUCounter counter;
    counter.CounterStart();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    g_cam.LookAt(0.0f, 0.0f, WALL_SIZE*sqrt(3.0)*(0.4+1/tan(DEGTORAD(g_fov*0.5))), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glLightfv(GL_LIGHT0, GL_POSITION, g_light_position);    // Position The Light
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, g_light_direction);
    glMultMatrix(g_rotm);
    glEnable(GL_LIGHTING);
    g_material_diffuse[0] = 1.0f;
    g_material_diffuse[1] = 0.57f;
    g_material_diffuse[2] = 0.04f;
    g_material_diffuse[3] = 1.0f;
    set_material();

    update_timer();
    draw_something3();

    draw_walls();

    glutSwapBuffers();

    double counts = counter.GetCounts();
    char str[512];
    sprintf(str, "%0.3ffps", counter.GetFrequence()/counts);
    glutSetWindowTitle(str);

}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glGetIntegerv(GL_VIEWPORT, g_viewport);

    //g_cam.Frustum(-10.0f, 10.0f, -10.0f, 10.0f, 10.0f, 150.0f);
    g_cam.Perspective(g_fov, float(w) / float(h), 1.0f, 500.0f);
    //g_cam.Ortho(-50.0f, 50.0f, -50.0f, 50.0f, 10.0f, 150.0f);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'p':
        g_pause = !g_pause;
        //if (g_pause) glutIdleFunc(0);
        //else glutIdleFunc(display);
        break;

    case 27:
        exit(0);
        break;


    default:
        break;
    }
}

void motion(int x, int y)
{
    if (g_left_button_down)
    {
        g_trackball.Update((float)(2.0*(x-g_viewport[0])/g_viewport[2]-1), (float)(2.0*(g_viewport[3]-y-1-g_viewport[1])/g_viewport[3]-1));
        g_trackball.BuildRotMatrix(g_rotm);

        glutPostRedisplay();
    }
}

void mouse(int button, int state, int x, int y)
{
    bool down = (state == GLUT_DOWN);

    switch (button) 
    {
    case GLUT_LEFT_BUTTON: g_left_button_down = down; break;
    case GLUT_MIDDLE_BUTTON: g_middle_button_down = down; break;
    case GLUT_RIGHT_BUTTON: g_right_button_down = down; break;
    }

    if (g_left_button_down)
    {
        g_trackball.Start((float)(2.0*(x-g_viewport[0])/g_viewport[2]-1), (float)(2.0*(g_viewport[3]-y-1-g_viewport[1])/g_viewport[3]-1));
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(512,512);
    glutCreateWindow("Gravity");

    if (!init()) return -1;

    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();

    return 0;
}
