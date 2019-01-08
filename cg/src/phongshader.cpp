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
#include <GL/glew.h>
#include "glinc.h"

#include "trackball.h"
#include "camera.h"

float g_light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
float g_light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
float g_light_position[] = { -0.2f, 0.2f, -2.6f, 1.0f };
float g_light_direction[] = { 0.0f - g_light_position[0],
                              0.0f - g_light_position[1],
                              -5.0f - g_light_position[2],
                              0.0f };

float g_material_ambient[]  = { 1.0f, 0.57f, 0.04f, 1.0f };
float g_material_diffuse[]  = { 1.0f, 0.57f, 0.04f, 1.0f };
float g_material_specular[]  = { 0.33f, 0.33f, 0.52f, 1.0f };
float g_material_emission[]  = { 0.0f, 0.0f, 0.0f, 0.0f };
float g_material_specular_power = 80.0f;

float g_color_background[] = { 0.0f, 0.0f, 0.0f, 1.0f };
float g_color_foreground[] = { 1.0f-g_color_background[0], 1.0f-g_color_background[1], 1.0f-g_color_background[2], 1.0f};

bool g_left_button_down = false;
bool g_middle_button_down = false;
bool g_right_button_down = false;
bool g_flat = false;
bool g_phong = true;
bool g_wireframe = false;

GLint g_viewport[4];

unsigned int g_which_obj = 0;
GLint g_refinement = 10;

TrackBallf g_trackball;
Matrixf g_rotm;
Cameraf g_cam;

GLuint g_vert_shader;
GLuint g_frag_shader;
GLuint g_program;

inline void set_material()
{
    GLenum face = GL_FRONT_AND_BACK;
    //glMaterialfv(face, GL_AMBIENT, g_material_ambient);
    glMaterialfv(face, GL_AMBIENT, g_material_diffuse);
    glMaterialfv(face, GL_DIFFUSE, g_material_diffuse);
    glMaterialfv(face, GL_SPECULAR, g_material_specular);
    glMaterialfv(face, GL_EMISSION, g_material_emission);
    glMaterialf(face, GL_SHININESS, g_material_specular_power);

    float backdiff[] = {0.3f, 0.1f, 1.0f, 1.0f };
    glMaterialfv(GL_BACK, GL_AMBIENT, backdiff);
    glMaterialfv(GL_BACK, GL_DIFFUSE, backdiff);
}

bool load_shader_source_from_file(GLuint shaderobj, char const *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        printf("ERROR: Cannot open file %s!\n", filename);
        return false;
    }

    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    GLchar *src = new GLchar[len+1];
    if (!src) {
        printf("ERROR: Cannot allocate memory for shader source code!");
        return false;
    }

    bool res = true;
    if (fread(src, sizeof(GLchar), len, fp)!=len) {
        printf("ERROR: Cannot load source code!");
        res = false;
    } else {
        src[len] = 0;
        glShaderSource(shaderobj, 1, (GLchar const **)&src, 0);
    }

    delete []src;
    return res;
}

bool compile_shader(GLuint shader)
{
    GLint len = 0;
    GLchar *log = 0;
    glCompileShader(shader);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

    if (len > 1) {
        log = new GLchar[len];
        glGetShaderInfoLog(shader, len, 0, log);
        log[len-1] = '\0';
        printf("%s\n", log);
        delete []log;
    } else printf("No compile information!\n");

    glGetShaderiv(shader, GL_COMPILE_STATUS, &len);
    if (len == GL_FALSE) return false;
    printf("Compile successful!\n");
    return true;
}

bool link_program(GLuint program)
{
    GLint len = 0;
    GLchar *log = 0;
    glLinkProgram(program);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

    if (len > 1) {
        log = new GLchar[len];
        glGetProgramInfoLog(program, len, 0, log);
        log[len-1] = '\0';
        printf("%s\n", log);
        delete []log;
    } else printf("No link information!\n");

    glGetProgramiv(program, GL_LINK_STATUS, &len);
    if (len == GL_FALSE) return false;
    printf("Link successful!\n");
    return true;
}

bool init_shaders()
{
    if (!GLEW_VERSION_2_0) {
            return false;
    }

    g_vert_shader = glCreateShader(GL_VERTEX_SHADER);
    g_frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

    if (!load_shader_source_from_file(g_vert_shader, "shaders/phong.vert")) return false;
    if (!load_shader_source_from_file(g_frag_shader, "shaders/phong.frag")) return false;

    if (!compile_shader(g_vert_shader) || !compile_shader(g_frag_shader)) return false;

    g_program = glCreateProgram();
    glAttachShader(g_program, g_vert_shader);
    glAttachShader(g_program, g_frag_shader);

    if (!link_program(g_program)) return false;
    glUseProgram(g_phong?g_program:0);

    return true;
}

void clean_shaders()
{
    glUseProgram(0);
    glDeleteProgram(g_program);
    glDeleteShader(g_vert_shader);
    glDeleteShader(g_frag_shader);
}

