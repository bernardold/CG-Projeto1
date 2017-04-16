/*
*   Fonte: http://stackoverflow.com/questions/8249282/set-background-image-of-an-opengl-window
*/


#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h> // Header File For The OpenGL32 Library
#include <OpenGL/glu.h> // Header File For The GLu32 Library
#include <GLUT/glut.h> // Header File For The GLut Library
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "SOIL.h"

GLfloat R = 0.0f, G = 0.0f, B = 0.0f; // variaveis globais
GLuint texture = 0;

GLfloat sorteia_cor() 
{
    return (rand()*1.0f) / (RAND_MAX*1.0f);
}

void init(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION); // Especificoes de observacao de cena
    gluOrtho2D(0, 1024, 0, 640);
}

GLuint loadTexture()
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
    
    return texture;
}

// void orthogonalStart(void) 
// {
//     glMatrixMode(GL_PROJECTION);
//     glPushMatrix();
//     glLoadIdentity();
//     gluOrtho2D(0, 1024, 0, 640);
//     glMatrixMode(GL_MODELVIEW);
// }

// void orthogonalEnd(void)
// {
//     glMatrixMode(GL_PROJECTION);
//     glPopMatrix();
//     glMatrixMode(GL_MODELVIEW);
// }

void background(void)
{
    loadTexture();
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture); 
    
    //orthogonalStart();
    glMatrixMode(GL_MODELVIEW);

    // texture width/height
    const int iw = 1024;
    const int ih = 640;

    //glPushMatrix();
    glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex2i(0, 0);
        glTexCoord2i(1, 0); glVertex2i(iw, 0);
        glTexCoord2i(1, 1); glVertex2i(iw, ih);
        glTexCoord2i(0, 1); glVertex2i(0, ih);
    glEnd();
    //glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
    //glDepthMask(GL_FALSE);
    //glDisable(GL_DEPTH_TEST);

    //orthogonalEnd();
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
    GLfloat theta;
    // Ao fim do loop, a matriz MODELVIEW voltara a ser a identidade
    for(theta = 60.0; theta <= 360.0; theta += 90.0)
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
    }
}

void display(void) 
{ 

    background();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 0.0f);
    triangles();

    glColor3f(1.0f, 0.0f, 0.0f);
    circle();

    glColor3f(1.0f, 1.0f, 1.0f);
    
    //glutPostRedisplay();
    glutSwapBuffers();
    glFlush();
}

void on_mouseClick(int botao_clicado, int estado_do_click, int x_mouse_position, int y_mouse_position) {
 
    // Sem o primeiro if, ela trata o click UP e DOWN
    if(estado_do_click == GLUT_DOWN)
    {
        if(botao_clicado == GLUT_RIGHT_BUTTON)
        {
            // R = 0.0f;
            // G = 0.0f;
            // B = 0.0f;
        }
        else if(botao_clicado == GLUT_LEFT_BUTTON)
        {
            // R = sorteia_cor();
            // G = sorteia_cor();
            // B = sorteia_cor();
        }
    }
 
    glutPostRedisplay(); // Forca a glut redesenhar a cena apзs a atualizacao, chama a funcao desenha de novo
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1024, 640);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Projeto 1 - Computacao Grafica");

    init();
    glutDisplayFunc(display);
    //glutMouseFunc(on_mouseClick);
    glutMainLoop();
    
    return 0;
}
