#include <stdio.h>

#include "img/image.h"
#include "GL/glut.h"

IMGImage image = NULL;

void init (void) {
    glViewport(0, 0, imgGetWidth(image), imgGetHeight(image));

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, imgGetWidth(image), 0, imgGetHeight(image));
    glMatrixMode(GL_MODELVIEW);
}

void main_display (void) {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (image) imgDraw(image, 0, 0);

    glutSwapBuffers();
}

int main (int argc, char* argv[]) {
    unsigned char threshold;
    image = imgLoadJPG("images/atlas5.jpg");

    if (image) {
        glutInit(&argc, argv);

        glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
        glutInitWindowSize(imgGetWidth(image), imgGetHeight(image));

        threshold = imgGetOtsuThreshold(image);

        imgThresholded(image, threshold);

        glutCreateWindow("Image view");
        glutDisplayFunc(main_display);

        init();
        glutMainLoop();
    } else printf("Error opening the image!\n");

    return 0;
}

