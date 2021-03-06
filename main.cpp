/*
   Class-Room Scenario created in OpenGL
*/

#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <iostream>

using namespace std;

/* Global variables */
char title[] = "Class-Room";
int zoom = 0;
int panlr = 0;
int panud = 0;
int refreshMills = 15;
GLfloat angle1 = 0.0f;
GLfloat angle2 = 0.0f;
bool fanOn = false;
bool rot = false;
GLfloat rotate = 0.0f;

/*Define some colors*/
float brown[]  = {0.65 ,0.5 ,0.39};
float white[] = {1,1,1};
float black[] = {0,0,0};
float blue[] = {.8,.8,.8};
float green[] ={.1,1,.1};
float red[] = {1,.4,.2};
float cream[] = {.83,.91,.69};
float cream1[] = {.78,.80,.76};
float cyan[] = {0.678431,0.917647,0.917647};
float olive[] = {0.309804,0.309804,0.184314};
float wood[] = {0.52,0.37,0.26};
float choc[] = {0.36,0.2,0.09};
float grey[] = {0.329412,0.329412,0.329412};


/* Initialize OpenGL Graphics */
void initGL()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
  glClearDepth(1.0f);                   // Set background depth to farthest
  glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
  glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
  glShadeModel(GL_SMOOTH);   // Enable smooth shading
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}


void DrawCube(float * color, float *color1 )
{
  glColor3f(color[0],color[1],color[2]);
  glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Top)
  glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Top)
  glColor3f(color1[0],color1[1],color1[2]);
  glVertex3f(-1.0f, 1.0f, 1.0f);    // Bottom Left Of The Quad (Top)
  glVertex3f( 1.0f, 1.0f, 1.0f);    // Bottom Right Of The Quad (Top)
  glColor3f(color[0],color[1],color[2]);
  glVertex3f( 1.0f,-1.0f, 1.0f);    // Top Right Of The Quad (Bottom)
  glVertex3f(-1.0f,-1.0f, 1.0f);    // Top Left Of The Quad (Bottom)
  glColor3f(color1[0],color1[1],color1[2]);
  glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Bottom)
  glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Bottom)
  glColor3f(color[0],color[1],color[2]);
  glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Front)
  glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Front)
  glColor3f(color1[0],color1[1],color1[2]);
  glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Front)
  glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Front)
  glColor3f(color[0],color[1],color[2]);
  glVertex3f( 1.0f,-1.0f,-1.0f);    // Top Right Of The Quad (Back)
  glVertex3f(-1.0f,-1.0f,-1.0f);    // Top Left Of The Quad (Back)
  glColor3f(color1[0],color1[1],color1[2]);
  glVertex3f(-1.0f, 1.0f,-1.0f);    // Bottom Left Of The Quad (Back)
  glVertex3f( 1.0f, 1.0f,-1.0f);    // Bottom Right Of The Quad (Back)
  glColor3f(color[0],color[1],color[2]);
  glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Left)
  glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Left)
  glColor3f(color1[0],color1[1],color1[2]);
  glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Left)
  glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Left)
  glColor3f(color[0],color[1],color[2]);
  glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Right)
  glVertex3f( -1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Right)
  glColor3f(color1[0],color1[1],color1[2]);
  glVertex3f( -1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Right)
  glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Right)
}


void DrawTiles(int colorflag,float x,float y,float z)
{
  float cubefacecolor[] = {0.329412,0.329412,0.329412};

  glScalef(1,1,1);

  glPushMatrix();

  glTranslatef(x, y, z);  // Move right and into the screen

  //colorflag = 1 => white cube
  //colorflag =  0 => black cube
  if(colorflag == 1)
  {
    //cout<<"here";
    cubefacecolor[0] = 0.752941;
    cubefacecolor[1] =0.752941 ;
    cubefacecolor[2] = 0.752941;
  }

  glBegin(GL_QUADS); // Begin drawing the color cube with 6 quads
    // Top face (y = 1.0f)
    // Define vertices in counter-clockwise (CCW) order with normal pointing out
    DrawCube(cubefacecolor, cubefacecolor);
  glEnd();  // End of drawing color-cube

  glPopMatrix();
}


