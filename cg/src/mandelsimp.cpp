/*
-----------------------------------------------------------------------
This source file is part of "cgcourse-examples"
(Examples for Computer Graphics Course of CCCE GUCAS.)

MODIFIED FROM:
CS330 - PROJECT 2
TITLE: mandelMain.cpp
PROGRAMMER OF ORIGINAL VERSION: Mike Ware

MODIFIED BY: Xue Jian (jian.xue.cn@gmail.com)
MAJOR CHANGE: Add support for Julia set.

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
#include <stdlib.h>
#include <math.h>
#include "glinc.h"

struct point_type
{
	GLint x, y;
};

struct color_type
{
	GLdouble r, g, b;
};

/* constant initializations */

int const SCREEN_WIDTH = 512;
int const SCREEN_HEIGHT = 512;

/* global initializations */

bool g_is_zoomed;
bool g_make_julia = true;
GLint g_max_iterations;
GLdouble g_xmin, g_xmax, g_ymin, g_ymax;
GLdouble g_xmin_prev, g_xmax_prev, g_ymin_prev, g_ymax_prev;
GLdouble g_rfactor, g_ifactor;
GLdouble g_cr, g_ci;
GLdouble g_ctable[][2] = { {-0.75, 0}, {0.285, 0.01}, {0.45, -0.1428}, {0.285, 0}, {-0.8, 0.156}, {-0.835, -0.2321}, {-0.70176, -0.3842} };
unsigned int const C_NUM = sizeof(g_ctable) / (2*sizeof(GLdouble));
unsigned int g_curc = 0;


GLfloat g_color_table[1024][4];

// point plotting function using current color
void plot_point(GLdouble x, GLdouble y)
{
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

// store current set coordinates
void capture_coords()
{
    g_xmin_prev = g_xmin;
    g_xmax_prev = g_xmax;
    g_ymin_prev = g_ymin;
    g_ymax_prev = g_ymax;
}

// use previously stored coordinates to display previous set
void step_back()
{
    if (g_is_zoomed)
    {
        g_xmin = g_xmin_prev;
        g_xmax = g_xmax_prev;
        g_ymin = g_ymin_prev;
        g_ymax = g_ymax_prev;

        glutPostRedisplay();
    }
}

void reset_region()
{
    if (g_make_julia) {
        g_xmin = -1.25;				// selected region
        g_xmax = 1.25;					// of set to be drawn
        g_ymin = -1.25;
        g_ymax = 1.25;
    } else {
        g_xmin = -2.0;				// selected region
        g_xmax = .5;					// of set to be drawn
        g_ymin = -1.25;
        g_ymax = 1.25;
    }
}

// caculates the real and imag screen factors
// that map a window coordinate to a complex number
void set_factors()
{
    g_rfactor = (g_xmax - g_xmin) / (SCREEN_WIDTH - 1);
    g_ifactor = (g_ymax - g_ymin) / (SCREEN_HEIGHT - 1);
}

// displays mandelbrot set for current selected region (g_xmin, g_xmax, g_ymin, yMax)
// will draw on the entire window
void display()
{
	GLdouble sqR, sqI, colorLevel;
	GLint numOfIterations;
	GLdouble cI, cR, zI, zR;

	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();

	set_factors();	// update real and imag factors for current region

    if (g_make_julia) {
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            for (int x = 0; x < SCREEN_WIDTH; x++) {
                zI = g_ymax - y * g_ifactor;
                zR = g_xmin + x * g_rfactor;
                numOfIterations = 0;

                sqR = zR * zR;
                sqI = zI * zI;
                do {
                    zI = 2 * zR * zI + g_ci;
                    zR = sqR - sqI + g_cr;

                    sqR = zR * zR;
                    sqI = zI * zI;
                    numOfIterations++;
                } while ((sqR + sqI) <= 400 && numOfIterations < g_max_iterations);

                if (numOfIterations >= g_max_iterations) { // c in set, color black			
                    glColor3f(0.0, 0.0, 0.0);
                } else { // c not in set, vary color			
                    glColor4fv(g_color_table[1024-(int)((numOfIterations/(double)g_max_iterations)*1023)]);
                }

                plot_point(x, y);
                //printf("iter num: %d\n", numOfIterations);
            }
        }
    } else {
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            cI = g_ymax - y * g_ifactor;
            for (int x = 0; x < SCREEN_WIDTH; x++) {
                cR = g_xmin + x * g_rfactor;

                zR = cR;
                zI = cI;
                numOfIterations = 0;

                sqR = zR * zR;
                sqI = zI * zI;
                while ((sqR + sqI) <= 400 && numOfIterations < g_max_iterations) {
                    zI = 2 * zR * zI + cI;
                    zR = sqR - sqI + cR;

                    sqR = zR * zR;
                    sqI = zI * zI;
                    numOfIterations++;
                }

                if (numOfIterations >= g_max_iterations) { // c in set, color black			
                    glColor3f(0.0, 0.0, 0.0);
                } else { // c not in set, vary color			
                    glColor4fv(g_color_table[1024-(int)((numOfIterations/(double)g_max_iterations)*1023)]);
                }

                plot_point(x, y);
            }
        }
    }

	glFlush();
}

