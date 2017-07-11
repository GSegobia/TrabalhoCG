#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

#include "Texture/TexturePixMap.cpp"
#include "Particle/Particles.cpp"

#include "MainScreen.h"

int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL | GLUT_DEPTH );
	glutInitWindowPosition (INIT_WINDOW_POSITION[0], INIT_WINDOW_POSITION[1]);
	glutInitWindowSize (curr_window_size[0], curr_window_size[1]);
	glutCreateWindow ("Particle System");

	glutReshapeFunc(ResizeWindow);
	glutKeyboardFunc(KeyboardPress);
	glutSpecialFunc(NonASCIIKeyboardPress);
	glutDisplayFunc(display);
	glutTimerFunc(20, timer, 1);
	glViewport(0, 0, curr_window_size[0], curr_window_size[1]);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_NORMALIZE);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	SetLights();

	makeImage(SPHERE_BMP_FILENAME, SPHERE_TEXTURE_NAME, false);
	makeImage(PARTICLE_RED_BMP_FILENAME, PARTICLE_RED_TEXTURE_NAME, false);
	makeImage(PARTICLE_WHITE_BMP_FILENAME, PARTICLE_WHITE_TEXTURE_NAME, false);

	glutMainLoop();

	return 0;
}
