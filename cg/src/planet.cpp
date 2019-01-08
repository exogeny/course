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
#include "glinc.h"
#include "FreeImage.h"
#include "trackball.h"
#include "quaternion.h"
#include "camera.h"

int g_window_width = 512;
int g_window_height = 512;
int g_last_x = 0;
int g_last_y = 0;

bool g_light = true;
bool g_rotate = true;
bool g_fullscreen = false;
bool g_left_button_down = false;
bool g_middle_button_down = false;
bool g_right_button_down = false;

float g_spin_angle = 0.01f;
float g_earth_angle = 0.0f;
float g_cloud_angle = 0.0f;

GLuint g_planet_texture_id;
GLuint g_cloud_texture_id;

GLfloat g_z=4.0f;       // Depth Into The Screen
GLfloat const Z_STEP = 0.05f;

GLclampf g_color_background[] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat g_light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat g_light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat g_light_position[] = { 0.0f, 0.0f, 4.0f, 1.0f };
GLfloat g_light_direction[] = { 0.0f, 0.0f, -1.0f, 1.0f };

GLfloat g_material_ambient[]  = { 0.75f, 0.75f, 0.75f, 1.0f };
GLfloat g_material_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat g_material_specular[]  = { 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat g_material_emission[]  = { 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat g_material_specular_power = 100.0f;

GLint g_viewport[4];
TrackBallf g_trackball(0.8);
Matrixf g_rotm;
Cameraf g_cam;

GLUquadric *g_qobj;

void set_material()
{
    GLenum face = GL_FRONT_AND_BACK;
    glMaterialfv(face, GL_AMBIENT, g_material_ambient);
    glMaterialfv(face, GL_DIFFUSE, g_material_diffuse);
    glMaterialfv(face, GL_SPECULAR, g_material_specular);
    glMaterialfv(face, GL_EMISSION, g_material_emission);
    glMaterialf(face, GL_SHININESS, g_material_specular_power);
}

FIBITMAP* load_image(char const *filename, int flag = 0)
{
    FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(filename, 0);

    if (fif == FIF_UNKNOWN) fif = FreeImage_GetFIFFromFilename(filename);
    if (fif == FIF_UNKNOWN) return false;

    return FreeImage_Load(fif, filename, flag); 
}

GLuint load_texture(char const *imgfile)
{
    if (!imgfile) return 0;

    FIBITMAP *tdib = load_image(imgfile);
    if (!tdib) return 0;

    //bool status(false);
    unsigned int bpp = FreeImage_GetBPP(tdib);

    FIBITMAP *dib = tdib;
    if (bpp != 24 && bpp != 32) dib = FreeImage_ConvertTo24Bits(tdib);

    BYTE *bits = FreeImage_GetBits(dib);
    unsigned int width = FreeImage_GetWidth(dib);
    unsigned int height = FreeImage_GetHeight(dib);

    GLenum format = FREEIMAGE_COLORORDER==FREEIMAGE_COLORORDER_BGR ? GL_BGR : GL_RGB;
    if (bpp == 32) format = FREEIMAGE_COLORORDER==FREEIMAGE_COLORORDER_BGR ? GL_BGRA : GL_RGBA;

    RGBQUAD *pal = FreeImage_GetPalette(dib);

    GLuint tex_id = 0;
    if (bits!=0 && width>0 && height>0) {
        //status = true;                                    // Set The Status To TRUE
        glGenTextures(1, &tex_id);                  // Create Three Textures

        // Create Nearest Filtered Texture
        //glBindTexture(GL_TEXTURE_2D, g_texture_id);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, bits);

        // Create Linear Filtered Texture
        //glBindTexture(GL_TEXTURE_2D, g_texture_id);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, bits);

        // Create MipMapped Texture
        glBindTexture(GL_TEXTURE_2D, tex_id);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
        gluBuild2DMipmaps(GL_TEXTURE_2D, (bpp==32 ? GL_RGBA : GL_RGB), width, height, format, GL_UNSIGNED_BYTE, bits);
    }

    if (bpp != 24 && bpp != 32) FreeImage_Unload(dib);

    FreeImage_Unload(tdib);

    return tex_id;                                      // Return The Status
}

bool load_textures()
{
    g_planet_texture_id = load_texture("data/planet/earthmap.jpg");
    if (g_planet_texture_id == 0) return false;

    g_cloud_texture_id = load_texture("data/planet/earthclouds.png");
    if (g_cloud_texture_id == 0) return false;

    return true;
}

bool init() 
{
    if (!load_textures()) {
        return false;
    }

    glEnable(GL_TEXTURE_2D);                            // Enable Texture Mapping
    glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading
    glClearColor(g_color_background[0], g_color_background[1], g_color_background[2], g_color_background[3]);               // Black Background
    glClearDepth(1.0f);                                 // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                             // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Really Nice Perspective Calculations

    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION,  1.0f);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION,    0.0f);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0f);

    //glLightfv(GL_LIGHT1, GL_AMBIENT, g_light_ambient);        // Setup The Ambient Light
    glLightfv(GL_LIGHT1, GL_DIFFUSE, g_light_diffuse);      // Setup The Diffuse Light
    glLightfv(GL_LIGHT1, GL_SPECULAR, g_light_diffuse);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0f);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0f);
    glLightfv(GL_LIGHT1, GL_POSITION, g_light_position);    // Position The Light
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, g_light_direction);
    glEnable(GL_LIGHT1);                                // Enable Light One

    set_material();

    g_qobj = gluNewQuadric();
    gluQuadricDrawStyle(g_qobj, GLU_FILL);
    gluQuadricNormals(g_qobj, GLU_SMOOTH);
    gluQuadricTexture(g_qobj, GL_TRUE);

    g_rotm.IdentityMatrix();
    g_cam.LookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    Vectorf vv(-0.5, 1, 0.8, 0);
    vv.Normalize();
    Vectorf ax(0, 0, 1, 0);
    double angle = acos(ax * vv);
    ax = ax % vv;
    Quaternionf dr;
    dr.AxisRadToQuat(ax[0], ax[1], ax[2], angle);
    g_trackball.Update(dr);
    g_trackball.BuildRotMatrix(g_rotm);

    return true;                                        // Initialization Went OK
}

