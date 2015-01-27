#include <iostream>
#include <freeglut.h>


void set2DMode(size_t Width, size_t Height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, Width, 0, Height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void set3DMode(size_t Width, size_t Height) {
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, float(Width) / Height, 0.01f, 1000);
	gluLookAt(0, 0, 40, 0, 0, 0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void displayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	int width = viewport[2];
	int height = viewport[3];
	set3DMode(width, height);

	set2DMode(width, height);
	glutSwapBuffers();
}

void reshapeFunc(int width, int height) {
	glViewport(0, 0, width, height);
}

void normalKeys(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		//glutLeaveMainLoop();
		break;
	default:
		break;
	}
}



int main() {
	std::cout << "Test\n";
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Test");
	glutDisplayFunc(displayFunc);
	glutReshapeFunc(reshapeFunc);
	glutMainLoop();
	return 0;
}