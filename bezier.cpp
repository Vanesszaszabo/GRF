#define _USE_MATH_DEFINES 

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h> 

struct Point {
    float x, y;
    bool visible;
    Point(float _x, float _y) : x(_x), y(_y), visible(true) {}
};

static std::vector<Point> points;
static bool showPoints = true;
static float pointRadius = 1.0;

void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Görbék rajzolása
    if (points.size() >= 4) {
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINE_STRIP);

        Point p0 = points[0];
        Point p1 = points[1];
        Point p2 = points[2];
        Point p3 = points[3];

        // Az elsõ görbe megrajzolása
        for (float t = 0; t <= 1; t += 0.01) {
            float x = pow(1 - t, 3) * p0.x +
                3 * t * pow(1 - t, 2) * p1.x +
                3 * pow(t, 2) * (1 - t) * p2.x +
                pow(t, 3) * p3.x;

            float y = pow(1 - t, 3) * p0.y +
                3 * t * pow(1 - t, 2) * p1.y +
                3 * pow(t, 2) * (1 - t) * p2.y +
                pow(t, 3) * p3.y;

            glVertex2f(x, y);
        }

        for (size_t i = 4; i < points.size(); i += 3) {
            if (i + 2 >= points.size()) break;

            p0 = p3;
            p1 = points[i];
            p2 = points[i + 1];
            p3 = points[i + 2];

            for (float t = 0; t <= 1; t += 0.01) {
                float x = pow(1 - t, 3) * p0.x +
                    3 * t * pow(1 - t, 2) * p1.x +
                    3 * pow(t, 2) * (1 - t) * p2.x +
                    pow(t, 3) * p3.x;

                float y = pow(1 - t, 3) * p0.y +
                    3 * t * pow(1 - t, 2) * p1.y +
                    3 * pow(t, 2) * (1 - t) * p2.y +
                    pow(t, 3) * p3.y;

                glVertex2f(x, y);
            }
        }
        glEnd();
    }

    if (showPoints) {
        // Kontrollpontok rajzolása
        glColor3f(1.0, 0.0, 0.0);
        for (const auto& point : points) {
            if (point.visible) {
                glBegin(GL_POLYGON);
                for (int i = 0; i < 360; i++) {
                    float angle = i * M_PI / 180;
                    glVertex2f(point.x + cos(angle) * pointRadius,
                        point.y + sin(angle) * pointRadius);
                }
                glEnd();
            }
        }
    }
    else {
        // Irányvektorok rajzolása
        if (points.size() >= 4) {
            for (size_t i = 0; i < points.size() - 3; i += 3) {
                // Kezdõpont -> elsõ irányvektor
                glColor3f(0.0, 1.0, 0.0); // Zöld szín az elsõ irányvektornak
                glBegin(GL_LINES);
                glVertex2f(points[i].x, points[i].y);
                glVertex2f(points[i + 1].x, points[i + 1].y);
                glEnd();

                // Végpont -> második irányvektor
                glColor3f(0.0, 0.0, 1.0); // Kék szín a második irányvektornak
                glBegin(GL_LINES);
                glVertex2f(points[i + 3].x, points[i + 3].y);
                glVertex2f(points[i + 2].x, points[i + 2].y);
                glEnd();

                // Kezdõ- és végpontok kis körökkel jelölve
                glColor3f(1.0, 0.0, 0.0); // Piros szín a pontoknak

                // Kezdõpont
                glBegin(GL_POLYGON);
                for (int j = 0; j < 360; j++) {
                    float angle = j * M_PI / 180;
                    glVertex2f(points[i].x + cos(angle) * pointRadius,
                        points[i].y + sin(angle) * pointRadius);
                }
                glEnd();

                // Végpont
                glBegin(GL_POLYGON);
                for (int j = 0; j < 360; j++) {
                    float angle = j * M_PI / 180;
                    glVertex2f(points[i + 3].x + cos(angle) * pointRadius,
                        points[i + 3].y + sin(angle) * pointRadius);
                }
                glEnd();
            }
        }
    }

    glFlush();
}


void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyInput(unsigned char key, int x, int y)
{
    switch (key) {
    case 27: // ESC
        exit(0);
        break;
    case ' ':
        showPoints = !showPoints;
        glutPostRedisplay();
        break;
    case 'c':
        if (points.size() >= 4) {
            // Az utolsó pont és az elsõ pont közötti irányítópontok kiszámítása
            float lastX = points.back().x;
            float lastY = points.back().y;
            float firstX = points[0].x;
            float firstY = points[0].y;

            // Két irányítópont az utolsó és elsõ pont között
            float control1X = lastX + (firstX - lastX) * 0.33f;
            float control1Y = lastY + (firstY - lastY) * 0.33f;
            float control2X = lastX + (firstX - lastX) * 0.66f;
            float control2Y = lastY + (firstY - lastY) * 0.66f;

            // Irányítópontok hozzáadása
            points.emplace_back(control1X, control1Y);
            points.emplace_back(control2X, control2Y);
            // Az elsõ pont hozzáadása zárópontként
            points.emplace_back(firstX, firstY);

            glutPostRedisplay();
        }
        break;
    }
}


void mouseInput(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float wx = (float)x / glutGet(GLUT_WINDOW_WIDTH) * 100.0;
        float wy = (float)(glutGet(GLUT_WINDOW_HEIGHT) - y) / glutGet(GLUT_WINDOW_HEIGHT) * 100.0;
        points.emplace_back(wx, wy);
        glutPostRedisplay();
    }
}

void printInteraction(void)
{
    std::cout << "Interaction:" << std::endl;
    std::cout << "Left click: Add control point" << std::endl;
    std::cout << "Space: Toggle point visibility" << std::endl;
    std::cout << "C: Close curve" << std::endl;
    std::cout << "ESC: Exit" << std::endl;
}

int main(int argc, char** argv)
{
    printInteraction();
    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bezier Curves");

    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutMouseFunc(mouseInput);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
    return 0;
}
