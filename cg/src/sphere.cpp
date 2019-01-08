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
#include "glinc.h"
#include "matrix.h"
#include "geotypes.h"
#include "trackball.h"
#include "camera.h"

using std::vector;

int g_n = 0;

int g_window_width = 512;
int g_window_height = 512;

GLfloat g_light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat g_light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat g_light_position[] = { -3.5f, 1.5f, 2.5f, 1.0f };
GLfloat g_light_direction[] = { 3.5f, -1.5f, -2.5f, 0.0f };
GLfloat g_light_rot = 0.0f;
GLfloat g_light_rot_speed = 0.2f;

GLfloat g_material_ambient[]  = { 1.0f, 0.57f, 0.04f, 1.0f };
GLfloat g_material_diffuse[]  = { 1.0f, 0.57f, 0.04f, 1.0f };
GLfloat g_material_specular[]  = { 0.33f, 0.33f, 0.52f, 0.0f };
GLfloat g_material_emission[]  = { 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat g_material_specular_power = 80.0f;

GLfloat g_color_background[] = { 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat g_color_foreground[] = { 1.0f-g_color_background[0], 1.0f-g_color_background[1], 1.0f-g_color_background[2], 1.0f};


bool g_flat_normal = false;
bool g_flat_shading = false;
bool g_fullscreen = false;
bool g_wireframe = false;

bool g_left_button_down = false;
bool g_middle_button_down = false;
bool g_right_button_down = false;
int g_last_x = 0;
int g_last_y = 0;

float g_z = 5.0f;
float const Z_STEP = 0.1f;

GLint g_viewport[4];
TrackBallf g_trackball(1.5f);
Matrixf g_rotm;
Cameraf g_cam;

vector<Point3f> g_verts;
vector<Point3f> g_norms;
vector<TriangleFace> g_faces;

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

void gen_triangle_flat(Point3f const &a, Point3f const &b, Point3f const &c)
{
	Vectorf v0(b.x-a.x, b.y-a.y, b.z-a.z), v1(c.x-a.x, c.y-a.y, c.z-a.z);
	v0 = v0 % v1;
	v0.Normalize();
	Point3f n;
	n.x = v0.ele[0];
	n.y = v0.ele[1];
	n.z = v0.ele[2];

	g_norms.push_back(n);

	g_verts.push_back(a);
	g_verts.push_back(b);
	g_verts.push_back(c);
}

void gen_triangle_smooth(Point3f const &a, Point3f const &b, Point3f const &c)
{
	g_norms.push_back(a);
	g_verts.push_back(a);

	g_norms.push_back(b);
	g_verts.push_back(b);

	g_norms.push_back(c);
	g_verts.push_back(c);
}

void divide_triangle(Point3f const &a, Point3f const &b, Point3f const &c, int n)
{
	if (n>0)
	{
		Vectorf v1(a.x+b.x, a.y+b.y, a.z+b.z), 
			v2(b.x+c.x, b.y+c.y, b.z+c.z),
			v3(c.x+a.x, c.y+a.y, c.z+a.z);

		v1.Normalize();
		v2.Normalize();
		v3.Normalize();

		Point3f p1, p2, p3;

		p1.x = v1.ele[0];
		p1.y = v1.ele[1];
		p1.z = v1.ele[2];

		p2.x = v2.ele[0];
		p2.y = v2.ele[1];
		p2.z = v2.ele[2];

		p3.x = v3.ele[0];
		p3.y = v3.ele[1];
		p3.z = v3.ele[2];

		divide_triangle(a, p1, p3, n-1);
		divide_triangle(b, p2, p1, n-1);
		divide_triangle(c, p3, p2, n-1);
		divide_triangle(p1, p2, p3, n-1);
	}
	else
	{
		if (g_flat_normal) gen_triangle_flat(a, b, c);
		else gen_triangle_smooth(a, b, c);
	}
}

void gen_sphere(int n)
{
	Point3f v[4] = { {0.0f, 0.0f, 1.0f},
	               {0.0f, 0.942809f, -0.333333f},
	               {-0.816497f, -0.471405f, -0.333333f},
	               {0.816497f, -0.471405f, -0.333333f}};

	g_verts.clear();
	g_norms.clear();

	divide_triangle(v[0], v[1], v[2], n);
	divide_triangle(v[3], v[2], v[1], n);
	divide_triangle(v[0], v[3], v[1], n);
	divide_triangle(v[0], v[2], v[3], n);

	printf("Triangles: %u\n", g_verts.size()/3);
	printf("Vertices: %u\n", g_verts.size());
}

void gen_triangle_flat_2(unsigned int ia, unsigned int ib, unsigned int ic)
{
	Point3f const &a = g_verts[ia];
	Point3f const &b = g_verts[ib];
	Point3f const &c = g_verts[ic];

	Vectorf v0(b.x-a.x, b.y-a.y, b.z-a.z), v1(c.x-a.x, c.y-a.y, c.z-a.z);
	v0 = v0 % v1;
	v0.Normalize();
	Point3f n;
	n.x = v0.ele[0];
	n.y = v0.ele[1];
	n.z = v0.ele[2];

	g_norms.push_back(n);

	TriangleFace f;
	f.verts[0] = ia;
	f.verts[1] = ib;
	f.verts[2] = ic;

	g_faces.push_back(f);
}

void gen_triangle_smooth_2(unsigned int ia, unsigned int ib, unsigned int ic)
{
	TriangleFace f;
	f.verts[0] = ia;
	f.verts[1] = ib;
	f.verts[2] = ic;

	g_faces.push_back(f);
}

void divide_triangle_2(unsigned int ia, unsigned int ib, unsigned int ic, int n)
{
	if (n>0)
	{
		Point3f const &a = g_verts[ia];
		Point3f const &b = g_verts[ib];
		Point3f const &c = g_verts[ic];

		Vectorf v1(a.x+b.x, a.y+b.y, a.z+b.z), 
			v2(b.x+c.x, b.y+c.y, b.z+c.z),
			v3(c.x+a.x, c.y+a.y, c.z+a.z);

		v1.Normalize();
		v2.Normalize();
		v3.Normalize();

		Point3f p1, p2, p3;

		p1.x = v1.ele[0];
		p1.y = v1.ele[1];
		p1.z = v1.ele[2];

		p2.x = v2.ele[0];
		p2.y = v2.ele[1];
		p2.z = v2.ele[2];

		p3.x = v3.ele[0];
		p3.y = v3.ele[1];
		p3.z = v3.ele[2];

		unsigned int ip1 = g_verts.size();
		g_verts.push_back(p1);

		unsigned int ip2 = g_verts.size();
		g_verts.push_back(p2);

		unsigned int ip3 = g_verts.size();
		g_verts.push_back(p3);

		if (!g_flat_normal)
		{
			g_norms.push_back(p1);
			g_norms.push_back(p2);
			g_norms.push_back(p3);
		}

		divide_triangle_2(ia, ip1, ip3, n-1);
		divide_triangle_2(ib, ip2, ip1, n-1);
		divide_triangle_2(ic, ip3, ip2, n-1);
		divide_triangle_2(ip1, ip2, ip3, n-1);
	}
	else
	{
		if (g_flat_normal) gen_triangle_flat_2(ia, ib, ic);
		else gen_triangle_smooth_2(ia, ib, ic);
	}
}

void gen_sphere_2(int n)
{
	Point3f v[4] = { {0.0f, 0.0f, 1.0f},
	               {0.0f, 0.942809f, -0.333333f},
	               {-0.816497f, -0.471405f, -0.333333f},
	               {0.816497f, -0.471405f, -0.333333f}};

	g_verts.clear();
	g_norms.clear();
	g_faces.clear();

	g_verts.push_back(v[0]);
	g_verts.push_back(v[1]);
	g_verts.push_back(v[2]);
	g_verts.push_back(v[3]);

	if (!g_flat_normal)
	{
		g_norms.push_back(v[0]);
		g_norms.push_back(v[1]);
		g_norms.push_back(v[2]);
		g_norms.push_back(v[3]);
	}

	divide_triangle_2(0, 1, 2, n);
	divide_triangle_2(3, 2, 1, n);
	divide_triangle_2(0, 3, 1, n);
	divide_triangle_2(0, 2, 3, n);

	printf("Recursion Depth: %d\n", g_n);
	printf("Triangles: %u\n", g_faces.size());
	printf("Vertices: %u\n", g_verts.size());
}


bool init() 
{
	g_rotm.IdentityMatrix();

	gen_sphere_2(g_n);

	set_material();
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(g_color_background[0], g_color_background[1], g_color_background[2], g_color_background[3]);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION,  1.0f);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION,    0.0f);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0f);

	//glLightfv(GL_LIGHT1, GL_AMBIENT, g_light_ambient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, g_light_diffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_SPECULAR, g_light_diffuse);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0f);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 60.0f);
	//glLightfv(GL_LIGHT1, GL_POSITION, g_light_position);	// Position The Light
	//glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, g_light_direction);
	glEnable(GL_LIGHT1);								// Enable Light One


	//float fcolor[4] = {0.8f, 0.8f, 0.8f, 1.0f};
	//glEnable(GL_FOG);
	//glFogf(GL_FOG_MODE, GL_EXP);
	//glFogf(GL_FOG_DENSITY, 0.1);
	//glFogfv(GL_FOG_COLOR, fcolor);

	return true;										// Initialization Went OK
}

