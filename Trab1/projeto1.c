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
#include "SOIL.h"


GLint w1 = 0, h1 = 0;
GLuint texture = 0;

void reshape(GLsizei w, GLsizei h)
{
    w1 = w;
    h1 = h;
    glViewport(0, 0, w, h);
}

void orthogonalStart(void) 
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-w1/2, w1/2, -h1/2, h1/2);
    glMatrixMode(GL_MODELVIEW);
}

void orthogonalEnd(void)
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void background(void)
{
    glBindTexture(GL_TEXTURE_2D, texture); 

    orthogonalStart();

    // texture width/height
    const int iw = 1024;
    const int ih = 640;

    glPushMatrix();
    glTranslatef(-iw/2, -ih/2, 0);
    glBegin(GL_QUADS);
        glTexCoord2i(0,0); glVertex2i(0, 0);
        glTexCoord2i(1,0); glVertex2i(iw, 0);
        glTexCoord2i(1,1); glVertex2i(iw, ih);
        glTexCoord2i(0,1); glVertex2i(0, ih);
    glEnd();
    glPopMatrix();

    orthogonalEnd();
}

void display(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);

    background();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glutSwapBuffers();
}

GLuint LoadTexture()
{
    texture = SOIL_load_OGL_texture(
                    "image1.png",
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
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    return texture;
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1024, 640);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Projeto 1 - Computacao Grafica");

    LoadTexture();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    
    return 0;
}

// GLuint texture;

// void LoadGLTextures()
// {
//     texture = SOIL_load_OGL_texture
//                 (
//                     "image1.png",
//                     SOIL_LOAD_AUTO,
//                     SOIL_CREATE_NEW_ID,
//                     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
//                 );

//     if(texture == 0)
//     {
//         printf("SOIL loading error: '%s'\n", SOIL_last_result());
//         exit(EXIT_FAILURE);
//     }

//     glBindTexture(GL_TEXTURE_2D, texture);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// }


// void init()
// {
//     glEnable(GL_TEXTURE_2D);
//     glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
//     gluOrtho2D(0, 1024, 0, 640);
//     //glShadeModel(GL_FLAT);
// }

// void display(void)
// {
//     glClear(GL_COLOR_BUFFER_BIT);
//     //glEnable(GL_TEXTURE_2D);
//     glLoadIdentity();
//     LoadGLTextures();
//     glBindTexture(GL_TEXTURE_2D, texture);
//     glColor3f(1.0f, 1.0f, 1.0f);
//     glBegin(GL_QUADS);
//         // glTexCoord2d(0.0,0.0); glVertex2d(0.0,0.0);
//         // glTexCoord2d(1.0,0.0); glVertex2d(1024.0,0.0);
//         // glTexCoord2d(1.0,1.0); glVertex2d(1024.0,512.0);
//         // glTexCoord2d(0.0,1.0); glVertex2d(0.0,512.0);
//         glTexCoord2f(0.0f, 0.25f); glVertex3f(0.25f, 0.25f, 0.0f);
//         glTexCoord2f(1.0f, 0.0f); glVertex3f(0.75f, 0.25f, 0.0f);
//         glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 0.75f, 0.0f);
//         glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
//     glEnd();

//     glFlush();
// }

// void main(int argc, char *argv[])
// {
//     glutInit(&argc, argv);
//     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//     glutInitWindowSize(1024, 640);
//     glutInitWindowPosition(200, 200);
//     glutCreateWindow("Projeto 1 - CG");

//     init();
//     glutDisplayFunc(display);
//     glutMainLoop();
// }

/*****************************************************************************************************/

// #include <GL/glut.h>    // Ja inclui a GL e a GLU
// #include "SOIL.h"

// void init(void)
// {
//     glClearColor(0.3f, 1.0f, 0.7f, 0.0f);   // Define a cor branca para o fundo 
//     gluOrtho2D(0, 1024, 0, 720);    // Define o plano ortogonal em que a cena sera construida
// }

// void desenha(void)
// {
//     glClear(GL_COLOR_BUFFER_BIT);   // Pinta a tela com a cor de fundo

//     glFlush();  // Forca a OpenGL a colocar na tela o que desenhamos
// }

// void main(int argc, char* argv[])
// {
//     glutInit(&argc, argv);                              // Inicia uma instancia da glut
//     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);        // Define o modo de display do buffer
//     glutInitWindowSize(1024, 720);                      // Define o tamanho em pixels da janela
//     glutCreateWindow("Projeto 1 - Computacao Grafica"); // Define o titulo da janela
//     glutDisplayFunc(desenha);                           // Estabelece que a funcao de rendering eh a funcao "desenha()"
 
//     //glutMouseFunc(on_mouseClick);   // Evento de click do mouse (binding)
//                                     // Espera recebero ponteiro para uma funcao com 4 args
//     init();
//     glutMainLoop();                 // Inicia as operacoes conforme as especificacoes anteriores
// }
