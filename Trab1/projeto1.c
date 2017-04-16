#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>  // Header File For The OpenGL32 Library
#include <OpenGL/glu.h> // Header File For The GLu32 Library
#include <GLUT/glut.h>  // Header File For The GLut Library
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "SOIL.h"

/*  Variaveis globais   */ 
const GLint w = 1024, h = 640;
GLfloat theta = 60.0f;
GLuint texture = 0;
/************************/

void init(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);    // Especificoes de observacao de cena
    gluOrtho2D(0, w, 0, h);
}

void reshape(GLsizei w, GLsizei h)
{
    glutReshapeWindow(1024, 640);   // Nao permite a alteracao de tamanho da janela
}

void loadTexture(void)
{
    texture = SOIL_load_OGL_texture(
                    "image2.png",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
                    );

    if(texture == 0)
    {
        printf("SOIL loading error: '%s'\n", SOIL_last_result());
        exit(EXIT_FAILURE);
    }

    glBindTexture(GL_TEXTURE_2D, texture); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void background(void)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);  // Define a textura corrente
    
    //glMatrixMode(GL_MODELVIEW); // pode comentar tambem

    glBegin(GL_QUADS);
        // TexCoord2i: Coord. dos pontos na textura
        // Vertex2i: Coord. dos pontos no poligono
        glTexCoord2i(0, 0); glVertex2i(0, 0);
        glTexCoord2i(1, 0); glVertex2i(w, 0);
        glTexCoord2i(1, 1); glVertex2i(w, h);
        glTexCoord2i(0, 1); glVertex2i(0, h);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

void circle(void)
{
    GLint N = 100;
    // Ponto 471, 518
    GLfloat x = 471.0f, y = 518.0f, r = 5.0f, theta = 0, h = (2 * 3.1415) / N;
    // h = 360 graus dividido por N retangulos

    for( ; theta <= 2 * 3.1415; theta += h)
    {
        /* Definicao de primitivas */
        glBegin(GL_TRIANGLES);
          glVertex2f(x, y);
          glVertex2f(x + r * cos(theta), y + r * sin(theta));
          glVertex2f(x + r * cos(theta+h), y + r * sin(theta+h));
          // Equacoes parametrizadas da circunferencia (circ. eh uma elipse)
        glEnd();
    }

}

void triangles(void)
{
    int i;
    // Ao fim do loop, a matriz MODELVIEW voltara a ser a identidade
    for(i = 0; i < 4; i++, theta += 90.0f)
    {
        glTranslatef(471.0, 518.0, 0.0);
        glRotatef(theta, 0.0, 0.0, 1.0);
        glTranslatef(-471.0, -518.0, 0.0);
        glBegin(GL_TRIANGLES);
            glVertex2f(471.0, 518.0);
            glVertex2f(515.0, 537.0);
            glVertex2f(515.0, 503.0);
        glEnd();
        glLoadIdentity();
        if(theta >= 360.0)
            theta -= 360.0;
    }
}

void display(void) 
{ 
    glClear(GL_COLOR_BUFFER_BIT);

    background();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 0.0f);
    triangles();

    glColor3f(1.0f, 0.0f, 0.0f);
    circle();

    glColor3f(1.0f, 1.0f, 1.0f);

    glutSwapBuffers();
    glFlush();
}

void onMouseClick(int button, int state, int x, int y) 
{
    // Tratamento apenas do click DOWN
    if(state == GLUT_DOWN)
    {
        if(button == GLUT_LEFT_BUTTON)
        {   
            theta += 10.0;
        }
        else if(button == GLUT_RIGHT_BUTTON)
        {
            theta += -10.0;
        }
    }
 
    glutPostRedisplay(); // Chama a funcao DISPLAY apos a atualizacao
}

void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1024, 640);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Projeto 1 - Computacao Grafica");

    init();
    loadTexture();

    glutDisplayFunc(display);
    //glutReshapeFunc(reshape);
    glutMouseFunc(onMouseClick);
    glutMainLoop();
}