void DrawFloor(int width, int length,float baseX,float baseY,float baseZ)
{
  int i,j;

  for(i=0;i<length;i++)
    for(j=0;j<width;j++)
    {
      DrawTiles((i+j)%2+1, baseX - i  , -1 ,baseZ - j);
    }
  for(i=0;i<length;i++)
    for(j=0;j<width;j++)
      //if(i==0 && j==0)
      //DrawTiles((i+j)%2-0.5, baseX +i  , -1 ,baseZ - j);
      //else
      DrawTiles((i+j)%2, baseX + i  , -1 ,baseZ - j);
}


void DrawTableTop(float x,float y,float z,float legScaleX,float legScaleY,float legScaleZ,float topScaleX,float topScaleY,float topScaleZ,float *color, float *color1)
{
  //float color[] = {.4,.2,.2};
  glPushMatrix();

  glTranslatef(x, y, z);  // Move right and into the screen
  glScalef(topScaleX,topScaleY,topScaleZ); //4,.25,1

  glBegin(GL_QUADS);  // Begin drawing the color cube with 6 quads
    // Top face (y = 1.0f)
    // Define vertices in counter-clockwise (CCW) order with normal pointing out
    DrawCube(color,color1);
  glEnd();  // End of drawing color-cube

  glPopMatrix();
}


void DrawTableLeg(float x,float y,float z,float legScaleX,float legScaleY,float legScaleZ,float topScaleX,float topScaleY,float topScaleZ,float *color, float *color1)
{
  //float color[] = {.4,.2,.2};
  glPushMatrix();

  glTranslatef(x,y,z);  // Move left and into the screen
  glScalef(legScaleX,legScaleY,legScaleZ); //.1,2,.1


  glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
    DrawCube(color,color1);
  glEnd();  // End of drawing color-cube

  glPopMatrix();
}


void createTable(float x,float y,float z)
{
  glPushMatrix();

  DrawTableTop(x+0,y+4,z+-6,.1,2,.1,4,.35,1,brown, choc);//co-ordinates
  //DrawTableTop(0,4,-10);//co-ordinates
  //  DrawTableTop(0,4,-14);//co-ordinates

  DrawTableLeg(x+-3.5+.2,y+1.75,z+-5,.15,2,.1,2,.25,1,brown, choc);//co-ordinates
  DrawTableLeg(x+-3.5+.2,y+1.75,z+-7,.15,2,.1,2,.25,1,brown, choc);//co-ordinates
  DrawTableLeg(x+3.5-.2,y+1.75,z+-5,.15,2,.1,2,.25,1,brown, choc);//co-ordinates
  DrawTableLeg(x+3.5-.2,y+1.75,z+-7,.15,2,.1,2,.25,1,brown, choc);//co-ordinates

  glPopMatrix();
}


void createClassRoomWalls(float x,float y,float z,float scaleX,float scaleY,float scaleZ,float * color )
{
  glPushMatrix();

  glTranslatef(x, y, z);  // Move right and into the screen

  glScalef(scaleX,scaleY,scaleZ); //.1,2,.1

  glBegin(GL_QUADS);   // Begin drawing the color cube with 6 quads
    // Top face (y = 1.0f)
    // Define vertices in counter-clockwise (CCW) order with normal pointing out
    DrawCube(color, color);
  glEnd();  // End of drawing color-cube

  glPopMatrix();
}


void createBench(float x,float y,float z)
{
  glPushMatrix();

  DrawTableTop(x+0,y+2,z+-6,.1,2,.1,4,.125,1,olive, black);//co-ordinates
  //DrawTableTop(0,4,-10);//co-ordinates
  //  DrawTableTop(0,4,-14);//co-ordinates

  DrawTableLeg(x+-3.7+.2,y+1,z+-5,.1,1,.1,4,.125,1,olive, black);//co-ordinates
  DrawTableLeg(x+-3.7+.2,y+1,z+-7,.1,1,.1,4,.125,1,olive, black);//co-ordinates
  DrawTableLeg(x+3.7-.2,y+1,z+-5,.1,1,.1,4,.125,1,olive, black);//co-ordinates
  DrawTableLeg(x+3.7-.2,y+1,z+-7,.1,1,.1,4,.125,1,olive, black);//co-ordinates

  glPopMatrix();
}


