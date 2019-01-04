#include <GL/freeglut.h>
#include "trackball.h"
#include "quaternion.h"
#include "camera.h"

//#ifndef GL_MULTISAMPLE
//#define GL_MULTISAMPLE  0x809D
//#endif

float g_xrot = 0.0f;
float g_yrot = 0.0f;
bool g_left_button_down = false;
bool g_middle_button_down = false;
bool g_right_button_down = false;
bool g_eular_start = false;
int g_last_x = 0;
int g_last_y = 0;

float const g_heading_stop = 30.0f;
float const g_pitch_stop = 90.0f;
float const g_bank_stop = 78.0f;
float const g_rotspeed = 0.2f;
float const g_rotsteps = 50.0f;

float g_heading = 0.0f;
float g_pitch = 0.0f;
float g_bank = 0.0f;

GLdouble g_asize;

GLint g_viewport[4];
TrackBallf g_trackball(0.4);
TrackBallf g_world_trackball(0.4);
Matrixf g_rotm;
Matrixf g_world_rotm;
Quaternionf g_rotv;
Cameraf g_cam;

GLUquadric *g_qobj;

void look_at(float eyex, float eyey, float eyez, float atx, float aty, float atz, float upx, float upy, float upz)
{
    //-z axis
    Vectorf minusz(atx - eyex, aty - eyey, atz - eyez);
    Vectorf x;                //x axis
    Vectorf y(upx, upy, upz); //(y axis)

    /* Viewing matrix
       x0        x1            x2            -eye Dot x
       y0        y1            y2            -eye Dot y
       z0        z1            z2            -eye Dot z
       0        0            0            1
    */

    /* Inverse of viewing matrix
       x0        y0            z0            eyex
       x1        y1            z1            eyey
       x2        y2            z2            eyez
       0        0            0            1
    */

    minusz.Normalize();

    // x = -z cross y
    x = minusz % y;
    x.Normalize();

    // Recompute y: y = x cross -z
    y = x % minusz;

    Matrixf view;

    view.IdentityMatrix();
    view.ele[0] = x.ele[0];
    view.ele[1] = y.ele[0];
    view.ele[2] = -minusz.ele[0];
    view.ele[4] = x.ele[1];
    view.ele[5] = y.ele[1];
    view.ele[6] = -minusz.ele[1];
    view.ele[8] = x.ele[2];
    view.ele[9] = y.ele[2];
    view.ele[10] = -minusz.ele[2];
    view.Translate(-eyex, -eyey, -eyez);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMultMatrixf(view);
}

void init()
{
    g_rotm.IdentityMatrix();
    g_world_rotm.IdentityMatrix();

    glShadeModel(GL_SMOOTH);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

    GLfloat pos[] = {1.5f, 1.0f, 100.0f, 1.0f};
    GLfloat dif[] = {1.0f, 1.0f, 1.0f, 1.0f};

    //    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
    //    glLightfv(GL_LIGHT0, GL_SPECULAR, dif);

    glMatrixMode(GL_MODELVIEW);
    g_cam.LookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    //gluLookAt(0.0, 0.0, 50.0, 0, 0, 0, 0, 1, 0);
    //look_at(0.0, 0.0, 50.0, 0, 0, 0, 0, 1, 1);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    //glEnable(GL_MULTISAMPLE);
    //glDisable(GL_MULTISAMPLE);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);

    glColorMaterial(GL_FRONT, GL_DIFFUSE);

    g_qobj = gluNewQuadric();
    gluQuadricDrawStyle(g_qobj, GLU_FILL);
    gluQuadricNormals(g_qobj, GLU_SMOOTH);
}

void clear()
{
    if (g_qobj)
    {
        gluDeleteQuadric(g_qobj);
        g_qobj = 0;
    }
}

enum ArrowType
{
    Cone,
    Ball
};

void draw_vector(Vectorf const &v, GLdouble len, GLdouble scale,
                 GLdouble r, GLdouble g, GLdouble b,
                 ArrowType arrow = Cone)
{
    Vectorf vv = v;
    vv.Normalize();
    Vectorf ax(0, 0, 1, 0);
    double angle = RADTODEG(acos(ax * vv));
    ax = ax % vv;
    //glEnable(GL_LIGHTING);
    //glEnable(GL_COLOR_MATERIAL);
    glPushMatrix();
    if (ax.Length2() < 0.00001)
    {
        if (angle > 90)
        {
            glRotated(180, 1, 0, 0);
        }
    }
    else
    {
        ax.Normalize();
        glRotated(angle, ax[0], ax[1], ax[2]);
    }
    GLdouble radius = g_asize * scale;
    glColor3d(r, g, b);
    gluCylinder(g_qobj, radius, radius, len, 20, 2);
    glTranslated(0, 0, len);
    glColor3d(r, g, b);
    switch (arrow)
    {
    case Cone:
        gluCylinder(g_qobj, radius * 4, 0.0, radius * 15, 20, 10);
        glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
        gluDisk(g_qobj, 0.0, radius * 4, 20, 1);
        break;

    case Ball:
        gluSphere(g_qobj, radius * 4, 20, 20);
        break;
    }

    glPopMatrix();
    //glDisable(GL_LIGHTING);
    //glDisable(GL_COLOR_MATERIAL);
}

