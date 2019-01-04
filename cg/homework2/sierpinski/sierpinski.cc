#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>

template <typename T>
struct _2d_point_type
{
    union {
        struct
        {
            T x, y;
        };
        T coord[2];
    };
};

typedef _2d_point_type<GLfloat> Point2f;

void display()
{
    Point2f vertices[3] = {{
                               0.0f,
                               0.0f,
                           },
                           {250.0f, 500.0f},
                           {500.0f, 0.0f}};
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
    for (int i = 0; i < 55000; ++i)
    {
        int j = rand() % 3;
        //GLfloat r = (rand() & 0xff) / 255.0f;
        //GLfloat g = 1.0f;//(rand() & 0xff) / 255.0f;
        //GLfloat b = 1.0f;//(rand() & 0xff) / 255.0f;

        p.x = (p.x + vertices[j].x) / 2.0f;
        p.y = (p.y + vertices[j].y) / 2.0f;

        //glColor3f(r, g, b);
        //if (i<100) continue;
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_POINTS);
        glVertex2fv(p.coord);
        glEnd();
    }
    glFlush();
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
    init();
    glutMainLoop();
    return 0;
}