void createBoard()
{
  glPushMatrix();

  glTranslatef(0, 15, -60);  // Move right and into the screen
  glScalef(19,6,.1);

  glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
    // Top face (y = 1.0f)
    // Define vertices in counter-clockwise (CCW) order with normal pointing out
    DrawCube(black, black);
  glEnd();  // End of drawing color-cube

  glPopMatrix();
}


void createDoor(float *color,float sx,float sy,float sz)
{
  glPushMatrix();

  glTranslatef(43.7, 3, -56);  // Move right and into the screen
  glScalef(sx,sy,sz);

  glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
    // Top face (y = 1.0f)
    // Define vertices in counter-clockwise (CCW) order with normal pointing out
    DrawCube(color, color);
  glEnd();  // End of drawing color-cube

  glPopMatrix();
}


void createLight()
{
  glPushMatrix();

  glTranslatef(0, 25, -60);  // Move right and into the screen
  glScalef(13,0.3,.1);

  glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
    // Top face (y = 1.0f)
    // Define vertices in counter-clockwise (CCW) order with normal pointing out
    DrawCube(white, white);
  glEnd(); // End of drawing color-cube

  glPopMatrix();
}


void createBook(float *color,float x,float y,float z)
{
  glPushMatrix();

  glTranslatef(x,y,z);  // Move right and into the screen
  glScalef(0.5,0.25,.25);

  glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
    // Top face (y = 1.0f)
    // Define vertices in counter-clockwise (CCW) order with normal pointing out
    DrawCube(color, color);
  glEnd(); // End of drawing color-cube

  glPopMatrix();
}


void createFan( int x, int y, int z )
{
  glPushMatrix();

  DrawTableLeg(x,y+4,z,.15,4,.1,2,.25,1,brown,brown);//co-ordinates

  DrawTableLeg(x,y,z,0.5,0.5,0.5,2,.25,1,red,choc);

  DrawTableLeg(x,y,z,6,0.03,0.5,2,.25,1,white,choc);

  DrawTableLeg(x,y,z,0.5,0.03,6,2,.25,1,white,choc);

  glPopMatrix();
}


void createProjector()
{
  glPushMatrix();

  DrawTableLeg(0, 25,-50,.15,4,.1,2,.25,1,grey,grey );

  DrawTableLeg(0,21,-50,0.5,0.5,0.5,2,.25,1,black,black);

  glPopMatrix();
}


/*
void drawStage(float *color)
{
  glPushMatrix();

  glTranslatef(0, 15, -60);  // Move right and into the screen
  glScalef(20,0,10);

  glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
    // Top face (y = 1.0f)
    // Define vertices in counter-clockwise (CCW) order with normal pointing out
    DrawCube(color);
  glEnd();

  glPopMatrix();
}
*/


/*
  Handler for window-repaint event. Called back when the window first appears and
  whenever the window needs to be re-painted.
*/
void display()
{
  int i,j;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

  glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

  glLoadIdentity(); // Reset the model-view matrix

  glRotatef(rotate, 0.0f, 1.0f, 0.0f);

  glTranslatef( panlr,panud,zoom );

  // Render a color-cube consisting of 6 quads with different colors
  glPushMatrix();
  glTranslatef(0,0,60);
  glScalef(2,1.5,2);
  createTable(0, 2, -50);
  glPopMatrix();

  //Draw all the Benches
  for(i=0;i<6;i++)
    if(i%2==0)
      createTable(-8*1,2,-12*(i/2+1)), createTable(-6*3,2,-12*(i/2+1));
    else
      createTable(8,2,-12*(i/2+1)),createTable(6*3,2,-12*(i/2+1));

  for(i=0;i<6;i++)
    if(i%2==0)
      createBench(-8*1,2,-12*(i/2+1)+4), createBench(-6*3,2,-12*(i/2+1)+4);
    else
      createBench(8,2,-12*(i/2+1)+4), createBench(6*3,2,-12*(i/2+1)+4);

  // Draw Class-Room walls
  createClassRoomWalls(0,15,-70,50,15,1,cream1); //front
  createClassRoomWalls(-35,15,-70,.25,15,70,cream); //left
  createClassRoomWalls(35,15,-70,.25,15,70,cream); //right
  createClassRoomWalls(0,95,-35,50,60,60,white); //top

  /* Draw the Class Board*/
  createBoard();

  createDoor(choc,9,16,9); // Draw Door
  createDoor(wood,9,15,8);

  createLight(); // Draw Tubelight

  glPushMatrix();
  createBook(black,2.5, 9.4, -50.5);
  createBook(cyan,2.5, 9.5, -50.5);
  glPopMatrix();

  DrawFloor(52,52,0,0,-15); //width,height,xy position

  glPushMatrix();
  glTranslatef(-13,21,-40);
  glRotatef(angle1, 0.0f, 1.0f, 0.0f);
  glTranslatef(13,-21,40);
  createFan(-13, 21,-40);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(13,21,-40);
  glRotatef(angle2, 0.0f, 1.0f, 0.0f);
  glTranslatef(-13,-21,40);
  createFan(13, 21,-40);
  glPopMatrix();

  createProjector();

  glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)

  if(fanOn)
  {
    angle1 += 15.0f;
    angle2 += 20.0f;
  }
}