bool init()
{
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        return false;
        printf("Error: %s\n", glewGetErrorString(err));
    }

    if (!init_shaders()) return false;

    g_rotm.IdentityMatrix();

    set_material();
    glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading
    glClearColor(g_color_background[0], g_color_background[1], g_color_background[2], g_color_background[3]);               // Black Background
    glClearDepth(1.0f);                                 // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                             // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Really Nice Perspective Calculations

    //glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    GLenum light = GL_LIGHT0;
    glLightf(light, GL_CONSTANT_ATTENUATION,  1.0f);
    glLightf(light, GL_LINEAR_ATTENUATION,    0.0f);
    glLightf(light, GL_QUADRATIC_ATTENUATION, 0.0f);

    //glLightfv(light, GL_AMBIENT, g_light_ambient);        // Setup The Ambient Light
    glLightfv(light, GL_DIFFUSE, g_light_diffuse);      // Setup The Diffuse Light
    glLightfv(light, GL_SPECULAR, g_light_diffuse);
    glLightf(light, GL_SPOT_EXPONENT, 26.5f);
    //glLightf(light, GL_SPOT_CUTOFF, 15.5f);
    glLightf(light, GL_SPOT_CUTOFF, 45.5f);
    glLightfv(light, GL_POSITION, g_light_position);    // Position The Light
    glLightfv(light, GL_SPOT_DIRECTION, g_light_direction);
    glEnable(light);                                // Enable Light One

    //glDrawBuffer(GL_FRONT_AND_BACK);

    //float fcolor[4] = {0.8f, 0.8f, 0.8f, 1.0f};
    //glEnable(GL_FOG);
    //glFogf(GL_FOG_MODE, GL_EXP);
    //glFogf(GL_FOG_DENSITY, 0.1);
    //glFogfv(GL_FOG_COLOR, fcolor);

    //glPolygonMode(GL_FRONT, GL_LINE);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    glEnable(GL_MULTISAMPLE);

    return true;                                        // Initialization Went OK

}

void draw_something()
{
    glEnable(GL_LIGHTING);
    //glutSolidSphere(1.0, 100, 100);
    //if (g_wireframe) glutWireTorus(0.3, 1.0, 10, 10);
    //else glutSolidTorus(0.3, 1.0, 10, 10);
    switch (g_which_obj)
    {
    case 0:
        glFrontFace(GL_CW);
        if (g_wireframe) glutWireTeapot(1.0); else glutSolidTeapot(1.0);
        glFrontFace(GL_CCW);
        break;

    case 1:
        if (g_wireframe) glutWireTorus(0.3, 1.0, g_refinement, g_refinement); 
        else glutSolidTorus(0.3, 1.0, g_refinement, g_refinement);
        break;

    case 2:
        if (g_wireframe) glutWireSphere(1.0, g_refinement, g_refinement); 
        else glutSolidSphere(1.0, g_refinement, g_refinement);
        break;

    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!g_left_button_down) 
    {
        g_trackball.Update(g_trackball.GetUpdateQuat());
        g_trackball.BuildRotMatrix(g_rotm);
    }

    glPushMatrix();

    glMultMatrixf(g_rotm);
    GLint loc = glGetUniformLocation(g_program, "lightPos");
    glUniform4fv(loc, 1, g_light_position);
    //loc = glGetUniformLocationARB(g_program, "ambient");
    //glUniform3fvARB(loc, 1, g_material_ambient);
    //glUseProgramObjectARB(g_program);
    draw_something();

    glPopMatrix();

    glutSwapBuffers();

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

    case 'f':
        g_flat = !g_flat;
        if (g_flat) glShadeModel(GL_FLAT);
        else glShadeModel(GL_SMOOTH);
        break;

    case 's':
        g_phong = !g_phong;
        glUseProgram(g_phong?g_program:0);
        break;

    case '.':
        g_which_obj = (g_which_obj+1) % 3;
        break;

    case ',':
        g_which_obj = (g_which_obj+3-1) % 3;
        break;

    case '[':
        g_refinement -= 5;
        if (g_refinement<5) g_refinement = 5;
        break;

    case ']':
        g_refinement += 5;
        break;

    case 'p':
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.5f);
        break;

    case 'l':
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0f);
        break;

    default:
        break;
    }
}

void reshape(int width, int height)
{
    if (height==0) height=1;

    glViewport(0, 0, width, height);
    glGetIntegerv(GL_VIEWPORT, g_viewport);

    g_cam.Perspective(45.0f, (float)(width)/(float)(height), 1.1f, 100.0f);
    g_cam.LookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    //glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitDisplayString("double rgba depth samples=4");
    glutInitWindowSize(512,512);
    glutCreateWindow("Phong Shading");

    if (!init()) {
        clean_shaders();
        system("pause");
        return -1;
    }

    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();

    clean_shaders();
    return 0;
}
