/*************/
/* CONSTANTS */
/*************/

/* Posição e Redimensionamento de Janela */
const GLint INIT_WINDOW_POSITION[] = {150, 150};
const GLfloat ASPECT_RATIO = 1.5;

/* Iluminação */
const GLfloat LIGHT_0_POSITION[]    = { 1.0, 0.0, 0.0, 0.0};
const GLfloat LIGHT_1_POSITION[]    = { -1.0, 0.0, 0.0, 0.0};
const GLfloat LIGHT_2_POSITION[]    = { 0.0, 0.0, 1.0, 0.0};
const GLfloat LIGHT_3_POSITION[]    = { 0.0, 0.0, -1.0, 0.0};
const GLfloat LIGHT_AMBIENT[]       = { 0.8, 0.8, 0.8, 1.0};
const GLfloat LIGHT_DIFFUSE[]       = { 0.9, 0.9, 0.9, 1.0};
const GLfloat LIGHT_SPECULAR[]      = { 1.0, 1.0, 1.0, 1.0};
const GLfloat LIGHT_MODEL_AMBIENT[] = { 0.2, 0.2, 0.2, 1.0};

/* Posição do Visualizador */
const GLfloat MAXIMUM_VIEWER_DISTANCE    = 20;
const GLfloat MINIMUM_VIEWER_DISTANCE    = 2;
const GLfloat INITIAL_VIEWER_DISTANCE    = 10;
const GLfloat VIEWER_DISTANCE_INCREMENT  = 0.1;
const GLfloat INITIAL_VIEWER_AZIMUTH     = 0.0;
const GLfloat INITIAL_VIEWER_ZENITH      = M_PI / 2.0;
const GLfloat VIEWER_ANGLE_INCREMENT     = M_PI / 60.0;
const GLfloat LOOK_AT_POSITION[] = {0.0, 0.0, 0.0};

/* Contantes da Esfera */
GLuint SPHERE_TEXTURE_NAME = 1;
const char SPHERE_BMP_FILENAME[] = "Bitmaps/earthmap.bmp";
const GLfloat SPHERE_RADIUS = 1.0;

/* Constantes das Partículas */

GLuint PARTICLE_RED_TEXTURE_NAME = 0;
const char PARTICLE_RED_BMP_FILENAME[] = "Bitmaps/particlered.bmp";

GLuint PARTICLE_WHITE_TEXTURE_NAME = 2;
const char PARTICLE_WHITE_BMP_FILENAME[] = "Bitmaps/particlewhite.bmp";


/***********/
/* GLOBALS */
/***********/


GLint curr_window_size[] = {750, (GLint)(750/ASPECT_RATIO)};
GLint curr_viewport_size[] = {750, (GLint)(750/ASPECT_RATIO)};


GLfloat viewer_distance = INITIAL_VIEWER_DISTANCE;
GLfloat viewer_azimuth = INITIAL_VIEWER_AZIMUTH;
GLfloat viewer_zenith  = INITIAL_VIEWER_ZENITH;

ParticleSystem alpha_particles(true);
ParticleSystem beta_particles(false);

/*************/
/* FUNCTIONS */
/*************/

/* Define Iluminação */
void SetLights()
{
	glLightfv(GL_LIGHT0, GL_AMBIENT,  LIGHT_AMBIENT);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  LIGHT_DIFFUSE);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LIGHT_SPECULAR);
	glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_0_POSITION);

	glLightfv(GL_LIGHT1, GL_AMBIENT,  LIGHT_AMBIENT);
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  LIGHT_DIFFUSE);
	glLightfv(GL_LIGHT1, GL_SPECULAR, LIGHT_SPECULAR);
	glLightfv(GL_LIGHT1, GL_POSITION, LIGHT_1_POSITION);

	glLightfv(GL_LIGHT2, GL_AMBIENT,  LIGHT_AMBIENT);
	glLightfv(GL_LIGHT2, GL_DIFFUSE,  LIGHT_DIFFUSE);
	glLightfv(GL_LIGHT2, GL_SPECULAR, LIGHT_SPECULAR);
	glLightfv(GL_LIGHT2, GL_POSITION, LIGHT_2_POSITION);

	glLightfv(GL_LIGHT3, GL_AMBIENT,  LIGHT_AMBIENT);
	glLightfv(GL_LIGHT3, GL_DIFFUSE,  LIGHT_DIFFUSE);
	glLightfv(GL_LIGHT3, GL_SPECULAR, LIGHT_SPECULAR);
	glLightfv(GL_LIGHT3, GL_POSITION, LIGHT_3_POSITION);
}

