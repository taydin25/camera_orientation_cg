#include<windows.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
int lolnot=1;//GL_LIGHTING is open or close
float xrv ,yrv ,zrv,degree;//rotation parameters.
// camera position angle
float angle=0.0;
// vector representing the camera's center position
float lx=0.0f,lz=-1.0f;
// camera s x and z
float x=0.0f,z=0.5f;
void init()
{
    glClearColor(0,0,0,1);
    glColor3f(1,0,0);
    glShadeModel (GL_SHININESS);
    //For light source
    GLfloat light_position[] = { 0.0, 0.0, -5.0, 1.0 };//-1-1 1 //x y z brightness
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    if(lolnot==1){
        glEnable(GL_LIGHTING);
    }
    else {
        glDisable(GL_LIGHTING);
    }
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}
void Cube_Face(GLfloat P1[],GLfloat P2[],GLfloat P3[],GLfloat P4[])
{
    glBegin(GL_POLYGON);
      glVertex3fv(P1);
      glVertex3fv(P2);
      glVertex3fv(P3);
      glVertex3fv(P4);
    glEnd();
}
void Cube(GLfloat V0[],GLfloat V1[],GLfloat V2[],GLfloat V3[],GLfloat V4[],GLfloat V5[],GLfloat V6[],GLfloat V7[])
{
      glColor3f(1,1,1);//Front face of cube
      Cube_Face(V0,V1,V2,V3);
      glColor3f(0,1,1);//Back face of cube
      Cube_Face(V4,V5,V6,V7);
      glColor3f(1,0.25,1);//Left face of cube
      Cube_Face(V0,V3,V7,V4);
      glColor3f(1,0.5,1);//Back face of cube
      Cube_Face(V1,V2,V6,V5);
      glColor3f(1,0.5,0.5);//Top face of cube
      Cube_Face(V0,V1,V5,V4);
      glColor3f(0.5,0.5,1);//Down face of cube
      Cube_Face(V3,V2,V6,V7);
}
void Cube_Draw(){
    GLfloat Vx[8][3]={
                            {-0.3, 0.3, 0.3 },//1.vertex of cube
                            { 0.3, 0.3, 0.3 },//2.vertex of cube
                            { 0.3,-0.3, 0.3 },//3.vertex of cube
                            {-0.3,-0.3, 0.3 },//4.vertex of cube
                            {-0.3, 0.3,-0.3},//5.vertex of cube
                            { 0.3, 0.3,-0.3 },//6.vertex of cube
                            { 0.3,-0.3,-0.3 },//7.vertex of cube
                            {-0.3,-0.3,-0.3 } //8.vertex of cube
                           };
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // Set the camera position
    gluLookAt(	x, 0.1f, z,
			x+lx, 0.6f,  z+lz,
			0.0f, 1.0f,  0.0f);

    glRotatef(degree,xrv,yrv,zrv);//rotate around a vector axis
    glutPostRedisplay();
    Cube(Vx[0],Vx[1],Vx[2],Vx[3],Vx[4],Vx[5],Vx[6],Vx[7]);//We have eight vertex in a cube
    glFlush ();
    glutSwapBuffers();
}//For camera moving by keyboard arrow keys.
void Move_Keys(int key, int xx, int yy) {

	float rate = 0.1f;
    printf("camera x=%f y=0.6 z=%f\n",x+lx,z+lz);
	switch (key) {
		case GLUT_KEY_LEFT :
			angle -= 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_RIGHT :
			angle += 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_UP :
			x += lx * rate;
			z += lz * rate;
			break;
		case GLUT_KEY_DOWN :
			x -= lx * rate;
			z -= lz * rate;
			break;
	}
}
int main(int argc, char **argv)
{
     printf("Enter rotation parameters [x y z angle]:\n");
     printf("First, enter x axis:");
     scanf("%f",&xrv);
     printf("Second, enter y axis:");
     scanf("%f",&yrv);
     printf("Third, enter z axis:");
     scanf("%f",&zrv);
     printf("Last, enter angle of rotation:");
     scanf("%f",&degree);
     printf("GL_LIGHTING function is enabled or disabled(1 or 0):");
     scanf("%d",&lolnot);
     glutInit(&argc, argv);
     glutInitWindowPosition(300,150);//default 300 150
     glutInitWindowSize(600,600);//default 600 600
     glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
     glutCreateWindow("CUBE IN ROTATE(HW6)");
     init();
     glutDisplayFunc(Cube_Draw);
     glutSpecialFunc(Move_Keys);
     glutMainLoop();
     return 0;
}
