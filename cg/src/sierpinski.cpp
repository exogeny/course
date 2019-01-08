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
#include <time.h>
#include "glinc.h"
#include "geotypes.h"

void display()
{
    Point2f vertices[3] = {{0.0f, 0.0f,}, {250.0f, 500.0f}, {500.0f, 0.0f}};
    Point2f p = {250.0f, 150.0f};
    
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex2fv(vertices[0].coord);
        glVertex2fv(vertices[1].coord);
        glVertex2fv(vertices[1].coord);
        glVertex2fv(vertices[2].coord);
        glVertex2fv(vertices[2].coord);
        glVertex2fv(vertices[0].coord);
    glEnd();

    srand((unsigned int)(time(0)));
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
    for (int i=0; i<55000; ++i)
    {
        int j = rand() % 3;
        //GLfloat r = (rand() & 0xff) / 255.0f;
        //GLfloat g = 1.0f;//(rand() & 0xff) / 255.0f;
        //GLfloat b = 1.0f;//(rand() & 0xff) / 255.0f;

        p.x = (p.x + vertices[j].x) / 2.0f;
        p.y = (p.y + vertices[j].y) / 2.0f;

        //glColor3f(r, g, b);
        //if (i<100) continue;
        glVertex2fv(p.coord);
    }
        glEnd();
    glFlush();
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

void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(2.5f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Sierpinski Gasket");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}
