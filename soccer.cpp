#include "Main.h"
#include "soccerVertices.cpp"
#include "soccerNormals.cpp"
#include "soccerQuads.cpp"
#include "soccerTextures.cpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <math.h>
#define E 2.71828


void InitGL(GLvoid);
void reshape(int width, int height);
void display(void);
void makeTextures(void);
void soccerBall(void);
void animacion(void);
void grass(void);
void keyboard(unsigned char key, int x, int y);
void arrow_keys(int a_keys, int x, int y);

float t = -1.85,
	soccerX = -12.0, soccerY = fabs(pow(-t, E) * ((3 * (cos(25 * t))) + (3 * (sin(25 * t))))) , soccerZ = 0.0,
	soccerRotX = 0.0, soccerRotY = 0.0,
	rotation = 0.0,
	posX = 0.0, posY = 0.0, posZ = 0.0;
boolean startAnimation = false;
int width, height, nrChannels;

int main(int argc, char** argv) {
	glutInit(&argc, argv);                          // Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);   // Display Mode (Clores RGB y alpha | Buffer Sencillo )
	glutInitWindowSize(1000, 1000);                 // Tamaño de la Ventana
	glutInitWindowPosition(0, 0);                   //Posicion de la Ventana
	glutCreateWindow("Proyecto Extraordinario");    // Nombre de la Ventana
	InitGL();                                       // Parametros iniciales de la aplicacion
	glutDisplayFunc(display);                       //Indicamos a Glut funcion de dibujo
	glutReshapeFunc(reshape);                       //Indicamos a Glut funcion en caso de cambio de tamano
	glutKeyboardFunc(keyboard);                     //Indicamos a Glut funcion de manejo de teclado
	glutSpecialFunc(arrow_keys);                    //Otras
	glutIdleFunc(animacion);
	glutMainLoop();//}
	return 0;
}
void InitGL(GLvoid) {    // Inicializamos parametros
	glClearColor(0.2392f, 0.5725f, 0.7960f, 0.0f);			// Negro de fondo
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	makeTextures();
}
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limiamos pantalla y Depth Buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	// Reinicializamos la actual matriz Modelview
	glTranslatef(0.0, -7.0, -20.0);
	glTranslatef(posX, posY, posZ);
	glRotatef(rotation, 0.0, 1.0, 0.0);
	grass();
	soccerBall();
	glFlush();
}
void makeTextures() {
	unsigned int texture = 0;
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}
void soccerBall() {
	glEnable(GL_TEXTURE_2D);
	int i = 0;
	unsigned char* soccerData = stbi_load("texturas/soccerTexture.jpg", &width, &height, &nrChannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, soccerData);
	stbi_image_free(soccerData);
	glColor3f(1.0, 1.0, 1.0);

	glPushMatrix();
		glTranslatef(soccerX, soccerY, soccerZ);
			glPushMatrix();
				glTranslatef(0.0, 0.9840625, 0.0);
				glRotatef(soccerRotX, 1.0, 0.0, 0.0);
				glRotatef(soccerRotY, 0.0, 1.0, 0.0);
				glTranslatef(0.0, -0.9840625, 0.0);
			glBegin(GL_QUADS);
				for (i; i < 3456; i++) {
					glTexCoord2f(vt[f[i][1]][0], vt[f[i][1]][1]); glNormal3f(vn[f[i][2]][0], vn[f[i][2]][1], vn[f[i][2]][2]); glVertex3f(v[f[i][0]][0], v[f[i][0]][1], v[f[i][0]][2]);
					glTexCoord2f(vt[f[i][4]][0], vt[f[i][4]][1]); glNormal3f(vn[f[i][5]][0], vn[f[i][5]][1], vn[f[i][5]][2]); glVertex3f(v[f[i][3]][0], v[f[i][3]][1], v[f[i][3]][2]);
					glTexCoord2f(vt[f[i][7]][0], vt[f[i][7]][1]); glNormal3f(vn[f[i][8]][0], vn[f[i][8]][1], vn[f[i][8]][2]); glVertex3f(v[f[i][6]][0], v[f[i][6]][1], v[f[i][6]][2]);
					glTexCoord2f(vt[f[i][10]][0], vt[f[i][10]][1]); glNormal3f(vn[f[i][11]][0], vn[f[i][11]][1], vn[f[i][11]][2]); glVertex3f(v[f[i][9]][0], v[f[i][9]][1], v[f[i][9]][2]);
				}
			glEnd();
		glPopMatrix();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}
void animacion() {
	if (t < (-0.003208) && startAnimation) {
		t += 0.002;
		soccerX += 0.05;
		soccerY = fabs(pow(-t, E) * ((3 * (cos(25 * t))) + (3 * (sin(25 * t)))));
	}

	glutPostRedisplay();
}
void grass() {
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	unsigned char* grassData = stbi_load("texturas/grass.jpg", &width, &height, &nrChannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, grassData);
	stbi_image_free(grassData); // Se libera la memoria de la textura
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
		for (int i = (-110); i <= 110; i++) {
			glPushMatrix();
				glTranslatef(i, 0.0, 0.0); // posición de numFilas
				glPushMatrix();
					glTranslatef(0.0, 0.0, 15);
					for (int k = 15; k >= (-100); k--) {
						glTranslatef(0.0, 0.0, -1.0);
						glBegin(GL_QUADS);
							glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.0, 0.5);
							glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, 0.0, 0.5);
							glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 0.0, -0.5);
							glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.0, -0.5);
						glEnd();
					}
				glPopMatrix();
			glPopMatrix();
		}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}
void reshape(int width, int height) { // Creamos funcion Reshape
	if (height == 0)									// Prevenir division entre cero
		height = 1;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();
	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 170.0); //Tipo de vista
	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}
void arrow_keys(int a_keys, int x, int y) {// Funcion para manejo de teclas especiales (arrow keys)
	switch (a_keys) {
	case GLUT_KEY_PAGE_UP:
		posZ += 1.0;
		break;
	case GLUT_KEY_PAGE_DOWN:
		posZ -= 1.0;
		break;
	case GLUT_KEY_UP:
		posY -= 3.0;
		break;
	case GLUT_KEY_DOWN:
		posY += 3.0;
		break;
	case GLUT_KEY_LEFT:
		posX += 3.0;
		break;
	case GLUT_KEY_RIGHT:
		posX -= 3.0;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: exit(0);
		break;
	case 'R': rotation += 4;
		break;
	case 'r': rotation -= 4;
		break;
	case 'T':
		soccerRotX += 8;
		break;
	case 't':
		soccerRotX -= 8;
		break;
	case 'Y':
		soccerRotY += 8;
		break;
	case 'y':
		soccerRotY -= 8;
		break;
	case 'B':
	case 'b':
		startAnimation = true;
		t = -1.85;
		soccerX = -12.0;
		break;
	}
	glutPostRedisplay();
}