/* Habilita Iluminação da Cena */
void UpdateLight()
{
	glPushMatrix();
		glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_0_POSITION);
		glLightfv(GL_LIGHT1, GL_POSITION, LIGHT_1_POSITION);
		glLightfv(GL_LIGHT2, GL_POSITION, LIGHT_2_POSITION);
		glLightfv(GL_LIGHT3, GL_POSITION, LIGHT_3_POSITION);
	glPopMatrix();

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
}

/* Redimensiona Janela */
void ResizeWindow(GLsizei w, GLsizei h)
{
	curr_window_size[0] = w;
	curr_window_size[1] = h;
	if (ASPECT_RATIO > w/h)
	{
		curr_viewport_size[0] = w;
		curr_viewport_size[1] = w / ASPECT_RATIO;
	}
	else
	{
		curr_viewport_size[1] = h;
		curr_viewport_size[0] = h * ASPECT_RATIO;
	}

	glViewport(0.5*(w-curr_viewport_size[0]), 0.5*(h-curr_viewport_size[1]), curr_viewport_size[0], curr_viewport_size[1]);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/* Zoom in, Zoom out e Fechar Janela*/
void KeyboardPress(unsigned char pressedKey, int mouseXPosition, int mouseYPosition)
{
	char pressedChar = char(pressedKey);
	switch(pressedKey)
	{
		case 'z': {
						viewer_distance -= VIEWER_DISTANCE_INCREMENT;
						if (viewer_distance < MINIMUM_VIEWER_DISTANCE)
							viewer_distance = MINIMUM_VIEWER_DISTANCE;
						break;
				  }
		case 'Z': {
						viewer_distance += VIEWER_DISTANCE_INCREMENT;
						if (viewer_distance > MAXIMUM_VIEWER_DISTANCE)
							viewer_distance = MAXIMUM_VIEWER_DISTANCE;
						break;
				  }
		case 27:  {
						exit(0);
						break;
				  }
	}
}

    //
void NonASCIIKeyboardPress(int pressedKey, int mouseXPosition, int mouseYPosition)
{
	glutIgnoreKeyRepeat(false);
	switch(pressedKey)
	{
		case GLUT_KEY_RIGHT: {
								viewer_azimuth += VIEWER_ANGLE_INCREMENT;
								if (viewer_azimuth > 2 * M_PI)
									viewer_azimuth -= 2* M_PI;
								break;
							 }
		case GLUT_KEY_LEFT:  {
								viewer_azimuth -= VIEWER_ANGLE_INCREMENT;
								if (viewer_azimuth < 0.0)
									viewer_azimuth+= 2 * M_PI;
								break;
							 }
		case GLUT_KEY_UP:    {
								viewer_zenith -= VIEWER_ANGLE_INCREMENT;
								if (viewer_zenith < VIEWER_ANGLE_INCREMENT)
									viewer_zenith = VIEWER_ANGLE_INCREMENT;
								break;
							 }
		case GLUT_KEY_DOWN:  {
								viewer_zenith += VIEWER_ANGLE_INCREMENT;
								if (viewer_zenith > M_PI - VIEWER_ANGLE_INCREMENT)
									viewer_zenith = M_PI - VIEWER_ANGLE_INCREMENT;
								break;
							 }
	}
}

void timer(int value){

	glutPostRedisplay();
	glutTimerFunc(20, timer, 1);
}

void drawSphere(GLfloat x_position){

	GLUquadric* sphere = gluNewQuadric();
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluQuadricTexture(sphere, GL_TRUE);
	//glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
    glPushMatrix();
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
      glPushMatrix();
		glTranslatef(x_position, 0, 0);
        glRotatef( -90.0, 1.0, 0.0, 0.0 );
        glBindTexture(GL_TEXTURE_2D, SPHERE_TEXTURE_NAME);
        gluSphere(sphere, SPHERE_RADIUS, 100, 100);
      glPopMatrix();
    glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(sphere);
}

void drawParticle(Particle currParticle, GLuint texture_name)
{
  glEnable(GL_TEXTURE_2D);
    glPushMatrix();
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
      glRotatef(currParticle.azimuth_rotation , 0, 1, 0);
      glRotatef( currParticle.zenith_rotation ,0,0,1);
      glTranslatef(SPHERE_RADIUS + currParticle.surface_translation_factor, 0, 0);
      glRotatef(90, 0 , 1, 0);
      glScalef( .25, .25, 1.0 );
      glBindTexture(GL_TEXTURE_2D, texture_name);

      glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2d(1,1);
          glVertex3f(0.5f, 0.5f, 0.0f); // Cima Direita
        glTexCoord2d(0,1);
          glVertex3f(-0.5f, 0.5f, 0.0f); // Cima Esquerda
        glTexCoord2d(1,0);
          glVertex3f(0.5f, -0.5f, 0.0f); // Baixo Direita
        glTexCoord2d(0,0);
          glVertex3f(-0.5f, -0.5f, 0.0f); // Baixo Esquerda
      glEnd();

      glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2d(1,1);
          glVertex3f(-0.5f, 0.5f, 0.0f); // Top Right
        glTexCoord2d(0,1);
          glVertex3f(0.5f, 0.5f, 0.0f); // Top Left
        glTexCoord2d(1,0);
          glVertex3f(-0.5f, -0.5f, 0.0f); // Bottom Right
        glTexCoord2d(0,0);
          glVertex3f(0.5f, -0.5f, 0.0f); // Bottom Left
      glEnd();
    glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

void drawAllParticles(GLfloat center, ParticleSystem &particles, GLuint texture_name){
 	glRotatef( -90.0, 0.0, 1.0, 0.0 );
 	particles.updateAll();
 	for(int i = 0; i < particles.getNumberOfParticles(); i++)
    	drawParticle(particles.getNextParticle(), texture_name);
}

void makeImage(const char *bitmap_file_name, GLuint &texture_name, bool has_alpha){

  TexturePixMap pix;
  pix.readBMPFile(bitmap_file_name, has_alpha);
  pix.setTexture(texture_name);

  return;
}

void display()
{
	// Initialize lighting.
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LIGHT_MODEL_AMBIENT);
	glEnable(GL_LIGHTING);

	// Set up the properties of the viewing camera.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(60.0, ASPECT_RATIO, 0.2, 100.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Position and orient viewer.
	gluLookAt(LOOK_AT_POSITION[0] + viewer_distance * sin(viewer_zenith) * sin(viewer_azimuth),
				LOOK_AT_POSITION[1] + viewer_distance * cos(viewer_zenith),
				LOOK_AT_POSITION[2] + viewer_distance * sin(viewer_zenith) * cos(viewer_azimuth),
				LOOK_AT_POSITION[0], LOOK_AT_POSITION[1], LOOK_AT_POSITION[2],
				0.0, 1.0, 0.020);

	UpdateLight();
	drawSphere(0.0);
	//drawSphere(3.0);

	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_COLOR,GL_ONE);

	drawAllParticles(0.0, alpha_particles, PARTICLE_RED_TEXTURE_NAME);
	drawAllParticles(0.0, beta_particles, PARTICLE_WHITE_TEXTURE_NAME);

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glutSwapBuffers();
	glFlush();
}
