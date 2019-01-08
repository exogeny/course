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
#include "glinc.h"

#include "trackball.h"
#include "quaternion.h"
#include "camera.h"
#include "cpucounter.h"

float g_light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
float g_light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
float g_light_position[] = { -10.0f, 10.0f, 10.0f, 1.0f };
float g_light_direction[] = { 1.0f, -1.0f, -1.0f, 0.0f };

float g_material_ambient[]  = { 1.0f, 0.57f, 0.04f, 1.0f };
float g_material_diffuse[]  = { 1.0f, 0.57f, 0.04f, 1.0f };
float g_material_specular[]  = { 0.33f, 0.33f, 0.52f, 1.0f };
float g_material_emission[]  = { 0.0f, 0.0f, 0.0f, 0.0f };
float g_material_specular_power = 80.0f;

float const EPS = 0.000001;
float const BALL_SIZE = 0.1f;
float const WALL_SIZE = 1.5f;

float g_cube_v[][3] = {
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

unsigned int const FACE_FRONT = 0;
unsigned int const FACE_BACK = 1;
unsigned int const FACE_LEFT = 2;
unsigned int const FACE_RIGHT = 3;
unsigned int const FACE_TOP = 4;
unsigned int const FACE_BOTTOM = 5;

unsigned int g_cube_faceorder[] = { FACE_BACK, FACE_LEFT, FACE_RIGHT, FACE_TOP, FACE_BOTTOM };

unsigned int const g_showtimes = 80;

bool g_left_button_down = false;
bool g_middle_button_down = false;
bool g_right_button_down = false;

typedef double value_type;
typedef Vector<value_type> vector_type;
typedef Matrix<value_type> matrix_type;

GLint g_viewport[4];
TrackBall<value_type> g_trackball;
matrix_type g_rotm;
Camera<value_type> g_cam;

CPUCounter g_timer;
double g_elapsed_seconds;

value_type g_sm = 1.0f;
//value_type g_dt = 0.005f;
value_type g_attenuation = 0.8f;
value_type g_kf = 0.75;
vector_type g_force(0.0, 0.0, 0.0, 0.0);
vector_type const GRAVITATION(0.0, -9.8, 0.0, 0.0);
vector_type g_spos;//(0.0, 1.0, 0.0, 1.0);
vector_type g_svel;//(1.0, 0.0, 1.5, 0.0);

void glMultMatrix(Matrix<float> const &mat) { glMultMatrixf(mat); }
void glMultMatrix(Matrix<double> const &mat) { glMultMatrixd(mat); }

void set_material()
{
    GLenum face = GL_FRONT_AND_BACK;
    //glMaterialfv(face, GL_AMBIENT, g_material_ambient);
    glMaterialfv(face, GL_AMBIENT, g_material_diffuse);
    glMaterialfv(face, GL_DIFFUSE, g_material_diffuse);
    glMaterialfv(face, GL_SPECULAR, g_material_specular);
    glMaterialfv(face, GL_EMISSION, g_material_emission);
    glMaterialf(face, GL_SHININESS, g_material_specular_power);
}

bool init()
{
	glEnable(GL_NORMALIZE);
	//glEnable(GL_AUTO_NORMAL);
	//glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	glLightfv(GL_LIGHT0, GL_AMBIENT, g_light_ambient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT0, GL_DIFFUSE, g_light_diffuse);		// Setup The Diffuse Light
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.0f);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60.0f);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_LIGHT0);								// Enable Light One

	g_rotm.IdentityMatrix();

    g_elapsed_seconds = 0;
    g_timer.CounterStart();

	return true;
}

void update_timer()
{
    g_elapsed_seconds = g_timer.GetCounts() / g_timer.GetFrequence();
    g_timer.CounterStart();
}

