#include <GL/freeglut.h>
#include <iostream>

// Initialize OpenGL
void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);              // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);               // Set the type of depth-test
    glShadeModel(GL_SMOOTH);              // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffer
    glLoadIdentity(); // Reset the model-view matrix

    // Render your scene here

    glutSwapBuffers(); // Swap the front and back frame buffers (double buffering)
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
    glutInitWindowSize(800, 600);     // Set the window's initial width & height
    glutInitWindowPosition(100, 100); // Position the window's initial top-left corner
    glutCreateWindow("FreeGLUT Animation"); // Create window with the given title
    glutDisplayFunc(display);         // Register callback handler for window re-paint event
    initGL();                         // Our own OpenGL initialization
    glutMainLoop();                   // Enter the event-processing loop
    return 0;
}
