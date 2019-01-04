#include <GL/glut.h>
#include <stdio.h>

int board[3][3]; /* amount of color for each square */

/* clear color value for every square on the board */
void init()
{
    int i, j;
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 3; ++j)
            board[i][j] = 0;
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void draw_squares(GLenum mode)
{
    GLuint i, j;
    for (i = 0; i < 3; ++i)
    {
        if (mode == GL_SELECT)
        {
            glPushName(i);
        }
        for (j = 0; j < 3; ++j)
        {
            if (mode == GL_SELECT)
                glPushName(j);
            glColor3f((GLfloat)i / 3.0, (GLfloat)j / 3.0, (GLfloat)board[i][j] / 3.0);
            glRecti(i, j, i + 1, j + 1);
            if (mode == GL_SELECT)
                glPopName();
        }
        if (mode == GL_SELECT)
        {
            glPopName();
        }
    }
}

/**
 * processHits prints out the contents of the 
 * selection array.
 **/
void process_hits(GLint hits, GLuint buffer[])
{
    int i;
    unsigned int j;
    GLuint ii, jj, names, *ptr;

    printf("=========================================\n");
    printf(" hits = %d\n", hits);
    ptr = buffer;

    for (i = 0; i < hits; ++i)
    {
        names = *ptr;
        printf(" number of names for this hit = %d\n", names);
        ptr++;
        printf(" z1 is %g; ", (float)*ptr / 0x7FFFFFFF);
        ptr++;
        printf(" z2 is %g\n", (float)*ptr / 0x7FFFFFFF);
        ptr++;
        printf("  names are: ");
        for (j = 0; j < names; ++j)
        {
            printf("%d ", *ptr);
            if (j == 0)
                ii = *ptr;
            else if (j == 1)
                jj = *ptr;
            ptr++;
        }
        printf("\n");
        board[ii][jj] = (board[ii][jj] + 1) % 3;
    }
}

#define BUFSIZE 512

void pick_squares(int button, int state, int x, int y)
{
    GLuint selectBuf[BUFSIZE];
    GLint hits;
    GLint viewport[4];

    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
        return;

    glGetIntegerv(GL_VIEWPORT, viewport);

    glSelectBuffer(BUFSIZE, selectBuf);
    glRenderMode(GL_SELECT);
    glInitNames();
    //glPushName(0);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    /* create 5x5 pixel picking region near cursor location */
    gluPickMatrix((GLdouble)x, (GLdouble)(viewport[3] - y), 5.0, 5.0, viewport);
    gluOrtho2D(0.0, 3.0, 0.0, 3.0);
    draw_squares(GL_SELECT);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glFlush();

    hits = glRenderMode(GL_RENDER);
    process_hits(hits, selectBuf);
    glutPostRedisplay();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    draw_squares(GL_RENDER);
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 3.0, 0.0, 3.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Pick Square");
    init();
    glutMouseFunc(pick_squares);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}