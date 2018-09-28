#include <bits/stdc++.h>
#include <unistd.h>
#include <GL/glut.h>
#define mp make_pair
#define PINT pair<int,int>
using namespace std;
int path[100][2], increment= -1;  // for storing the best way to reach the goal
float points[4][2] = {{50,50},{450,50},{450,450},{50,450}}; 
float points1[4][2] = {{0,0},{500,0},{500,500},{0,500}};  // for maze boundary
int pathctr;  // length of the optimal path
float obstacle[17][17];
int sx,sy,dx,dy;
int curx,cury;  //current position of tracker
int flag = 1;
vector<PINT> old;

void init2D(float r, float g, float b) {
	glClearColor(r,g,b,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
}

void circle(float x,float y,float r,float g,float b)  // function to draw the circle 
{
	
	float angle,tmpX,tmpY;
	double radius= 12.5;
	glColor3f(r/256,g/256,b/256);
	glBegin(GL_TRIANGLE_FAN);  // helful to draw circle
	glVertex2f(x,y);	 
	for (angle=1.0f;angle<361.0f;angle+=0.2)
	{
	    tmpX = x+sin(angle)*radius;
	    tmpY = y+cos(angle)*radius;
	    glVertex2f(tmpX,tmpY);
	} 
	glEnd();
}

void mouseActions(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {   // checking the mouse click status
		if((x>150 && x<400) && (y>200 && y<300)){           // mouse position required to start the demo
			flag=3;
		}
		else if((x>150 && x<400) && (y>350 && y<450)){       // mouse position required to start the actual game
			flag=2;
		}
		else if((x>420 && x<490) && (y>409 && y<441)){   // for exiting the application
      		exit (0);
		}
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT); 
	if(flag == 1)
	{
		float points2[4][2] = {{150,200},{400,200},{400,300},{150,300}};   // showing the option to see the "demo"
		float points3[4][2] = {{150,50},{400,50},{400,150},{150,150}};     // showing the game name "Maze Runner"
		float points4[4][2] = {{150,350},{400,350},{400,450},{150,450}};   // showing the option to "play"
		float points5[4][2] = {{420,60},{490,60},{490,90},{420,90}};   // showing the option to "Exit"
		glColor3f(0/256,0/256,0/256);
		glBegin(GL_POLYGON);
		for(int i =0 ;i < 4;i++){
			glVertex2f(points1[i][0],points1[i][1]);  //drawing the outer boundary
		}
		glEnd();
		glColor3f(255.0/256,255.0/256,0.0/256);
		glBegin(GL_LINE_LOOP);
		for(int i =0 ;i < 4;i++){
			glVertex2f(points2[i][0],points2[i][1]);  // drawing the demo option box
		}
		glEnd();
		glBegin(GL_LINE_LOOP);
		for(int i =0 ;i < 4;i++){
			glVertex2f(points3[i][0],points3[i][1]);   // drawing the game option box
		}
		glEnd();
		glBegin(GL_LINE_LOOP);
		for(int i =0 ;i < 4;i++){
			glVertex2f(points4[i][0],points4[i][1]);   // drawing the box for game name 
		}
		glEnd();
		glBegin(GL_LINE_LOOP);
		for(int i =0 ;i < 4;i++){
			glVertex2f(points5[i][0],points5[i][1]);   // drawing the box for exit
		}
		glEnd();

		glColor3f(255.0/256,255.0/256,0.0/256);
		
		char m1[100] = "See the demo";
		char m2[100] = "Play the challenge";
		char m3[100] = "Maze Runner";
		char m4[100] = "Exit";

		// writing the names in the boxes drawn above
		int l1 = (int)strlen(m1);
		glRasterPos2f(200,250);
		for(int i = 0 ; i < l1; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,m1[i]);  
		int l2 = (int)strlen(m2);
		glRasterPos2f(180,100);
		for(int i = 0 ; i < l2; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,m2[i]);
		int l4 = (int)strlen(m4);
		glRasterPos2f(432,70);
		for(int i = 0 ; i < l4; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,m4[i]);
		int l3 = (int)strlen(m3);
		glRasterPos2f(200,400);
		for(int i = 0 ; i < l3; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,m3[i]);
		glFlush();
	
	}
	if(flag == 2)   // game option is chosen
	{
		system("g++ bfs.cpp");
		system("./a.out");
		system("g++ game.cpp -lGL -lGLU -lglut");  
		system("./a.out");
		flag = 1;
	}
	if(flag == 3)  // demo option is chosen
	{
		system("g++ bfs.cpp");
		system("./a.out");
		system("g++ demo.cpp -lGL -lGLU -lglut");  
		system("./a.out");
		flag = 1;
	}
	glutPostRedisplay();
	
}
void keys(unsigned char key,int x,int y)
{
  
  switch(key)
  {
  
    
 case 113:
  
      glutDestroyWindow(glutGetWindow());
  break;
     glFlush(); 
  }

}
int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(150, 400);
	glutCreateWindow("Maze Runner");
	init2D(105.0/256,240.0/256,174.0/256);
	glutDisplayFunc(display);
	glutMouseFunc(mouseActions);
	glutKeyboardFunc(keys);
	glutMainLoop();
	return 0;
}