void clear()
{
    if (g_qobj) {
        gluDeleteQuadric(g_qobj);
        g_qobj = 0;
    }
}

void resize(int width, int height)
{
    if (height==0)                                      // Prevent A Divide By Zero By
    {
        height=1;                                       // Making Height Equal One
    }

    glViewport(0, 0, width, height);
    glGetIntegerv(GL_VIEWPORT, g_viewport);

    g_cam.Perspective(45.0f, (float)(width)/(float)(height), 1.1f, 100.0f);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
    g_cam.LookAt(0.0f, 0.0f, g_z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);


    glMultMatrixf(g_rotm);

    glPushMatrix();
    //glTranslatef(0.0f, 0.0f, g_z);

    if (g_light) glEnable(GL_LIGHTING);
    else glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glRotatef(g_earth_angle, 0.0f, 0.0f, 1.0f);
    if (g_rotate) {
        g_earth_angle += g_spin_angle;
    }

    glBindTexture(GL_TEXTURE_2D, g_planet_texture_id);
    gluSphere(g_qobj, 1.0, 50, 50);

    glPopMatrix();

    glPushMatrix();
    glRotatef(g_cloud_angle, 0.0f, 0.0f, 1.0f);
    if (g_rotate) {
        g_cloud_angle += g_spin_angle*1.5f;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindTexture(GL_TEXTURE_2D, g_cloud_texture_id);
    gluSphere(g_qobj, 1.03, 50, 50);

    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;


    case 'l':
        g_light = !g_light;
        break;

    case 'r':
        g_rotate = !g_rotate;
        break;

    case 's':
        g_light = false;
        break;

    case '.':
        g_spin_angle *= 2.0f;
        break;

    case ',':
        if (g_spin_angle <= 0.01f) g_spin_angle = 0.01f;
        else g_spin_angle *= 0.5f;
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
        g_z -= Z_STEP;
        break;

    case GLUT_KEY_DOWN:
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
        else glutReshapeWindow(g_window_width, g_window_height);
        break;
    }
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

    if (g_left_button_down) {
        g_trackball.Start((float)(2.0*(x-g_viewport[0])/g_viewport[2]-1), (float)(2.0*(g_viewport[3]-y-1-g_viewport[1])/g_viewport[3]-1));
    }

    g_last_x = x;
    g_last_y = y;   
}

int main(int argc, char *argv[])
{
    g_qobj = 0;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE); 
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(g_window_width, g_window_height); 
    glutCreateWindow( "Texture 2D" ); 
    if (!init()) exit(-1);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special_keys);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutIdleFunc(display);
    glutMainLoop();

    clear();

    return 0;
}