void motion(int x, int y)
{
	if (g_left_button_down)
	{
		g_last_x = x;
		g_last_y = y;
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

	g_last_x = x;
	g_last_y = y;	
}

void draw_sphere()
{
	if (g_flat_normal)
	{
		glBegin(GL_TRIANGLES);
		for (unsigned int i=0; i<g_norms.size(); ++i)
		{
			glNormal3fv(g_norms[i].coord);
			glVertex3fv(g_verts[i*3].coord);
			glVertex3fv(g_verts[i*3+1].coord);
			glVertex3fv(g_verts[i*3+2].coord);
		}
		glEnd();
	}
	else
	{
		glBegin(GL_TRIANGLES);
		for (unsigned int i=0; i<g_verts.size(); i+=3)
		{
			glNormal3fv(g_norms[i].coord);
			glVertex3fv(g_verts[i].coord);

			glNormal3fv(g_norms[i+1].coord);
			glVertex3fv(g_verts[i+1].coord);

			glNormal3fv(g_norms[i+2].coord);
			glVertex3fv(g_verts[i+2].coord);
		}
		glEnd();
	}
}

void draw_sphere_2()
{
	if (g_wireframe)
	{
		//glDisable(GL_LIGHTING);
		glEnable(GL_LIGHTING);
		glColor4fv(g_color_foreground);
		glBegin(GL_LINES);
		for (unsigned int i=0; i<g_faces.size(); ++i)
		{
			unsigned int const *f = g_faces[i].verts;
			glVertex3fv(g_verts[f[0]].coord);
			glVertex3fv(g_verts[f[1]].coord);
			glVertex3fv(g_verts[f[1]].coord);
			glVertex3fv(g_verts[f[2]].coord);
			glVertex3fv(g_verts[f[2]].coord);
			glVertex3fv(g_verts[f[0]].coord);
		}
		glEnd();
	}
	else
	{
		glEnable(GL_LIGHTING);
		if (g_flat_normal)
		{
			glBegin(GL_TRIANGLES);
			for (unsigned int i=0; i<g_faces.size(); ++i)
			{
				unsigned int const *f = g_faces[i].verts;
				glNormal3fv(g_norms[i].coord);
				glVertex3fv(g_verts[f[0]].coord);
				glVertex3fv(g_verts[f[1]].coord);
				glVertex3fv(g_verts[f[2]].coord);
			}
			glEnd();
		}
		else
		{
			glBegin(GL_TRIANGLES);
			for (unsigned int i=0; i<g_faces.size(); ++i)
			{
				unsigned int const *f = g_faces[i].verts;

				glNormal3fv(g_norms[f[0]].coord);
				glVertex3fv(g_verts[f[0]].coord);

				glNormal3fv(g_norms[f[1]].coord);
				glVertex3fv(g_verts[f[1]].coord);

				glNormal3fv(g_norms[f[2]].coord);
				glVertex3fv(g_verts[f[2]].coord);
			}
			glEnd();
		}
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;

	case 'w':
		g_wireframe = !g_wireframe;
		break;

	case 'n':
		g_flat_normal = !g_flat_normal;
		gen_sphere_2(g_n);
        if (g_flat_normal) printf("flat normal / ");
        else printf("smooth normal / ");
        if (g_flat_shading) printf("flat shading\n");
        else printf("smooth shading\n");
		break;

    case 'f':
        g_flat_shading = !g_flat_shading;
        if (g_flat_shading) glShadeModel(GL_FLAT);
        else glShadeModel(GL_SMOOTH);
        if (g_flat_normal) printf("flat normal / ");
        else printf("smooth normal / ");
        if (g_flat_shading) printf("flat shading\n");
        else printf("smooth shading\n");
        break;


	default:
		break;
	}
}

void special_keys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		g_n = g_n>=8 ? 8 : g_n+1;
		gen_sphere_2(g_n);
		break;

	case GLUT_KEY_DOWN:
		g_n = g_n<=0 ? 0 : g_n-1;
		gen_sphere_2(g_n);
		break;

	case GLUT_KEY_LEFT:
		//g_yspeed -= SPEED_STEP;
		break;

	case GLUT_KEY_RIGHT:
		//g_yspeed += SPEED_STEP;
		break;

	case GLUT_KEY_PAGE_UP:
		g_z -= Z_STEP;
		break;

	case GLUT_KEY_PAGE_DOWN:
		g_z += Z_STEP;
		break;

	case GLUT_KEY_F1:
		g_fullscreen = !g_fullscreen;
		if (g_fullscreen)
		{
			g_window_width = glutGet(GLUT_WINDOW_WIDTH);
			g_window_height = glutGet(GLUT_WINDOW_HEIGHT);
			glutFullScreen();
		}
		else 
		{
			glutPositionWindow(50, 50);
			glutReshapeWindow(g_window_width, g_window_height);
		}
		break;
	}
}