void draw_axes(GLdouble len = 1.0, GLdouble scale = 1.0, ArrowType arrow = Cone)
{
    draw_vector(Vectorf(1.0f, 0.0f, 0.0f), len, scale, 1.0, 0.0, 0.0, arrow);
    draw_vector(Vectorf(0.0f, 1.0f, 0.0f), len, scale, 0.0, 1.0, 0.0, arrow);
    draw_vector(Vectorf(0.0f, 0.0f, 1.0f), len, scale, 0.0, 0.0, 1.0, arrow);
}

void draw_something()
{

    //glEnable(GL_COLOR_MATERIAL);
    glColor3d(1.0, 0.57, 0.04);
    glutSolidTeapot(0.5);
    //glDisable(GL_COLOR_MATERIAL);
}

void motion_function(int x, int y)
{
    if (g_left_button_down || g_right_button_down)
    {
        g_yrot += x - g_last_x;
        g_xrot += y - g_last_y;
        g_last_x = x;
        g_last_y = y;

        if (g_left_button_down)
        {
            g_trackball.Update((float)(2.0 * (x - g_viewport[0]) / g_viewport[2] - 1), (float)(2.0 * (g_viewport[3] - y - 1 - g_viewport[1]) / g_viewport[3] - 1));
            g_trackball.BuildRotMatrix(g_rotm);
        }
        else
        {
            g_world_trackball.Update((float)(2.0 * (x - g_viewport[0]) / g_viewport[2] - 1), (float)(2.0 * (g_viewport[3] - y - 1 - g_viewport[1]) / g_viewport[3] - 1));
            g_world_trackball.BuildRotMatrix(g_world_rotm);
        }
        glutPostRedisplay();
    }
}

void mouse_function(int button, int state, int x, int y)
{
    bool down = (state == GLUT_DOWN);

    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        g_left_button_down = down;
        break;
    case GLUT_MIDDLE_BUTTON:
        g_middle_button_down = down;
        break;
    case GLUT_RIGHT_BUTTON:
        g_right_button_down = down;
        break;
    }

    if (g_left_button_down)
    {
        g_trackball.Start((float)(2.0 * (x - g_viewport[0]) / g_viewport[2] - 1), (float)(2.0 * (g_viewport[3] - y - 1 - g_viewport[1]) / g_viewport[3] - 1));
    }

    if (g_right_button_down)
    {
        g_world_trackball.Start((float)(2.0 * (x - g_viewport[0]) / g_viewport[2] - 1), (float)(2.0 * (g_viewport[3] - y - 1 - g_viewport[1]) / g_viewport[3] - 1));
    }

    g_last_x = x;
    g_last_y = y;
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (g_eular_start)
    {
        g_rotm.IdentityMatrix();
        //g_rotm.RotateY(g_heading);
        //g_rotm.RotateZ(g_pitch);
        //g_rotm.RotateX(g_bank);

        Matrixf m1, m2, m3;

        m1.RotateYMatrix(g_heading);
        m2.RotateZMatrix(g_pitch);
        m3.RotateXMatrix(g_bank);

        g_rotm = m1 * m2 * m3;
        //g_rotm = m3 * m2 * m1;
    }

    //if (!g_left_button_down)
    //{
    //g_trackball.Update(g_trackball.GetUpdateQuat());
    //g_trackball.BuildRotMatrix(g_rotm);
    //}
    glEnable(GL_COLOR_MATERIAL);

    glPushMatrix();
    glMultMatrixf(g_world_rotm);
    glPushMatrix();
    draw_axes(1.3, 1.0);
    glPopMatrix();
    glPushMatrix();
    glMultMatrixf(g_rotm);
    draw_axes(0.7, 3.0);
    draw_something();
    glPopMatrix();
    glPopMatrix();

    glDisable(GL_COLOR_MATERIAL);

    glutSwapBuffers();

    if (g_heading < g_heading_stop)
    {
        g_heading += g_rotspeed; //g_heading_stop / g_rotsteps;
    }
    else if (g_pitch < g_pitch_stop)
    {
        g_pitch += g_rotspeed; //g_pitch_stop / g_rotsteps;
    }
    else if (g_bank < g_bank_stop)
    {
        g_bank += g_rotspeed; //g_bank_stop / g_rotsteps;
    }
    else
        g_eular_start = false;
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 's':
        g_heading = 0.0f;
        g_pitch = 0.0f;
        g_bank = 0.0f;
        g_eular_start = true;
        break;
    }
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glGetIntegerv(GL_VIEWPORT, g_viewport);

    //g_cam.Frustum(-10.0f, 10.0f, -10.0f, 10.0f, 10.0f, 150.0f);
    g_cam.Perspective(45.0f, float(w) / float(h), 1.0f, 100.0f);
    //g_cam.Ortho(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 100.0f);
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //glOrtho(-50.0, 50.0, -50.0, 50.0, 0.0, 150.0);
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    g_asize = 0.0075; //6.0 / sqrt((double)w*w+h*h);
}

int main(int argc, char **argv)
{
    g_qobj = 0;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Transform");
    init();
    glutMouseFunc(mouse_function);
    glutMotionFunc(motion_function);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    clear();
    return 0;
}