// used by zoom() to swap two corner points
void swap_corners(point_type c[])
{
    point_type temp;

    temp.x = c[0].x;
    temp.y = c[0].y;

    c[0].x = c[1].x;
    c[0].y = c[1].y;
    c[1].x = temp.x;
    c[1].y = temp.y;
}

// zoom function that determines where on screen the user has clicked
// it will readjust the selected mandelbrot set values and real and imag
// screen factors accordingly
void zoom(point_type corner[])
{
	g_is_zoomed = true;
	capture_coords();					// store current coords for stepBack()

	if (corner[0].x >= corner[1].x)		// make sure first clicked coord is
		swap_corners(corner);			// top left corner of region and second
										// clicked coord is bottom left corner
	if (corner[0].y > corner[1].y)		// of region to be zoom
	{
		g_ymin = g_ymax - corner[0].y * g_ifactor;
		g_ymax = g_ymax - corner[1].y * g_ifactor;
	}
	else
	{
		g_ymin = g_ymax - (corner[0].y + (corner[1].y - corner[0].y)) * g_ifactor;
		g_ymax = g_ymax - (corner[1].y - (corner[1].y - corner[0].y)) * g_ifactor;
	}

	g_xmin = g_xmin_prev + corner[0].x * g_rfactor;
	g_xmax = g_xmin_prev + corner[1].x * g_rfactor;

	glutPostRedisplay();
}

// mouse function that will catch two mouse left button clicks to zoom in
// on the region represented by the clicks
void mouse(int button, int state, int x, int y)
{
	static point_type corner[2];
	static int num_corners = 0;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		corner[num_corners].x = x;
		corner[num_corners].y = SCREEN_HEIGHT - y;
		num_corners++;

		if (num_corners == 2)	// two corners have been clicked by user
		{
			zoom(corner);		// zoom to two corners
			num_corners = 0;
		}
	}
}

// if user presses 'ESC' key, will terminate program
void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'b': case 'B':
            step_back();
            break;

        case 'j': case 'J':
            g_make_julia = true;
            reset_region();
            glutPostRedisplay();
            break;

        case '.': case '>':
            if (g_make_julia) {
                g_curc = (g_curc+1)%C_NUM;
                g_cr = g_ctable[g_curc][0];
                g_ci = g_ctable[g_curc][1];
				printf("c = %f + %fi\n", g_cr, g_ci);
            }
            glutPostRedisplay();
            break;
 
        case ',': case '<':
            if (g_make_julia) {
                g_curc = (g_curc+C_NUM-1)%C_NUM;
                g_cr = g_ctable[g_curc][0];
                g_ci = g_ctable[g_curc][1];
				printf("c = %f + %fi\n", g_cr, g_ci);
            }
            glutPostRedisplay();
            break;

        case 'm': case 'M':
            g_make_julia = false;
            reset_region();
            glutPostRedisplay();
            break;

        case 27:
            exit(0);
    }
}

int main(int argc, char** argv)
{
    g_max_iterations = 80;		// max # of iterations to determine if in set
    g_is_zoomed = false;			// flag denoting whether user has zoomed

    g_cr = g_ctable[g_curc][0];
    g_ci = g_ctable[g_curc][1];

    int i;
    for (i=0; i<256; ++i)
    {
        g_color_table[i][0] = 1.0f;
        g_color_table[i][1] = (float)i / 255.0f;
        g_color_table[i][2] = 0.0f;
        g_color_table[i][3] = 1.0f;
    }
    for (i=0; i<256; ++i)
    {
        g_color_table[256+i][0] = (float)(255-i) / 255.0f;
        g_color_table[256+i][1] = 1.0f;
        g_color_table[256+i][2] = 0.0f;
        g_color_table[256+i][3] = 1.0f;
    }
    for (i=0; i<256; ++i)
    {
        g_color_table[512+i][0] = 0.0f;
        g_color_table[512+i][1] = 1.0f;
        g_color_table[512+i][2] = (float)i / 255.0f;
        g_color_table[512+i][3] = 1.0f;
    }
    for (i=0; i<256; ++i)
    {
        g_color_table[768+i][0] = 0.0f;
        g_color_table[768+i][1] = (float)(255-i) / 255.0f;
        g_color_table[768+i][2] = 1.0f;
        g_color_table[768+i][3] = 1.0f;
    }

    reset_region();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("Mandelbrot Set Implementation");
    glMatrixMode(GL_PROJECTION);

    gluOrtho2D(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT);	// assuming 1024/768 resolution
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glutKeyboardFunc(keyboard);		// register keyboard function
    glutDisplayFunc(display);		// register display function
    glutMouseFunc(mouse);				// registry mouse function
    glutMainLoop();

    return 0;
}
