/*  
*   Projeto 1 - CG
*   
*   Bernardo Duarte             8598861
*   Giovani Ortolani Barbosa    8936648
*   Giovanni Robira             8531887           
*   Julia Minetto Macias        8937329
*/

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

/*                 Variaveis globais                  */ 
const GLint imageW = 1024, imageH = 640;
GLfloat theta = 60.0f;
GLuint texture = 0;
int leftButtonDown = 0, rightButtonDown = 0;
/******************************************************/

void init(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);            // Especificoes de observacao de cena
    gluOrtho2D(0, imageW, 0, imageH);       // Define a janela de recorte como sendo do tamanho do background
}

void reshape(GLsizei w, GLsizei h)
{
    glutReshapeWindow(1024, 640);   // Nao permite a alteracao de tamanho da janela
}

void mouseHold(void)
{
    if(leftButtonDown)
        theta += 0.5f;
    if(rightButtonDown)
        theta -= 0.5f;
}

void onMouseClick(int button, int state, int x, int y) 
{
    if(button == GLUT_LEFT_BUTTON)
    {   
        leftButtonDown = (state == GLUT_DOWN);
    }
    else if(button == GLUT_RIGHT_BUTTON)
    {
        rightButtonDown = (state == GLUT_DOWN);
    }
 
    glutPostRedisplay();    // Chama a funcao display() para realizar a atualizacao a cada frame
}

void loadTexture(void)
{
    texture = SOIL_load_OGL_texture(
                    "image4.png",
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

    glBegin(GL_QUADS);
        // TexCoord2i: Coord. dos pontos na textura
        // Vertex2i: Coord. dos pontos no poligono
        glTexCoord2i(0, 0); glVertex2i(0, 0);
        glTexCoord2i(1, 0); glVertex2i(imageW, 0);
        glTexCoord2i(1, 1); glVertex2i(imageW, imageH);
        glTexCoord2i(0, 1); glVertex2i(0, imageH);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

void retangle(void)
{   
    glColor3f(0.5f, 0.35f, 0.05f);
    glBegin(GL_QUADS);
        glVertex2f(204.0f, 455.0f);
        glVertex2f(212.0f, 455.0f);
        glVertex2f(212.0f, 515.0f);
        glVertex2f(204.0f, 515.0f);
    glEnd();
}

void triangles(void)
{
    int i;
    // Ao fim do loop, a matriz MODELVIEW voltara a ser a identidade
    // i = 4, 4 triangulos amarelos e 4 triangulos vermelhos
    for(i = 0; i < 4; i++, theta += 90.0f)
    {
        if(theta >= 360.0)
            theta -= 360.0;
        glTranslatef(208.0, 515.0, 0.0);
        glRotatef(theta, 0.0, 0.0, 1.0);
        glTranslatef(-208.0, -515.0, 0.0);
        glBegin(GL_TRIANGLES);
            glColor3f(0.1f, 0.1f, 0.0f);
            glVertex2f(208.0, 515.0);
            glColor3f(1.0f, 1.0f, 0.2f);
            glVertex2f(238.0, 515.0);
            glColor3f(0.8f, 0.7f, 0.1f);
            glVertex2f(238.0, 545.0);
        glEnd();
        glBegin(GL_TRIANGLES);
            glColor3f(0.5f, 0.1f, 0.1f);
            glVertex2f(208.0, 515.0);
            glColor3f(0.0f, 0.0f, 0.0f);
            glVertex2f(238.0, 545.0);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f(208.0, 590.0);
        glEnd();
        glLoadIdentity();
    }
}

void circle(void)
{
    GLint N = 100;
    // Ponto do dedo: 471, 518
    GLfloat x = 208.0f, y = 515.0f, r = 4.0f, theta = 0, h = (2 * 3.1415) / N;
    // h = 360 graus dividido por N retangulos

    for( ; theta <= 2 * 3.1415; theta += h)
    {   
        glColor3f(0.0f, 0.5f, 0.5f);  
        glBegin(GL_TRIANGLES);  
            glVertex2f(x, y);
            // Equacoes parametrizadas da circunferencia (circ. eh uma elipse)  
            glVertex2f(x + r * cos(theta), y + r * sin(theta));
            glVertex2f(x + r * cos(theta + h), y + r * sin(theta + h));
        glEnd();
    }
}

void display(void) 
{ 
    glClear(GL_COLOR_BUFFER_BIT);

    background();   // Carrega a imagem de fundo

    mouseHold();    // Verifica se o mouse esta pressionado
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    retangle();
    triangles();
    circle();

    glColor3f(1.0f, 1.0f, 1.0f);

    //glutSwapBuffers();
    glutPostRedisplay();    // Chama a funcao DISPLAY apos a atualizacao
    glFlush();
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
    glutReshapeFunc(reshape);
    glutMouseFunc(onMouseClick);
    glutMainLoop();
}