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

unsigned int const MAX_CPTS = 25;

unsigned int g_width = 512;
unsigned int g_height = 512;
GLint g_viewport[4];

unsigned int const PICK_BUFFER_SIZE = 512;
GLuint g_pick_buffer[PICK_BUFFER_SIZE];
GLdouble g_pick_size = 10.0;

GLfloat g_cpts[MAX_CPTS][4];
GLfloat g_knots[MAX_CPTS*2] = {0,.1,.2,.3,.4,.4,.4,.5,.6,.7,.8};
unsigned int g_cptnum = 0;
int g_curcpt = -1;
int g_curknot = -1;

int g_order = 4;

bool g_left_button_down = false;
bool g_middle_button_down = false;
bool g_right_button_down = false;

bool g_show_control_polygon = false;
bool g_show_curve = false;

float g_color_background[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float g_color_foreground[] = { 1.0f-g_color_background[0], 1.0f-g_color_background[1], 1.0f-g_color_background[2], 1.0f};

GLUnurbs *g_nurbsobj = 0;

GLfloat g_knotline_start = -0.8f;
GLfloat g_knotline_length = 1.6f;

void draw_control_points(GLenum mode)
{
	for (unsigned int i=0; i<g_cptnum; ++i) 
	{
		if (mode == GL_SELECT) glPushName(i);
		//glPushMatrix();
		//glTranslatef(g_cpts[i][0], g_cpts[i][1], g_cpts[i][2]);
		//gluDisk(g_qobj, 0, .02, 20, 20);
		//glPopMatrix();
		glPointSize((float)g_pick_size);
		glBegin(GL_POINTS);
		glVertex4fv(g_cpts[i]);
		glEnd();
		if (mode == GL_SELECT) glPopName();
	}
}

void draw_knots(GLenum mode)
{
	GLfloat ypos = -0.8f;

	glLineWidth(1.0f);
	glColor4f(1.0f, 0.2f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(g_knotline_start, ypos, 0.0f);
	glVertex3f(g_knotline_start+g_knotline_length, ypos, 0.0f);
	glEnd();

	glPointSize(6.0f);
	for (int i=0; i<g_cptnum+g_order; ++i)
	{
		if (mode == GL_SELECT) glPushName(MAX_CPTS + i);
		glBegin(GL_POINTS);
		glVertex3f(g_knotline_start+g_knots[i]*g_knotline_length, ypos, 0.0f);
		glEnd();
		if (mode == GL_SELECT) glPopName();
	}
	

}

void draw_scene(GLenum mode = GL_RENDER)
{
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);

	draw_control_points(mode);

	if (g_show_control_polygon)
	{
		glLineWidth(1.0f);
		glBegin(GL_LINE_STRIP);
		for (unsigned int i=0; i<g_cptnum; ++i) glVertex4fv(g_cpts[i]);
		glEnd();
	}

	draw_knots(mode);

	if (g_show_curve)
	{
		glLineWidth(2.0f);
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
		gluBeginCurve(g_nurbsobj);
		gluNurbsCurve(g_nurbsobj, g_cptnum+g_order, g_knots, 4, &g_cpts[0][0], g_order, GL_MAP1_VERTEX_4);
		gluEndCurve(g_nurbsobj);
	}


}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	draw_scene();
	
	glutSwapBuffers();
}


void reshape(int w, int h)
{
	g_width = w;
	g_height = h;

	glViewport(0, 0, w, h);
	glGetIntegerv(GL_VIEWPORT, g_viewport);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f ,1.0f);
	glMatrixMode(GL_MODELVIEW);
}

bool process_hits(GLint hits)
{
	//printf("hits: %d\n", hits);
	int i, j;
	GLuint names, z = ~0x0, minz = ~0x0;
 
	bool got_one = false;
	GLuint *nameptr = 0;
	for (i=0,j=0; i<hits && j<PICK_BUFFER_SIZE; ++i)
	{
		names = g_pick_buffer[j++];
		z = g_pick_buffer[j++];

		if (names>0 && z<=minz)
		{
			got_one = true;
			minz = z;
			nameptr = g_pick_buffer + j + names;

			//printf("hit!\n");
		}
		j += names + 1;
	}

	g_curcpt = -1;
	g_curknot = -1;
	if (got_one)
	{
		g_curcpt = *nameptr;
		if (g_curcpt >= MAX_CPTS)
		{
			g_curknot = g_curcpt - MAX_CPTS;
			g_curcpt = -1;
		}
	}

	return got_one;
}