void draw_something()
{
	// (1) apply force
	g_force = vector_type(0.0, 0.0, 0.0, 0.0);
	if (g_right_button_down) g_force += vector_type(10.0, 30.0, 17.0, 0.0);
	if (fabs(g_spos.ele[1]+WALL_SIZE-BALL_SIZE)<=EPS) g_force += -g_kf*g_sm*g_svel;
	matrix_type m = g_rotm;
	m.Inverse();
	vector_type gf = m * GRAVITATION * g_sm;
	g_force += gf;

	// (2) update position (use the Euler Method to solve the equations)
	g_svel += g_force * ((value_type)(1.0)/g_sm) * g_elapsed_seconds;
	g_spos += g_svel * g_elapsed_seconds;

	if (fabs(g_spos.ele[0]) >= WALL_SIZE-BALL_SIZE) {
		g_svel.ele[0] = -g_svel.ele[0]*g_attenuation;
		if (g_spos.ele[0]>0) {
			g_spos.ele[0] = WALL_SIZE-BALL_SIZE-EPS;
			g_cube_f[3][4] = g_showtimes;
		} else {
			g_spos.ele[0] = -WALL_SIZE+BALL_SIZE+EPS;
			g_cube_f[2][4] = g_showtimes;
		}
	}

	if (fabs(g_spos.ele[1]) >= WALL_SIZE-BALL_SIZE) {
		g_svel.ele[1] = -g_svel.ele[1]*g_attenuation;
		if (g_spos.ele[1]>0) {
			g_spos.ele[1] = WALL_SIZE-BALL_SIZE-EPS;
			g_cube_f[4][4] = g_showtimes;
		} else {
			g_spos.ele[1] = -WALL_SIZE+BALL_SIZE+EPS;
		}
	}

	if (fabs(g_spos.ele[2]) >= WALL_SIZE-BALL_SIZE) {
		g_svel.ele[2] = -g_svel.ele[2]*g_attenuation;
		if (g_spos.ele[2]>0) {
			g_spos.ele[2] = WALL_SIZE-BALL_SIZE-EPS;
			g_cube_f[0][4] = g_showtimes;
		} else {
			g_spos.ele[2] = -WALL_SIZE+BALL_SIZE+EPS;
			g_cube_f[1][4] = g_showtimes;
		}
	}

	// (3) render object
	glPushMatrix();

	glTranslated(g_spos.ele[0], g_spos.ele[1], g_spos.ele[2]);
	glutSolidSphere(BALL_SIZE, 50, 50);

	glPopMatrix();
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
	glVertex3fv(g_cube_v[g_cube_f[face][0]]);
	glVertex3fv(g_cube_v[g_cube_f[face][1]]);
	glVertex3fv(g_cube_v[g_cube_f[face][2]]);
	glVertex3fv(g_cube_v[g_cube_f[face][3]]);

	for (face=0; face<5; ++face) {
		if (g_cube_f[face][4]>0) {
			g_material_diffuse[3] = 0.6f*(float)(g_cube_f[face][4])/(float)(g_showtimes);
			set_material();
			glNormal3fv(g_cube_fn[face]);
			glVertex3fv(g_cube_v[g_cube_f[face][0]]);
			glVertex3fv(g_cube_v[g_cube_f[face][1]]);
			glVertex3fv(g_cube_v[g_cube_f[face][2]]);
			glVertex3fv(g_cube_v[g_cube_f[face][3]]);
			g_cube_f[face][4] --;
		}
	}

	/*
	// Back Face
	glNormal3f( 0.0f, 0.0f,1.0f);
	glVertex3fv(g_cube_v[4]);
	glVertex3fv(g_cube_v[5]);
	glVertex3fv(g_cube_v[6]);
	glVertex3fv(g_cube_v[7]);

	// Top Face
	glNormal3f( 0.0f, -1.0f, 0.0f);
	glVertex3fv(g_cube_v[5]);
	glVertex3fv(g_cube_v[3]);
	glVertex3fv(g_cube_v[2]);
	glVertex3fv(g_cube_v[6]);

	// Bottom Face
	glNormal3f( 0.0f,1.0f, 0.0f);
	glVertex3fv(g_cube_v[4]);
	glVertex3fv(g_cube_v[7]);
	glVertex3fv(g_cube_v[1]);
	glVertex3fv(g_cube_v[0]);

	// Right face
	glNormal3f( -1.0f, 0.0f, 0.0f);
	glVertex3fv(g_cube_v[7]);
	glVertex3fv(g_cube_v[6]);
	glVertex3fv(g_cube_v[2]);
	glVertex3fv(g_cube_v[1]);

	// Left Face
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3fv(g_cube_v[4]);
	glVertex3fv(g_cube_v[0]);
	glVertex3fv(g_cube_v[3]);
	glVertex3fv(g_cube_v[5]);

	// Front Face
	glNormal3f( 0.0f, 0.0f, 1.0f);
	glVertex3fv(g_cube_v[0]);
	glVertex3fv(g_cube_v[1]);
	glVertex3fv(g_cube_v[2]);
	glVertex3fv(g_cube_v[3]);
	*/

	glEnd();

	glPopMatrix();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    g_cam.LookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	glLightfv(GL_LIGHT0, GL_POSITION, g_light_position);	// Position The Light
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, g_light_direction);
	glMultMatrix(g_rotm);
	glEnable(GL_LIGHTING);
	g_material_diffuse[0] = 1.0f;
	g_material_diffuse[1] = 0.57f;
	g_material_diffuse[2] = 0.04f;
	g_material_diffuse[3] = 1.0f;
	set_material();

    update_timer();
	draw_something();
	draw_walls();


	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glGetIntegerv(GL_VIEWPORT, g_viewport);

	//g_cam.Frustum(-10.0f, 10.0f, -10.0f, 10.0f, 10.0f, 150.0f);
	g_cam.Perspective(60.0f, float(w) / float(h), 2.0f, 5000.0f);
	//g_cam.Ortho(-50.0f, 50.0f, -50.0f, 50.0f, 10.0f, 150.0f);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
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