/*
Handler for window re-size event. Called back when the window first appears and
whenever the window is re-sized with its new width and height
*/
void reshape(GLsizei width, GLsizei height)
{
  // Compute aspect ratio of the new window
  if (height == 0)
    height = 1;                // To prevent divide by 0

  GLfloat aspect = (GLfloat)width / (GLfloat)height;

  // Set the viewport to cover the new window
  glViewport(0, 0, width, height);

  // Set the aspect ratio of the clipping volume to match the viewport
  glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix

  glLoadIdentity();

  // Enable perspective projection with fovy, aspect, zNear and zFar
  //(0,0,0,0,0,-100,0,0,-1);
  gluPerspective(90.0f, aspect, 0.1f, 100.0f);

  // glOrtho(-20,20,20,20,0,-100);
  // glScalef(1,1,5);
  gluLookAt(1, 12, -5, /* look from camera XYZ */
            0, 0, -30, /* look at the origin */
            0, 1, 0); /* positive Y up vector */
  // glCallList(SCENE);
}


void mouseFunction( int button, int state, int x, int y )
{
  if( button==GLUT_LEFT_BUTTON && state==GLUT_DOWN ) //if left button is clicked, zoomin
  {
    zoom+=5;
  }
  else if( button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN ) //if right button is clicked,zoomout
  {
    zoom-=5;
  }
  glutPostRedisplay();
}


void keyFunction(unsigned char key, int x, int y)
{
  if(key=='f')
  {
    fanOn^=1;
  }
  else if(key=='l')
  {
    rotate+=5.0f;
  }
  else if(key=='r')
  {
    rotate-=5.0f;
  }

  glutPostRedisplay();
}


void SpecialInput(int key, int x, int y)
{
  switch(key)
  {
    case GLUT_KEY_LEFT:
      panlr+=5;
      break;
    case GLUT_KEY_RIGHT:
      panlr-=5;
      break;
    case GLUT_KEY_UP:
      panud-=5;
      break;
    case GLUT_KEY_DOWN:
      panud+=5;
      break;
  }
  glutPostRedisplay();
}


void timer(int value)
{
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}


/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv)
{
  glutInit(&argc, argv);           // Initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE);// Enable double buffered mode
  glutInitWindowSize(640, 480);    // Set the window's initial width & height
  glutInitWindowPosition(50, 50);  // Position the window's initial top-left corner
  glutCreateWindow(title);         // Create window with the given title
  glutDisplayFunc(display);        // Register callback handler for window re-paint event
  glutReshapeFunc(reshape);        // Register callback handler for window re-size event
  glutMouseFunc(mouseFunction);    // Register callback handler for mouse interaction
  glutSpecialFunc(SpecialInput);   // Register callback handler for specials keys interaction
  glutKeyboardFunc(keyFunction);   // Register callback handler for keyboard keys
  initGL();                        // Our own OpenGL initialization
  glutTimerFunc(0, timer, 0);
  glutMainLoop();                  // Enter the infinite event-processing loop

  return 0;
}
