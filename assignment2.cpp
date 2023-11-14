#include <GL/glut.h>


float angleX = 0.0; // Rotation around the X axis
float angleY = 0.0; // Rotation around the Y axis

float playerPosX = 0.0; // Player's position along the X axis
float playerPosY = -0.42; // Player's position along the Y axis
float playerPosZ = 0.0; // Player's position along the Z axis

float playerRotAngle = 0.0; // Player's rotation angle


// void drawFencePost(float x, float y, float z) {
//     glPushMatrix();
//     glColor3f(0.6, 0.4, 0.2); // Brown color for the fence post
//     glTranslatef(x, y, z);
//     glScalef(0.1, 1.0, 0.1); // Scale the cube to make it look like a post
//     glutSolidCube(1.0);
//     glPopMatrix();
// }
void drawFencePost(float x, float y, float z) {
    GLUquadric *quadric = gluNewQuadric();

    glPushMatrix();
    glColor3f(0.6, 0.4, 0.2); // Brown color for the fence
    glTranslatef(x, y, z);
    glRotatef(-90, 1.0, 0.0, 0.0); // Rotate the cylinder to stand upright
    gluCylinder(quadric, 0.05, 0.05, 1.0, 10, 10); // Draw a cylinder as a post
    glPopMatrix();

    gluDeleteQuadric(quadric);
}

void drawSun() {
    glPushMatrix();
      glColor3f(1.0, 0.65, 0.0); // Light orange color for the sun
    glTranslatef(1.0, 1.5, -1.9); // Position the sun slightly in front of the back wall
    glutSolidSphere(0.3, 20, 20); // Draw a smaller sphere for the sun
    glPopMatrix();
}







void drawWall(double thickness) {
	glPushMatrix();
	glTranslated(0.5, 0.5 * thickness, 0.5);
	glScaled(1.0, thickness, 1.0);
	glutSolidCube(1);
	glPopMatrix();
}