bool pick(int x, int y)
{
	glSelectBuffer(PICK_BUFFER_SIZE, g_pick_buffer);
	glRenderMode(GL_SELECT);
	glInitNames();
	//glPushName(0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	{
		glLoadIdentity();
		gluPickMatrix((GLdouble)x, (GLdouble)(g_viewport[3]-y), g_pick_size, g_pick_size, g_viewport);

		glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f ,1.0f);

		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);

		draw_scene(GL_SELECT);
	}
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	//glMatrixMode(GL_MODELVIEW);

	//glFlush();
	
	return process_hits(glRenderMode(GL_RENDER));
}

void motion(int x, int y)
{
	if (g_left_button_down && (g_curcpt>=0 || g_curknot>=0))
	{
		float wx = (2.0f * float(x)) / float(g_width -1) - 1.0f;
		if (g_curcpt>=0)
		{
			float wy = (2.0f * float(g_height-1-y)) / float(g_height-1) -1.0f;
			g_cpts[g_curcpt][0] = wx*g_cpts[g_curcpt][3];
			g_cpts[g_curcpt][1] = wy*g_cpts[g_curcpt][3];
			g_cpts[g_curcpt][2] = 0.0f;
		}
		else if (g_curknot>=0)
		{
			wx = (wx - g_knotline_start) / g_knotline_length;
			float left = g_curknot==0 ? 0.0f : g_knots[g_curknot-1];
			float right = g_curknot==g_cptnum+g_order-1 ? 1.0f : g_knots[g_curknot+1];
			if (wx<left) wx = left;
			if (wx>right) wx = right;
			g_knots[g_curknot] = wx;
		}
		glutPostRedisplay();
	}

}

void update_knots()
{
	float step = 1.0f / (float)(g_cptnum+g_order-1);
	g_knots[0] = 0.0f;
	for (int i=1; i<g_cptnum+g_order; ++i) g_knots[i] = g_knots[i-1]+step;
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
		if (pick(x, y))
		{
		}
		else 
		{
			if (g_cptnum >= MAX_CPTS) return;
			float wx = (2.0f * float(x)) / float(g_width -1) - 1.0f;
			float wy = (2.0f * float(g_height-1-y)) / float(g_height-1) -1.0f;

			g_cpts[g_cptnum][3] = g_cptnum==1 ? 1.0f : 1.0f;
			g_cpts[g_cptnum][0] = wx*g_cpts[g_cptnum][3];
			g_cpts[g_cptnum][1] = wy*g_cpts[g_cptnum][3];
			g_cpts[g_cptnum][2] = 0.0f;
			g_cptnum ++;

			update_knots();
		}
	}

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q': case 'Q':
		exit(0);
		break;

	case 'c': case 'C':
		g_cptnum = 0;
		glutPostRedisplay();
		break;

	case 'e': case 'E':
		g_show_control_polygon = false;
		g_show_curve = false;
		glutPostRedisplay();
		break;

	case 'p': case 'P':
		g_show_control_polygon = !g_show_control_polygon;
		glutPostRedisplay();
		break;

	case 'n': case 'N':
		g_show_curve = !g_show_curve;
		glutPostRedisplay();
		break;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(g_width, g_height); 
	glutCreateWindow("Nurbs Curve"); 

	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);

	glClearColor(g_color_background[0], g_color_background[1], g_color_background[2], g_color_background[3]);

	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_FLAT);
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);

	if (!(g_nurbsobj = gluNewNurbsRenderer())) return -1;
	gluNurbsProperty(g_nurbsobj, GLU_SAMPLING_TOLERANCE, 10.0f);

	update_knots();

	glutMainLoop();

	gluDeleteNurbsRenderer(g_nurbsobj);

	return 0;
}
