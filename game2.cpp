#include <bits/stdc++.h>
#include <unistd.h>
#include <GL/glut.h>
#include <ctime>
#define mp make_pair
#define PINT pair<int,int>
using namespace std;
int path[100][2], increment=0;
float points[4][2] = {{50,50},{450,50},{450,450},{50,450}};
int pathctr;
float obstacle[17][17];
int sx,sy,dx,dy;
int curx,cury;
vector<PINT> old;
int nextlevel=0;

time_t start,end;

void init2D(float r, float g, float b) {
	glClearColor(r,g,b,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
}

void scoreString(int score,char* s){
	vector<int> vec;
	while(score!=0){
		int xx=score%10;
		vec.push_back(xx);
		score/=10;
	}
	int ind=13;
	for(int i=vec.size()-1;i>=0;i--){
		char ch='0'+vec[i];
		s[ind++]=ch;
	}
	s[ind]='\0';
}

char fixScore[100];
int lenfix;

int completed=0;
int fixscore=0;
int ss=0;
void keyPressed(int key,int x,int y)   // function for controlling keyboard inputs      
{
	if (key == GLUT_KEY_RIGHT) {    // for right arrow key
		int tmpx=curx,tmpy=cury+1;
		if (obstacle[tmpx][tmpy]==0 || obstacle[tmpx][tmpy]==2 || obstacle[tmpx][tmpy]== 3 ) {
			if(obstacle[tmpx][tmpy]==3){
				system("aplay /home/jk/Jk/beep-02.wav");
				obstacle[tmpx][tmpy]=0;
				ss+=10;
			}
			curx=tmpx,cury=tmpy;
			if(curx==dx && cury==dy){
				completed=1;
				return ;
			}
			if (old.size()>=2 && old[old.size()-2]==mp(tmpx,tmpy)) {
				old.erase(old.end()-1);
				return;
			}
			old.push_back(mp(tmpx,tmpy));
		}
	}

	else if (key == GLUT_KEY_LEFT) {  // for left arrow key
		int tmpx=curx,tmpy=cury-1;
		if (obstacle[tmpx][tmpy]==0 || obstacle[tmpx][tmpy]==2 || obstacle[tmpx][tmpy]== 3) {
			if(obstacle[tmpx][tmpy]==3){
				obstacle[tmpx][tmpy]=0;
				system("aplay /home/jk/Jk/beep-02.wav");
				ss+=10;
			}
			curx=tmpx,cury=tmpy;
			if(curx==dx && cury==dy){
				completed=1;
				return ;
			}
			if (old.size()>=2 && old[old.size()-2]==mp(tmpx,tmpy)) {
				old.erase(old.end()-1);
				return;
			}
			old.push_back(mp(tmpx,tmpy));
		}
	}

	else if (key == GLUT_KEY_UP) {  // for up arrow key
		int tmpx=curx+1,tmpy=cury;
		if (obstacle[tmpx][tmpy]==0 || obstacle[tmpx][tmpy]==2|| obstacle[tmpx][tmpy]== 3) {
			if(obstacle[tmpx][tmpy]==3){
				obstacle[tmpx][tmpy]=0;
				system("aplay /home/jk/Jk/beep-02.wav");
				ss+=10;
			}
			curx=tmpx,cury=tmpy;
			if(curx==dx && cury==dy){
				completed=1;
				return ;
			}
			if (old.size()>=2 && old[old.size()-2]==mp(tmpx,tmpy)) {
				old.erase(old.end()-1);
				return;
			}
			old.push_back(mp(tmpx,tmpy));
		}
	}

	else if (key == GLUT_KEY_DOWN) {  // for down arrow key 
		int tmpx=curx-1,tmpy=cury;
		if (obstacle[tmpx][tmpy]==0 || obstacle[tmpx][tmpy]==2|| obstacle[tmpx][tmpy]== 3) {
			if(obstacle[tmpx][tmpy]==3){
				obstacle[tmpx][tmpy]=0;
				system("aplay /home/jk/Jk/beep-02.wav");
				ss+=10;
			}
			curx=tmpx,cury=tmpy;
			if(curx==dx && cury==dy){
				completed=1;
				return ;
			}
			if (old.size()>=2 && old[old.size()-2]==mp(tmpx,tmpy)) {
				old.erase(old.end()-1);
				return;
			}
			old.push_back(mp(tmpx,tmpy));
		}
	}
}

void circle(float x,float y,float r,float g,float b)   // to draw the circle
{
	float angle,tmpX,tmpY;
	double radius= 12.5;
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

void smallCircle(float x,float y,float r,float g,float b)   // to draw the circle
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

// void mouseActions(int button, int state, int x, int y)
// {
// 	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { 
// 		if((x>420 && x<490) && (y>409 && y<441)){   // for exiting the application
//       		system("g++ bfs2.cpp");
//       		system("./a.out");
//       		system("g++ game2.cpp -lGL -lGLU -lglut");
//       		system("./a.out");
// 		}
// 	}
// }

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(105.0/256,240.0/256,174.0/256);
	glBegin(GL_POLYGON);
	for(int i =0 ;i < 4;i++){
		glVertex2f(points[i][0],points[i][1]);
	}
	glEnd();
	float x1,y1,x2,y2;
	int tmpX,tmpY;
	float x,y;
	float angle;
	for(int i =1;i<=16;i++)
	{
		for(int j=1;j<=16;j++)
		{	
			if(obstacle[i][j] == 1)
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
			if(obstacle[i][j] == 3 )
			{
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
				for (angle=1.0f;angle<361.0f;angle+=0.2)
				{
				    tmpX = x+sin(angle)*radius;
				    tmpY = y+cos(angle)*radius;
				    glVertex2f(tmpX,tmpY);
				} 
				glEnd();
			}
		}
		// glutPostRedisplay();
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

	float points5[4][2] = {{420,60},{490,60},{490,90},{420,90}}; 

	int cou=1;  
	for (int i=old.size()-1;i>=0;i--) {   // drawing the snake
		x1 = 50 + 25*(old[i].second- 1); 
		x2 = 50 + 25*(old[i].second);
		y1 = 50 + 25*(old[i].first- 1);
		y2 = 50 + 25*(old[i].first);
		x1 = (x1+x2)/2.0,y1=(y1+y2)/2.0;	
		if (i==old.size()-1){
			circle(x1,y1,241.0,196.0,15.0);
			smallCircle(x1+5,y1+5,102.0,51.0,0.0); // for face of snake
		}
		else 
			circle(x1,y1,101.0,31.0,255.0);
		cou++;
		if(cou==7)
			break;
	}

	// if(nextlevel==1){
	// 	glBegin(GL_LINE_LOOP);
	// 	for(int i =0 ;i < 4;i++){
	// 		glVertex2f(points5[i][0],points5[i][1]);   // drawing the box for exit
	// 	}
	// 	glEnd();
	// 	char m4[100]="Next ";

	// 	int l4 = (int)strlen(m4);
	// 	glRasterPos2f(432,70);
	// 	for(int i = 0 ; i < l4; i++)
	// 		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,m4[i]);
	// }

	if(completed==1){
		if(fixscore==0){
			// nextlevel=1;
			system("aplay /home/jk/Jk/beep-03.wav");
			end=time(0);
			int score=1000-((end-start)*10);
			char m[100]="Your Score : ";
			score+=ss;
			scoreString(score,m);
			fixscore=1;
			int l = (int)strlen(m);
			for(int i=0;i<l;i++)
				fixScore[i]=m[i];
			fixScore[l]='\0';
			lenfix=l;
		}
		glColor3f(256.0/256,0.0/256,0.0/256);
		glRasterPos2f(200,250);
		int j;
		for(j = 0 ; j < lenfix; j++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,fixScore[j]);


		char m1[100]="Exiting in 3 Seconds ";
		int l = (int)strlen(m1);
		glColor3f(256.0/256,0.0/256,0.0/256);
		glRasterPos2f(120,40);
		for(j = 0 ; j < l; j++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,m1[j]);

		glFlush();
	
		sleep(2);
		glutPostRedisplay();
		glutDestroyWindow(glutGetWindow());
	}
	glFlush();
	usleep(10000);
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
	start = time(0);

	glutInit(&argc, argv);
	freopen("game.txt","r",stdin);
	for(int i=16;i>=1;i--)
	{
		for(int j=1;j<=16;j++)
		{
			cin >> obstacle[i][j];
		}
	}
	cin>>sx>>sy>>dx>>dy;
	curx=sx,cury=sy;
	old.push_back(mp(curx,cury));
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(150, 400);
	glutCreateWindow("Pathfinder");
	init2D(105.0/256,240.0/256,174.0/256);
	glutDisplayFunc(display);
	glutSpecialFunc(keyPressed);	
	glutKeyboardFunc(keys);
	glutMainLoop();
	return 0;
}