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

#include <stdio.h>
#include "glinc.h"
#include "trackball.h"
#include "quaternion.h"
#include "camera.h"

unsigned int const PICK_BUFFER_SIZE = 512;
GLuint g_pick_buffer[PICK_BUFFER_SIZE];
GLdouble g_pick_size = 0.1;

bool g_left_button_down = false;
bool g_middle_button_down = false;
bool g_right_button_down = false;
int g_last_x = 0;
int g_last_y = 0;

GLdouble g_ball_radius = 0.05;
GLint g_ball_slices = 10;
GLint g_ball_stacks = 10;

GLUquadric *g_qobj;

int g_curcpt_u = -1;
int g_curcpt_v = -1;

GLint g_viewport[4];
TrackBallf g_trackball;
Matrixf g_modelm;
Cameraf g_cam;
Vectorf g_screen_point;
Matrixf g_transm;

/* 控制点坐标 */
GLfloat g_cpts[4][4][3] = {
	{{-1.5, -1.5, 2.0}, {-0.5, -1.5, 2.0},
	{0.5, -1.5, -1.0}, {1.5, -1.5, 2.0}},
	{{-1.5, -0.5, 1.0}, {-0.5, 1.5, 2.0},
	{0.5, 0.5, 1.0}, {1.5, -0.5, -1.0}},
	{{-1.5, 0.5, 2.0}, {-0.5, 0.5, 1.0},
	{0.5, 0.5, 3.0}, {1.5, -1.5, 1.5}},
	{{-1.5, 1.5, -2.0}, {-0.5, 1.5, -2.0},
	{0.5, 0.5, 1.0}, {1.5, 1.5, -1.0}}
};

void initlights()
{
	GLfloat ambient[] = { 0.4, 0.6, 0.2, 1.0 };
	GLfloat position[] = { 0.0, 0.0, 3.0, 1.0 };
	GLfloat mat_diffuse[] = { 0.2, 0.4, 0.8, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 80.0 };
	//glFrontFace(GL_CCW);
	//glEnable(GL_AUTO_NORMAL);
	//glEnable(GL_NORMALIZE);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
    
    //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE);
}

void draw_scene(GLenum mode)
{
	glPushMatrix();
	if (!g_left_button_down) 
	{
		//g_trackball.Update(g_trackball.GetUpdateQuat());
		//g_trackball.BuildRotMatrix(g_modelm);
	}

	//g_modelm.Rotate(35.0, 1.0, 1.0, 1.0);
	glMultMatrixf(g_modelm);

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12,
		4, &g_cpts[0][0][0]);
	glMapGrid2f(80, 0.0, 1.0, 80, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, 80, 0, 80);

	// draw control points
	for (int ui=0; ui<4; ++ui)
	{
		if (mode == GL_SELECT) glPushName(ui);
		for (int vi=0; vi<4; ++vi)
		{
			if (mode == GL_SELECT) glPushName(vi);
			glPushMatrix();
			glTranslatef(g_cpts[ui][vi][0], g_cpts[ui][vi][1], g_cpts[ui][vi][2]);
			gluSphere(g_qobj, g_ball_radius, g_ball_slices, g_ball_stacks);
			glPopMatrix();
			if (mode == GL_SELECT) glPopName();
		}
		if (mode == GL_SELECT) glPopName();
	}

	glPopMatrix();
	//glFlush();
}

/*
 *	processHits prints out the contents of the 
 *  selection array.
 */
bool process_hits(GLint hits)
{
	int i, j;
	GLuint names, z = 0xffffffff, minz = 0xffffffff;
 
	bool got_one = false;
	GLuint *nameptr = NULL;
	for (i=0,j=0; i<hits && j<PICK_BUFFER_SIZE; ++i)
	{
		names = g_pick_buffer[j++];
		z = g_pick_buffer[j++];

		if (names>1 && z<=minz)
		{
			got_one = true;
			minz = z;
			nameptr = g_pick_buffer + j + names - 1;

			printf("hit!\n");
		}
		j += names + 1;
	}

	if (got_one)
	{
		g_curcpt_u = *(nameptr++);
		g_curcpt_v = *nameptr;
	}
	else
	{
		g_curcpt_u = -1;
	}

	return got_one;
}

bool pick(int x, int y)
{
	glSelectBuffer(PICK_BUFFER_SIZE, g_pick_buffer);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	{
		glLoadIdentity();
		gluPickMatrix((GLdouble)x, (GLdouble)(g_viewport[3]-y), g_pick_size, g_pick_size, g_viewport);

		glMultMatrixf(g_cam.GetProjectionMatrix());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);

		draw_scene(GL_SELECT);
	}
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	
	//看看拾到了什么
	return process_hits(glRenderMode(GL_RENDER));
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	//g_cam.LookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	draw_scene(GL_RENDER);
    
    glutSwapBuffers();
}

