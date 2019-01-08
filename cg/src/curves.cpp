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
#include <stdlib.h>
#include <string.h>
#include "glinc.h"

typedef enum _curve_type
{
    BEZIER,
    INTERPOLATED,
    BSPLINE

} CurveType;

GLint g_viewport[4];

unsigned int const PICK_BUFFER_SIZE = 512;
GLuint g_pick_buffer[PICK_BUFFER_SIZE];
GLdouble g_pick_size = 10.0;
int g_curcpt = -1;

bool g_left_button_down = false;
bool g_middle_button_down = false;
bool g_right_button_down = false;

GLfloat g_colors[][3] =
{
    {1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f}
};

unsigned int const MAX_CPTS = 25;

bool g_show_control_polygon = false;
bool g_show_new_cpts = false;
bool g_show_new_control_polygon = false;
bool g_show_bezier = false;
bool g_show_interpolated = false;
bool g_show_bspline = false;

GLfloat g_cpts[MAX_CPTS][3];
GLfloat g_newcpts[MAX_CPTS][3];
unsigned int g_cptnum = 0;

int g_order = 4;

unsigned int g_width = 512;
unsigned int g_height = 512;

float g_color_background[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float g_color_foreground[] = { 1.0f-g_color_background[0], 1.0f-g_color_background[1], 1.0f-g_color_background[2], 1.0f};

float g_minterp[4][4] = 
{
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { -5.0f/6.0f, 3.0f, -3.0f/2.0f, 1.0f/3.0f },
    { 1.0f/3.0f, -3.0f/2.0f, 3.0f, -5.0f/6.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f }
};

float g_mbspline[4][4] = 
{
    { 1.0f/6.0f, 4.0f/6.0f, 1.0f/6.0f, 0.0f },
    { 0.0f, 4.0f/6.0f, 2.0f/6.0f, 0.0f },
    { 0.0f, 2.0f/6.0f, 4.0f/6.0f, 0.0f },
    { 0.0f, 1.0f/6.0f, 4.0f/6.0f, 1.0f/6.0f }
};

float g_midentity[4][4] = 
{
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f }
};


void vmul(float m[4][4], float v[4][3], float r[4][3])
{
    for (int i=0; i<4; ++i)
        for (int j=0; j<3; ++j)
        {
            r[i][j] = 0.0f;
            for (int k=0; k<4; ++k)
                r[i][j] += m[i][k] * v[k][j];
        }
}

void copy_matrix(CurveType type, float m[4][4])
{
    switch (type)
    {
    case BEZIER: memcpy(&m[0][0], &g_midentity[0][0], 4*4*sizeof(float)); break;
    case INTERPOLATED: memcpy(&m[0][0], &g_minterp[0][0], 4*4*sizeof(float)); break;
    case BSPLINE: memcpy(&m[0][0], &g_mbspline[0][0], 4*4*sizeof(float)); break;
    }
}

void draw_curves(CurveType type)
{
    unsigned int i, step;
    float m[4][4];
    GLfloat newcpts[4][3];

    if (type != BEZIER) copy_matrix(type, m);

    int order;
    if (type == BEZIER)
    {
        order = g_order;
        step = order - 1;
    }
    else
    {
        order = 4;
        if (type == BSPLINE) step = 1;
        else step = 3;
    }

    glColor3fv(g_colors[type]);

    i=0;
    while (i+order-1 < g_cptnum)
    {
        GLfloat *cpts = &g_cpts[i][0];
        if (type != BEZIER) 
        {
            vmul(m, &g_cpts[i], newcpts);
            cpts = &newcpts[0][0];
        }

        glLineWidth(2.0f);
        glMap1f(GL_MAP1_VERTEX_3, 0.0f, 1.0f, 3, order, cpts);
        glMapGrid1f(30, 0.0f, 1.0f);
        glEvalMesh1(GL_LINE, 0, 30);

        if (g_show_new_cpts)
        {
            glPointSize(5.0f);
            glBegin(GL_POINTS);
            for (unsigned int i=0; i<4; ++i) glVertex3fv(cpts+i*3);
            glEnd();
        }

        if (g_show_new_control_polygon)
        {
            glLineWidth(1.0f);
            glBegin(GL_LINE_STRIP);
            for (unsigned int i=0; i<4; ++i) glVertex3fv(cpts+i*3);
            glEnd();
        }

        i += step;
    }
}

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
        glVertex3fv(g_cpts[i]);
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
        for (unsigned int i=0; i<g_cptnum; ++i) glVertex3fv(g_cpts[i]);
        glEnd();
    }

    if (g_show_bezier) draw_curves(BEZIER);
    if (g_show_interpolated) draw_curves(INTERPOLATED);
    if (g_show_bspline) draw_curves(BSPLINE);

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    draw_scene();
    
    glutSwapBuffers();
}



/*
 *  processHits prints out the contents of the 
 *  selection array.
 */
bool process_hits(GLint hits)
{
    //printf("hits: %d\n", hits);
    int i, j;
    GLuint names, z = ~0x0, minz = ~0x0;
 
    bool got_one = false;
    GLuint *nameptr = NULL;
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

    if (got_one)
    {
        g_curcpt = *nameptr;
    }
    else
    {
        g_curcpt = -1;
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
    if (g_left_button_down && g_curcpt>=0)
    {
        float wx = (2.0f * float(x)) / float(g_width -1) - 1.0f;
        float wy = (2.0f * float(g_height-1-y)) / float(g_height-1) -1.0f;
        g_cpts[g_curcpt][0] = wx;
        g_cpts[g_curcpt][1] = wy;
        g_cpts[g_curcpt][2] = 0.0f;
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
        }
        else 
        {
            if (g_cptnum >= MAX_CPTS) return;
            float wx = (2.0f * float(x)) / float(g_width -1) - 1.0f;
            float wy = (2.0f * float(g_height-1-y)) / float(g_height-1) -1.0f;

            g_cpts[g_cptnum][0] = wx;
            g_cpts[g_cptnum][1] = wy;
            g_cpts[g_cptnum][2] = 0.0f;
            g_cptnum ++;
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
        g_show_new_cpts = false;
        g_show_new_control_polygon = false;
        g_show_bezier = false;
        g_show_interpolated = false;
        g_show_bspline = false;
        glutPostRedisplay();
        break;

    case 'b': case 'B':
        g_show_bezier = !g_show_bezier;
        glutPostRedisplay();
        break;

    case 'i': case 'I':
        g_show_interpolated = !g_show_interpolated;
        glutPostRedisplay();
        break;

    case 's': case 'S':
        g_show_bspline = !g_show_bspline;
        glutPostRedisplay();
        break;

    case '1':
        g_show_control_polygon = !g_show_control_polygon;
        glutPostRedisplay();
        break;

    case '2':
        g_show_new_cpts = !g_show_new_cpts;
        glutPostRedisplay();
        break;

    case '3':
        g_show_new_control_polygon = !g_show_new_control_polygon;
        glutPostRedisplay();
        break;

    }
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

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(g_width, g_height); 
    glutCreateWindow("Curves"); 

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);

    glClearColor(g_color_background[0], g_color_background[1], g_color_background[2], g_color_background[3]);
    glEnable(GL_MAP1_VERTEX_3);

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_FLAT);
    glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);

    glutMainLoop();

    return 0;
}