void drawPlayer() {
    glPushMatrix();

    // Apply a uniform scale to the entire model
    glScalef(0.2, 0.2, 0.2); 

    // Drawing the head (sphere) in yellow
    glColor3f(1.0, 1.0, 0.0); // Yellow color
    glPushMatrix();
    glTranslatef(0.0, 1.5, 0.0);
    glutSolidSphere(0.25, 20, 20);
    glPopMatrix();

    // Drawing the body (cube) in green
    glColor3f(0.0, 1.0, 0.0); // Green color
    glPushMatrix();
    glTranslatef(0.0, 0.75, 0.0);
    glScalef(0.5, 1.0, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    // Drawing arms (cubes) in blue
    glColor3f(0.0, 0.0, 1.0); // Blue color
    glPushMatrix();
    glTranslatef(0.0, 0.75, 0.0);
    glScalef(1.0, 0.1, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

    // Drawing legs (cubes) in orange, separated
    //  glColor3f(1.0, 0.0, 0.0); // Setting the color to red
    glColor3f(1.0, 0.5, 0.0);  // orange color
    // Left leg
    glPushMatrix();
    glTranslatef(-0.1, 0.0, 0.0); // Slightly to the left
    glScalef(0.1, 0.5, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();
    // Right leg
    glPushMatrix();
    glTranslatef(0.1, 0.0, 0.0); // Slightly to the right
    glScalef(0.1, 0.5, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

    // Drawing hands (spheres) in yellow
    glColor3f(1.0, 1.0, 0.0); // Yellow color
    glPushMatrix();
    glTranslatef(-0.5, 0.75, 0.0);
    glutSolidSphere(0.1, 10, 10);
    glColor3f(1.0, 0.0, 0.0); // Setting the color to red
    glTranslatef(1.0, 0.0, 0.0);
    glutSolidSphere(0.1, 10, 10);
    glPopMatrix();

    // Drawing feet (spheres) in yellow
    glColor3f(1.0, 1.0, 0.0); // Yellow color
    glPushMatrix();
    glTranslatef(-0.1, -0.25, 0.0); // Adjust to align with legs
    glutSolidSphere(0.1, 10, 10);
    glTranslatef(0.2, 0.0, 0.0);
    glutSolidSphere(0.1, 10, 10);
    glPopMatrix();

    glPopMatrix();
}



void specialKeyInput(int key, int x, int y) {
    float moveAmount = 0.1; // Define a variable for movement amount
    float halfPlayerWidth = 0.1 / 2; // Half the width of the player

    switch (key) {
        case GLUT_KEY_RIGHT: // Move right
            if (playerPosX + moveAmount + halfPlayerWidth < 2.20) {
                playerPosX += moveAmount;
                playerRotAngle = 90.0; // Rotate to the right
            }
            break;
        case GLUT_KEY_LEFT: // Move left
            if (playerPosX - moveAmount - halfPlayerWidth > -2.20) {
                playerPosX -= moveAmount;
                playerRotAngle = -90.0; // Rotate to the left
            }
            break;
        case GLUT_KEY_UP: // Move player backward
            if (playerPosZ - moveAmount - halfPlayerWidth > -2.15) {
                playerPosZ -= moveAmount;
                playerRotAngle = 180.0;
            }
            break;
        case GLUT_KEY_DOWN: // Move player forward
            if (playerPosZ + moveAmount + halfPlayerWidth < 2.3) { // Assuming no front wall
                playerPosZ += moveAmount;
                playerRotAngle = 0.0;
            }
            break;
        //     case GLUT_KEY_UP: // Move up
        //     playerPosY += 0.1;
        //     playerRotAngle = 0.0; // Facing forward/up
        //     break;
        //     case GLUT_KEY_DOWN: // Move down
        //     playerPosY -= 0.1;
        //     playerRotAngle = 180.0; // Facing backward/down
        //     break;
    }
    glutPostRedisplay();
}



void handleKeyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': // Rotate camera upward
            angleX += 5.0;
            break;
        case 's': // Rotate camera downward
            angleX -= 5.0;
            break;
        case 'a': // Rotate camera left
            angleY += 5.0;
            break;
        case 'd': // Rotate camera right
            angleY -= 5.0;
            break;

    }
    glutPostRedisplay();
}



void display() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // Set the clear color to white
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0,  // Camera position (front view)
              0.0, 0.0, 0.0,  // Look at point (origin)
              0.0, 1.0, 0.0); // Up vector (y-axis)

    // Apply rotations
    glRotatef(angleX, 1.0, 0.0, 0.0); // Rotate around X axis
    glRotatef(angleY, 0.0, 1.0, 0.0); // Rotate around Y axis


    // Draw the ground
    glColor3f(0.7, 0.7, 0.7); // Set color for ground
    glPushMatrix();
    glTranslatef(0, -0.5, 0); // Position the ground
    glScalef(4.5, 0.05, 4.5); // Scale to act as a ground
    glutSolidCube(1);
    glPopMatrix();

    // Draw the left wall
    glColor3f(0.5, 0.5, 0.5); // Set color for walls
    glPushMatrix();
    glTranslatef(-2.25, 0.97, 0); // Adjust position for left wall
    glRotatef(0, 0, 0, 1); // Rotate to stand up
    glScalef(0.05, 3.0, 4.4); // Scale to fit ground's side and back wall's height
    glutSolidCube(1);
    glPopMatrix();


    // Draw the right wall
    glPushMatrix();
    glTranslatef(2.25, 0.97, 0); // Adjust position for right wall
    glRotatef(0, 0, 0, 1); // Rotate to stand up
    glScalef(0.05, 3.0, 4.5); // Scale to fit ground's side and back wall's height
    glutSolidCube(1);
    glPopMatrix();
    

    // Draw the back wall
    glColor3f(0.68, 0.85, 1.0); // RGB for light blue

    glPushMatrix();
    glTranslatef(0, 0.97, -2.2); // Position for back wall
    glRotatef(90, 0, 0, 1); // Rotate to stand up
    glScalef(3, 4.5, 0.05); // Scale to fit ground's side
    glutSolidCube(1);
    glPopMatrix();
    
    for (float i = -2.15; i <= 2.15; i += 1.0) {
        // Left fence
        drawFencePost(-2.35, 0.5, i);
        // Right fence
        drawFencePost(2.35, 0.5, i);
    }

    // Draw fence along the back side
    // for (float i = -2.25; i <= 2.25; i += 1.0) {
    //     drawFencePost(i, 0.5, -2.35);
    // }

     drawSun();

    glPushMatrix();
    glTranslatef(playerPosX, playerPosY, playerPosZ);
    glRotatef(playerRotAngle, 0.0, 1.0, 0.0); // Rotate around the Y axis
    drawPlayer();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 800);
    glutCreateWindow("Amusement park");

    glEnable(GL_DEPTH_TEST); // Enable depth testing

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)800 / (GLfloat)600, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(display);
     
     // Register keyboard callback
    glutKeyboardFunc(handleKeyboard);
    glutSpecialFunc(specialKeyInput);




    glutMainLoop();
    return 0;
}