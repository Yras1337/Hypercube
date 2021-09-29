#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "Vectorf.h"
#include "Matrix.h"
float W = 900;
float H = 900;
float getX;
float Pi = 3.14159265359;
float Angle = 0;
float Deg = Pi / 180.0f;
std::vector < Vector4f > points;
std::vector < Vector3f > projected2d;
void InitVector() {
    points.push_back(Vector4f(-1, -1, -1, 1));
    points.push_back(Vector4f(1, -1, -1, 1));
    points.push_back(Vector4f(1, 1, -1, 1));
    points.push_back(Vector4f(-1, 1, -1, 1));
    points.push_back(Vector4f(-1, -1, 1, 1));
    points.push_back(Vector4f(1, -1, 1, 1));
    points.push_back(Vector4f(1, 1, 1, 1));
    points.push_back(Vector4f(-1, 1, 1, 1));
    points.push_back(Vector4f(-1, -1, -1, -1));
    points.push_back(Vector4f(1, -1, -1, -1));
    points.push_back(Vector4f(1, 1, -1, -1));
    points.push_back(Vector4f(-1, 1, -1, -1));
    points.push_back(Vector4f(-1, -1, 1, -1));
    points.push_back(Vector4f(1, -1, 1, -1));
    points.push_back(Vector4f(1, 1, 1, -1));
    points.push_back(Vector4f(-1, 1, 1, -1));
    for (int i = 0; i < 16; i++) {
        projected2d.push_back(Vector3f(0, 0, 0));
    }
}
void connect(int offset, int i, int j, std::vector < Vector3f > points) {
    Vector3f a = points[i + offset];
    Vector3f b = points[j + offset];
    glVertex2d(a.x, a.y);
    glVertex2d(b.x, b.y);
}
std::vector < std::vector < float > > rotationZW, rotationYZ, projection;
void InitMatrix(float angle) {
    rotationZW = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, cos(Angle), -sin(Angle)},
        {0, 0, sin(Angle), cos(Angle)}
    };
    rotationYZ = {
        {1, 0, 0, 0},
        {0, cos(1.13446f), -sin(1.13446f), 0 },
        {0, sin(1.13446f), cos(1.13446f), 0},
        {0, 0, 0, 1}
    };
}
    
void draw() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.412f, 0.412f, 0.412f);
    glPointSize(7.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < 16; i++) {
        InitMatrix(Angle);
        Vector4f v = points[i];
        Vector4f rotated = matmul(rotationZW, v, true);
        rotated = matmul(rotationYZ, rotated, true);
        float distance = 2;
        float w = 1 / (distance - rotated.w);
        projection = {
          {w, 0, 0, 0},
          {0, w, 0, 0},
          {0, 0, 0, 0}
        };
        Vector3f projected = matmul(projection, rotated);
        projected.x *= 0.25f;
        projected.y *= 0.25f;
        projected2d[i] = projected;
        glVertex2d(projected.x, projected.y);
    }
    glEnd();
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 4; i++) {
        // первый куб
        connect(0, i, (i + 1) % 4, projected2d);
        connect(0, i + 4, ((i + 1) % 4) + 4, projected2d);
        connect(0, i, i + 4, projected2d);
        // второй куб
        connect(8, i, (i + 1) % 4, projected2d);
        connect(8, i + 4, ((i + 1) % 4) + 4, projected2d);
        connect(8, i, i + 4, projected2d);
    }
    for (int i = 0; i < 8; i++) {
        // соединение кубов
        connect(0, i, i + 8, projected2d);
    }
    Angle += Deg;
    if (Angle > Pi) {
        Angle -= Pi;
    }
    glEnd();
    glutSwapBuffers();
}
void timf(int value) {
    draw();
	glutTimerFunc(10, timf, 0);
}
int main(int argc, char** argv) {
    InitVector();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_ALPHA | GLUT_RGBA);
	glutInitWindowSize(int(W), int(H));
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Window");
	glClearColor(0, 0, 0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); 
    glFrustum(0, W, H, 0, -1, 1);
	glutDisplayFunc(draw);
	glutTimerFunc(10, timf, 0);
	glutMainLoop();
	return 0;
}