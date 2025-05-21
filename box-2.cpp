/////////////////////////////////          
// box.cpp
//
// This program draws a wire box.
//
// Sumanta Guha.
/////////////////////////////////
#define _USE_MATH_DEFINES 

#include <cstdlib>
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

// Globals.
float scaleBox = 5.0;
int isWireFrame = 1;
int isCube = 1;
int sphereDepth = 8;
static int isAnimate = 0; // Animated?
static int animationPeriod = 50; // Time interval between frames.
static float boxAngle = 0.0; // Angle of rotation.

static float cameraDistance = 15.0;
static double angleXZ = 0.0; // X és Z tengely menti forgatás szöge
static double m = 0.0; // fel - le nyilak

GLfloat  lookAtX = 0.0f, lookAtY = 0.0f, lookAtZ = -cameraDistance;  // Hova nézünk


// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);

	double eyeX = lookAtX + cameraDistance * sin(angleXZ * M_PI / 180.0);
	double eyeZ = lookAtZ + cameraDistance * cos(angleXZ * M_PI / 180.0);
	gluLookAt(eyeX, m, eyeZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);

	/* Milyen alakzatok vannak GENNYÓÓÓÓÓÓÓÓÓÓÓÓ /solid/wire
	Cube: glutWireCube
	Sphere: glutWireSphere
	Torus: glutWireTorus
	Dodecahedron: glutWireDodeCahedron
	Octahedron: glutWireOctahedron
	Tetrahedron: glutWireTetraHedron
	Icosahedron: glutWireIcosahedron
	Teapot: glutWireTeapot
	*/

	// Ez a Kék doboz, elõször ezt hozzuk létre
	///////////////////////////////////////////// Kék doboz /////////////////////////////////////////////
	
	glPushMatrix();
	glTranslatef(0.0, 0.0, -cameraDistance); // Standard eltolás Frustum miatt
	glRotatef(30.0, 0.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	if (isWireFrame == 0) {
		//isCube == 1 ? glutWireCube(scaleBox) : glutWireSphere(scaleBox/2, sphereDepth, sphereDepth);  // Box vs Sphere
		switch (isCube)
		{
		case 0:
			glutWireCube(scaleBox);
			break;
		case 1:
			glutWireSphere(scaleBox / 2, sphereDepth, sphereDepth);
			break;
		case 2:
			glutWireTorus(scaleBox / 2, scaleBox * 0.75, sphereDepth, sphereDepth);
			break;
		case 3:
			glutWireCone(scaleBox / 2, scaleBox, sphereDepth, sphereDepth);
			break;
		case 4:
			glutWireCylinder(scaleBox / 2, scaleBox, sphereDepth, sphereDepth);
			break;
		default:
			break;
		}
		
	}
	else {
		//isCube == 1 ? glutSolidCube(scaleBox) : glutSolidSphere(scaleBox/2, sphereDepth, sphereDepth);  // Box vs Sphere
		switch (isCube)
		{
		case 0:
			glutSolidCube(scaleBox);
			break;
		case 1:
			glutSolidSphere(scaleBox / 2, sphereDepth, sphereDepth);
			break;
		case 2:
			glutSolidTorus(scaleBox / 2, scaleBox * 0.75, sphereDepth, sphereDepth);
			break;
		case 3:
			glutSolidCone(scaleBox / 2, scaleBox, sphereDepth, sphereDepth);
			break;
		case 4:
			glutSolidCylinder(scaleBox / 2, scaleBox, sphereDepth, sphereDepth);
			break;
		default:
			break;
		}
	}
	glPopMatrix();

	///////////////////////////////////////////// Kék doboz /////////////////////////////////////////////

	///////////////////////////////////////////// Piros doboz /////////////////////////////////////////////
	
	glPushMatrix();
	glTranslatef(0.0, 0.0, -cameraDistance);	// Standard eltolás Frustum miatt
	glTranslatef(scaleBox / 2, scaleBox, scaleBox * -1);
	glRotatef(boxAngle + 60.0, 0.0, 1.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	if (isWireFrame == 0) {
		//isCube == 1 ? glutWireCube(scaleBox) : glutWireSphere(scaleBox/2, sphereDepth, sphereDepth);  // Box vs Sphere
		switch (isCube)
		{
		case 0:
			glutWireCube(scaleBox);
			break;
		case 1:
			glutWireSphere(scaleBox / 2, sphereDepth, sphereDepth);
			break;
		case 2:
			glutWireTorus(scaleBox / 2, scaleBox * 0.75, sphereDepth, sphereDepth);
			break;
		case 3:
			glutWireCone(scaleBox / 2, scaleBox, sphereDepth, sphereDepth);
			break;
		case 4:
			glutWireCylinder(scaleBox / 2, scaleBox, sphereDepth, sphereDepth);
			break;
		default:
			break;
		}

	}
	else {
		//isCube == 1 ? glutSolidCube(scaleBox) : glutSolidSphere(scaleBox/2, sphereDepth, sphereDepth);  // Box vs Sphere
		switch (isCube)
		{
		case 0:
			glutSolidCube(scaleBox);
			break;
		case 1:
			glutSolidSphere(scaleBox / 2, sphereDepth, sphereDepth);
			break;
		case 2:
			glutSolidTorus(scaleBox / 2, scaleBox * 0.75, sphereDepth, sphereDepth);
			break;
		case 3:
			glutSolidCone(scaleBox / 2, scaleBox, sphereDepth, sphereDepth);
			break;
		case 4:
			glutSolidCylinder(scaleBox / 2, scaleBox, sphereDepth, sphereDepth);
			break;
		default:
			break;
		}
	}

	
	glPopMatrix();
	///////////////////////////////////////////// Piros doboz /////////////////////////////////////////////

	glFlush();
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
}

void increaseAngle(void)
{
	boxAngle += 5.0;
	if (boxAngle > 360.0) boxAngle -= 360.0;
	glutPostRedisplay();
}

void animate(int value)
{
	if (isAnimate)
	{
		increaseAngle();

		glutPostRedisplay();
		glutTimerFunc(animationPeriod, animate, 1);
	}
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
	if (key == GLUT_KEY_UP) { if (m + 5 >= 50) m = 50; else m += 5; }
	if (key == GLUT_KEY_DOWN) { if (m - 5 <= -50) m = -50; else m -= 5; }
	glutPostRedisplay();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;

	case 'q':
		isWireFrame = (isWireFrame + 1) % 2;
		glutPostRedisplay();
		break;
	case 'e':
		isCube = (isCube + 1) % 5;
		glutPostRedisplay();
		break;
	case 'i':
		sphereDepth += 1;
		if (sphereDepth > 20) sphereDepth = 20;
		glutPostRedisplay();
		break;
	case 'I':
		sphereDepth -= 1;
		if (sphereDepth < 4) sphereDepth = 4;
		glutPostRedisplay();
		break;
	case 'O':
		animationPeriod += 5;
		glutPostRedisplay();
		break;
	case 'o':
		if (animationPeriod > 5) animationPeriod -= 5;
		glutPostRedisplay();
		break;
	case 'x':
		angleXZ += 5.0;
		if (angleXZ > 360.0) angleXZ -= 360.0;
		glutPostRedisplay();
		break;
	case 'X':
		angleXZ -= 5.0;
		if (angleXZ < 0.0) angleXZ += 360.0;
		glutPostRedisplay();
		break;

	case ' ':
		if (isAnimate) isAnimate = 0;
		else
		{
			isAnimate = 1;
			animate(1);
		}
		break;
	default:
		break;
	}
}
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Press q to toggle wireframe / fill." << std::endl
		<< "Press the up/down arrow keys to look up and down." << std::endl
		<< "Press the x, X, keys to rotate the scene." << std::endl
		<< "Press Space to toggle in red object rotation, o, O to increment the rotation-speed of the red cube." << std::endl
		<< "Press e to toggle inbetween sphere and cube." << std::endl
		<< "Press i to increase the size of sphere." << std::endl;
}

// Main routine.
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	printInteraction();
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("box.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}