void init()
{
	g_modelm.IdentityMatrix();
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glEnable (GL_DEPTH_TEST);
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12,
		4, &g_cpts[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glMapGrid2f(80, 0.0, 1.0, 80, 0.0, 1.0);
	initlights();

	g_qobj = gluNewQuadric();
	gluQuadricDrawStyle(g_qobj, GLU_FILL);
	gluQuadricNormals(g_qobj, GLU_SMOOTH);
}

void reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glGetIntegerv(GL_VIEWPORT, g_viewport);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	if (w <= h)
//		glOrtho(-4.0, 4.0, -4.0*(GLfloat)h/(GLfloat)w,
//		4.0*(GLfloat)h/(GLfloat)w, -4.0, 4.0);
//	else
//		glOrtho(-4.0*(GLfloat)w/(GLfloat)h,
//		4.0*(GLfloat)w/(GLfloat)h, -4.0, 4.0, -4.0, 4.0);
	g_cam.Perspective(45.0f, (float)(w)/(float)(h), 1.1f, 100.0f);
	//g_cam.Ortho(-4.0f, 4.0f, -4.0f, 4.0f, 1.0f, 400.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	g_cam.LookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

void motion(int x, int y)
{
	if (g_left_button_down)
	{
		if (g_curcpt_u<0)
		{
			g_last_x = x;
			g_last_y = y;
			g_trackball.Update((float)(2.0*(x-g_viewport[0])/g_viewport[2]-1), (float)(2.0*(g_viewport[3]-y-1-g_viewport[1])/g_viewport[3]-1));
			g_trackball.BuildRotMatrix(g_modelm);
		}
		else
		{
			g_screen_point.ele[0] = (float)((x - g_viewport[0]) * 2.0f / g_viewport[2] - 1);
			g_screen_point.ele[1] = (float)((g_viewport[3] - y -1 - g_viewport[1]) * 2.0f / g_viewport[3] - 1);
			g_screen_point.ele[3] = 1.0f;

			printf("%f, %f, %f\n", g_screen_point.ele[0], g_screen_point.ele[1], g_screen_point.ele[2]);

			Vectorf curv = g_screen_point;
			curv *= g_cam.GetInverseOfProjectionMatrix();
			float temp;
			if (!g_cam.IsParallelProjection())
			{
				temp = 1.0f / curv.ele[3];
				curv.ele[0] *= temp;
				curv.ele[1] *= temp;
				curv.ele[2] *= temp;
				curv.ele[3] = 1.0f;
			}

			curv *= g_transm;
			//curv *= g_cam.GetInverseOfViewMatrix();

			printf("%f, %f, %f\n", curv.ele[0], curv.ele[1], curv.ele[2]);

			GLfloat *curcpt = g_cpts[g_curcpt_u][g_curcpt_v];
			curcpt[0] = curv.ele[0];
			curcpt[1] = curv.ele[1];
			curcpt[2] = curv.ele[2];
		}

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
		if (pick(x, y))
		{
			GLfloat *curcpt = g_cpts[g_curcpt_u][g_curcpt_v];
			g_screen_point.ele[0] = curcpt[0];
			g_screen_point.ele[1] = curcpt[1];
			g_screen_point.ele[2] = curcpt[2];
			g_screen_point.ele[3] = 1.0f;

			g_transm = g_cam.GetProjectionMatrix() * g_cam.GetViewMatrix() * g_modelm;
			g_screen_point *= g_transm;
			float temp;
			if (!g_cam.IsParallelProjection())
			{
				temp = 1.0f / g_screen_point.ele[3];
				g_screen_point.ele[0] *= temp;
				g_screen_point.ele[1] *= temp;
				g_screen_point.ele[2] *= temp;
				g_screen_point.ele[3] = 1.0f;
			}

			Matrixf invm = g_modelm;
			invm.Inverse();
			g_transm = invm * g_cam.GetInverseOfViewMatrix();
		}
		else g_trackball.Start((float)(2.0*(x-g_viewport[0])/g_viewport[2]-1), (float)(2.0*(g_viewport[3]-y-1-g_viewport[1])/g_viewport[3]-1));
	}

	g_last_x = x;
	g_last_y = y;	
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

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(512, 512); 
	glutCreateWindow("Lighted and Filled Bezier Surface"); 

	init();
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);


	glutMainLoop();

	gluDeleteQuadric(g_qobj);

	return 0;
}