void draw_something()
{
	glEnable(GL_LIGHTING);
	//glutSolidSphere(1.0, 100, 100);
	if (g_wireframe) glutWireTorus(0.3, 1.0, 100, 100);
	else glutSolidTorus(0.3, 1.0, 100, 100);
	glutSolidTeapot(0.7);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (!g_left_button_down) 
	{
		//Matrixf rotvm;
		//g_rotv.BuildMatrix(rotvm);
		//g_rotm = rotvm * g_rotm;
		g_trackball.Update(g_trackball.GetUpdateQuat());
		g_trackball.BuildRotMatrix(g_rotm);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	g_cam.LookAt(0.0f, 0.0f, g_z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	//glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	    glRotatef(g_light_rot, 1.0f, 1.0f, -1.0f);
	    g_light_rot += g_light_rot_speed;
	    if (g_light_rot > 360.0f) g_light_rot = 0.0f;
	    glLightfv(GL_LIGHT1, GL_POSITION, g_light_position);	// Position The Light
	    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, g_light_direction);
	    glTranslatef(g_light_position[0], g_light_position[1], g_light_position[2]);
	    glutSolidSphere(0.1, 50, 50);
	glPopMatrix();

	
	glPushMatrix();
		glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(15.0f, 0.0f, 0.0f, 1.0f);

		glPushMatrix();
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			glutSolidTorus(0.01, 2.0, 10, 300);
		glPopMatrix();

		glRotatef(g_light_rot, 0.0f, 1.0f, 0.0f);
		glTranslatef(2.0f, 0.0f, 0.0f);
		g_material_diffuse[0] = 0.1f;
		g_material_diffuse[1] = 0.2f;
		g_material_diffuse[2] = 0.9f;
		set_material();
		glutSolidSphere(0.3, 50, 50);
	glPopMatrix();	

	g_material_diffuse[0] = 1.0f;
	g_material_diffuse[1] = 0.57f;
	g_material_diffuse[2] = 0.04f;
	set_material();
	glMultMatrixf(g_rotm);
	draw_sphere_2();
	//draw_something();

	glutSwapBuffers();
}


void reshape(int width, int height)
{
	if (height==0)
	{
		height=1;
	}

	glViewport(0, 0, width, height);
	glGetIntegerv(GL_VIEWPORT, g_viewport);

	g_cam.Perspective(45.0f, (float)(width)/(float)(height), 1.1f, 100.0f);
}


int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(g_window_width, g_window_height);
  glutCreateWindow( "Sphere" );

  if (!init()) return -1;

  glutDisplayFunc(display); 
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special_keys);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutIdleFunc(display);

  glutMainLoop();

  return 0;
}
