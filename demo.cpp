#include <bits/stdc++.h>
#include <unistd.h>
#include <GL/glut.h>
using namespace std;
float obstacle[17][17];
int sx,sy,dx,dy;
int curx,cury;

void init2D(float r, float g, float b){
	glClearColor(r,g,b,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
}

void circle(float x1,float y1,float  r,float g,float b) 
{
	
	float angle,x2,y2;
	double radius= 12.5;
	glColor3f(r/256,g/256,b/256);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1,y1);
	 
	for (angle=1.0f;angle<361.0f;angle+=0.2)
	{
	    x2 = x1+sin(angle)*radius;
	    y2 = y1+cos(angle)*radius;
	    glVertex2f(x2,y2);
	} 
	glEnd();
}

void smallCircle(float x,float y,float r,float g,float b)   // to draw the small circle
{
	float angle,tmpX,tmpY;
	double radius= 5;
	glColor3f(r/256,g/256,b/256);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x,y);	 
	for (angle=1.0f;angle<361.0f;angle+=0.2)
	{
	    tmpX = x+sin(angle)*radius;
	    tmpY = y+cos(angle)*radius;
	    glVertex2f(tmpX,tmpY);
	} 
	glEnd();
}

void mouseActions(int button, int state, int x, int y) // just to check the coordinates
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {   
		cout<<x<<" "<<y<<endl;
	}
}

int path[100][2], increment=0;  // for storing the ponits where snake is there
float points[4][2] = {{50,50},{450,50},{450,450},{50,450}}; // outer boundary of matrix
int pathctr; 

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(105.0/256,240.0/256,174.0/256);
	glBegin(GL_POLYGON);
	for(int i =0 ;i < 4;i++){
		glVertex2f(points[i][0],points[i][1]);
	}
	glEnd();
	float x1,y1,x2,y2;
	
	for(int i =1;i<=16;i++)
	{
		for(int j=1;j<=16;j++)
		{	
			if(obstacle[i][j] == 1 )
			{
				x1 = 50 + 25*(j - 1);
				x2 = 50 + 25*(j);
				y1 = 50 + 25*(i- 1);
				y2 = 50 + 25*(i);
				glColor3f(0.0/256,200.0/256,83.0/256);
				glBegin(GL_POLYGON);
				glVertex2f(x1,y1);
				glVertex2f(x2,y1);
				glVertex2f(x2,y2);
				glVertex2f(x1,y2);
				
				glEnd();
			}	
			if(obstacle[i][j] == 3 ){
				float x1,x2,y1,y2,x,y,tmpX,tmpY;
			x1 = 50 + 25*(j - 1);
				x2 = 50 + 25*(j);
				y1 = 50 + 25*(i- 1);
				y2 = 50 + 25*(i);
				x=(x1+x2)/2;
				y=(y1+y2)/2;
				glColor3f(179.0/256,143.0/256,0.0/256);
				glBegin(GL_TRIANGLE_FAN);
				glVertex2f(x,y);	 
				double radius= 10;
				for (float angle=1.0f;angle<361.0f;angle+=0.2)
				{
				    tmpX = x+sin(angle)*radius;
				    tmpY = y+cos(angle)*radius;
				    glVertex2f(tmpX,tmpY);
				} 
				glEnd();	
			}
		}

	}
	x1 = 50 + 25*(sy-1);
	x2 = 50 + 25*(sy);
	y1 = 50 + 25*(sx-1);
	y2 = 50 + 25*(sx);
	x1 = (x1+x2)/2.0,y1=(y1+y2)/2.0;	
	circle(x1,y1,255.0,23.0,68.0);  // drawing the source

	x1 = 50 + 25*(dy - 1);
	x2 = 50 + 25*(dy);
	y1 = 50 + 25*(dx- 1);
	y2 = 50 + 25*(dx);
	glColor3f(256.0/256,0.0/256,0.0/256); //drawing  the destination
	glBegin(GL_POLYGON);
	
	glVertex2f(x1+3,y2-10);
	glVertex2f((x1+x2)/2,y2-2);	
	glVertex2f(x2-3,y2-10);
		
	glEnd();

	glColor3f(0.0/256,0.0/256,256.0/256);
	glBegin(GL_POLYGON);
	glVertex2f(x1+6,y2-10);
	glVertex2f(x2-6,y2-10);
	glVertex2f(x2-6,y2-20);	
	glVertex2f(x1+6,y2-20);		
	glEnd();
		
	int cou=1;
	
	
	for(int i=increment-1;i>=0;i--)   // drawing snake for demo
	{
		cout<<"increment:"<<increment<<"\n";
		
		x1 = 50 + 25*(path[i][1] - 1);
		x2 = 50 + 25*(path[i][1]);
		y1 = 50 + 25*(path[i][0]- 1);
		y2 = 50 + 25*(path[i][0]);		
		x1 = (x1+x2)/2.0,y1=(y1+y2)/2.0;
		circle(x1,y1,101.0,31.0,255.0); 
		if (i==increment-1){
			circle(x1,y1,241.0,196.0,15.0);
			smallCircle(x1+5,y1+5,102.0,51.0,0.0); // for face of snake
		}
		else {
			circle(x1,y1,101.0,31.0,255.0);
		}

		cou++;

		if(i==increment-1){
			if(obstacle[path[i][0]][path[i][1]] == 3 ) {
				obstacle[path[i][0]][path[i][1]]=0;
				system("aplay /home/jk/Jk/beep-02.wav");
			}
			if(increment==20){
				sleep(2);
				glutDestroyWindow(glutGetWindow());
			}
		}
		
		
		if(cou==7)
			break;
	}
	glFlush();
	
	if (increment++<pathctr) {
		usleep(700000); // for the delay
		usleep(10000);
		glutPostRedisplay();
	}
}

int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	freopen("maze.txt","r",stdin);  // for getting the maze input
	for(int i=16;i>=1;i--)
	{
		for(int j=1;j<=16;j++)
		{
			cin >> obstacle[i][j];  
		}
	}
	cin >> pathctr ;
	for(int i =0;i<pathctr;i++)  
	{
		cin >> path[i][0] >> path[i][1] ;  // getting path coordinates
		if(i==0){
			sx=path[i][0];
			sy=path[i][1];
		}
		if(i==pathctr-1){
			dx=path[i][0];
			dy=path[i][1];
		}
	}
	cout<<pathctr<<"\n";
	for(int k=0;k<20;k++){
		
			cout<<path[k][0]<<"\n";
			cout<<path[k][1]<<"\n";
		
	}
	cout<<"======================================\n";
	for(int k=0;k<20;k++){
		cout<<obstacle[path[k][0]][path[k][1]]<<"\n" ;
			
		}
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(150, 400);
	glutCreateWindow("Maze Runner Game");
	init2D(105.0/256,240.0/256,174.0/256);
	glutDisplayFunc(display);
	glutMouseFunc(mouseActions);
	glutMainLoop();
	return 0;
}
