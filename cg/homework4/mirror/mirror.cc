#include <stdlib.h>
#include <GL/freeglut.h>
#include <GL/glext.h>

#include "camera.h"
#include "trackball.h"
#include "FreeImage.h"

struct Mirror {
    Mirror(Vectorf const &normalVector,   // normal vector
           Vectorf const &centerPoint,    // center point
           Vectorf const &halfDiagLB,     // left-bottom diagonal vector
           Vectorf const &halfDiagRB,     // right-bottom diagonal vector
           float hl                       // half length of diagonal
           )
           : normal(normalVector), center(centerPoint) {

               normal.Normalize();

               normal[3] = 0;
               center[3] = 1;

               Vectorf hdlb(halfDiagLB), hdrb(halfDiagRB);
               hdlb.Normalize();
               hdrb.Normalize();
               hdlb *= abs(hl);
               hdrb *= abs(hl);
               hdlb[3] = 0;
               hdrb[3] = 0;

               vert_lb = center + hdlb;
               vert_rb = center + hdrb;
               vert_rt = center - hdlb;
               vert_lt = center - hdrb;
    }

    Vectorf normal;
    Vectorf center;
    Vectorf vert_lb; // left-bottom vertex
    Vectorf vert_rb; // right-bottom vertex
    Vectorf vert_rt; // right-top vertex
    Vectorf vert_lt; // left-top vertex
};

bool g_left_button_down = false;
bool g_middle_button_down = false;
bool g_right_button_down = false;
int g_last_x = 0;
int g_last_y = 0;

GLuint g_texture_id;
GLint g_viewport[4];
GLdouble g_clip_plane[4];
TrackBallf g_trackball;
Matrixf g_rotm;
Matrixf g_mirm;
Cameraf g_cam;

Mirror g_mirror(Vectorf(0.0f, 1.0f, 0.0f, 0.0f),
                Vectorf(0.0f, -1.2f, 0.0f, 1.0f), 
                Vectorf(-1.0f, 0.0f, 1.0f, 0.0f), 
                Vectorf(1.0f, 0.0f, 1.0f, 0.0f),  
                3.0f);


void compute_mirror_matrix(Vectorf const &n, Vectorf const &pt, Matrixf &m)
{
    Vectorf p = n;

    p.Normalize();
    p[3] = - p * pt;

    m[0] = 1 - 2*p[0]*p[0];
    m[1] = -2*p[0]*p[1];
    m[2] = -2*p[0]*p[2];
    m[3] = 0;

    m[4] = m[1];
    m[5] = 1 - 2*p[1]*p[1];
    m[6] = -2*p[1]*p[2];
    m[7] = 0;

    m[8] = m[2];
    m[9] = m[6];
    m[10] = 1 - 2*p[2]*p[2];
    m[11] = 0;

    m[12] = -2*p[0]*p[3];
    m[13] = -2*p[1]*p[3];
    m[14] = -2*p[2]*p[3];
    m[15] = 1;
}

bool load_texture(char const *filename, int flag)
{
    FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(filename, 0);

    if (fif == FIF_UNKNOWN) fif = FreeImage_GetFIFFromFilename(filename);
    if (fif == FIF_UNKNOWN) return false;

    FIBITMAP *dib = FreeImage_Load(fif, filename, flag);
    if (!dib) return false;

    BYTE *bits = FreeImage_GetBits(dib);
    unsigned int width = FreeImage_GetWidth(dib);
    unsigned int height = FreeImage_GetHeight(dib);
    if (bits==0 || width==0 || height==0) return false;

    glGenTextures(1, &g_texture_id);
    glBindTexture(GL_TEXTURE_2D, g_texture_id);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, bits);

    FreeImage_Unload(dib);

    return true;
}

bool init()
{
    g_texture_id = 0;

    if (!load_texture("Data/marble.jpg", 0)) return false;

    g_rotm.IdentityMatrix();
    compute_mirror_matrix(g_mirror.normal, g_mirror.center, g_mirm);

    g_clip_plane[0] = -g_mirror.normal[0];
    g_clip_plane[1] = -g_mirror.normal[1];
    g_clip_plane[2] = -g_mirror.normal[2];
    g_clip_plane[3] =  g_mirror.normal * g_mirror.center;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0);
    glClearStencil(0);

    GLfloat pos[] = { 0.0f, 0.0f, 100.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);

    return true;


}

void clear()
{
    if (g_texture_id) {
        glDeleteTextures(1, &g_texture_id);
        g_texture_id = 0;
    }
}


void reshape(int w, int h)
{
    if (h==0) h=1;
    glViewport(0, 0, w, h);
    glGetIntegerv(GL_VIEWPORT, g_viewport);

    g_cam.Perspective(45.0f, (float)w / (float)h, 1.5f, 100.0f);
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


void draw_mirror(Mirror const &mirror)
{
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, g_texture_id);
    glBegin(GL_QUADS);
    glNormal3fv(mirror.normal);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3fv(mirror.vert_lb);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3fv(mirror.vert_rb);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3fv(mirror.vert_rt);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3fv(mirror.vert_lt);
    glEnd();
    //glDisable(GL_TEXTURE_2D);
}




// for debug
void draw_mirror_frame(Mirror const &mirror)
{
    glDisable(GL_LIGHTING);
    glBegin(GL_LINE_LOOP);
    glVertex3fv(mirror.vert_lb);
    glVertex3fv(mirror.vert_rb);
    glVertex3fv(mirror.vert_rt);
    glVertex3fv(mirror.vert_lt);
    glEnd();
    glEnable(GL_LIGHTING);
}

void draw_scene()
{
    glColor3f(0.93f, 0.1f, 0.56f);
    glutSolidTeapot(1.0);

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    g_cam.LookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glMultMatrixf(g_rotm);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
    draw_scene();
    //draw_mirror_frame(g_mirror);

    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilFunc(GL_ALWAYS, 1, ~0);
    glColorMask(0, 0, 0, 0);
    draw_mirror(g_mirror);

    glDepthRange(1, 1);
    glDepthFunc(GL_ALWAYS);
    glStencilFunc(GL_EQUAL, 1, ~0);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    draw_mirror(g_mirror);

    glDepthRange(0, 1);
    glDepthFunc(GL_LESS);
    glColorMask(1, 1, 1, 1);

    glPushMatrix();

    glClipPlane(GL_CLIP_PLANE0, g_clip_plane);
    glEnable(GL_CLIP_PLANE0);
    glMultMatrixf(g_mirm);
    glCullFace(GL_FRONT);
    draw_scene();
    glCullFace(GL_BACK);
    glDisable(GL_CLIP_PLANE0);

    glPopMatrix();

/*
    glColorMask(0, 0, 0, 0);
    glStencilOp(GL_KEEP, GL_KEEP, GL_ZERO);
    glDepthFunc(GL_ALWAYS);
    draw_mirror(g_mirror);
    glDepthFunc(GL_LESS);
    glColorMask(1, 1, 1, 1);
*/
    glDisable(GL_STENCIL_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    glColor3f(0.9f, 0.9f, 0.9f);
    glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, g_texture_id);
    draw_mirror(g_mirror);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    glutSwapBuffers();

}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(512, 512);
    glutInitDisplayString("samples=4 stencil>=3 rgb double depth");
    glutCreateWindow("Mirror");

    if (!init()) return -1;

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutMainLoop();

    clear();

    return 0;
}