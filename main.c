#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

static int window;
static int menu_id;
static int submenu_id;

int maximum = 15;
int difficulty = 500;

int m[15][15];
int m2[15][15];
int points = 0;

typedef struct node{
	int rot;
	float type;
	int x[4];
	int y[4];
	float color[3];
} node;

node *tet;
void drawTextTimes(char* string,float x, float y)
{
	glColor3f(0,1,1);
	int len, i;
	glRasterPos2f(x,y);
	len=(int) strlen(string);
	for(i = 0; i < len; i++)
	{
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
	}
}
void drawTextHel(char* string,float x, float y)
{
	glColor3f(0,0.4,0);
	int len, i;
	glRasterPos2f(x,y);
	len=(int) strlen(string);
	for(i = 0; i < len; i++)
	{
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,string[i]);
	}
}
void type(node *n){
	if(n -> type == 0){
		//Z tetrimino
		n -> x[0] = 6;
		n -> y[0] = -1;
		n -> x[1] = 7;
		n -> y[1] = -1;
		n -> x[2] = 7;
		n -> y[2] = 0;
		n -> x[3] = 8;
		n -> y[3] = 0;
		n -> color[0] = 0.5;
		n -> color[1] = 1;
		n -> color[2] = 0;
	}else if(n -> type == 1){
		//O tetrimino
		n -> x[0] = 7;
		n -> y[0] = 0;
		n -> x[1] = 8;
		n -> y[1] = 0;
		n -> x[2] = 7;
		n -> y[2] = -1;
		n -> x[3] = 8;
		n -> y[3] = -1;
		n -> color[0] = 1;
		n -> color[1] = 1;
		n -> color[2] = 0;
	}else if(n -> type == 2){
		//J tetrimino
		n -> x[0] = 7;
		n -> y[0] = 0;
		n -> x[1] = 7;
		n -> y[1] = -1;
 		n -> x[2] = 7;
		n -> y[2] = -2;
		n -> x[3] = 8;
		n -> y[3] = -2;
		n -> color[0] = 0;
		n -> color[1] = 0;
		n -> color[2] = 1;
	}else if(n -> type == 3){
		//I tetrimino
		n -> x[0] = 7;
		n -> y[0] = 0;
		n -> x[1] = 7;
		n -> y[1] = -1;
		n -> x[2] = 7;
		n -> y[2] = -2;
		n -> x[3] = 7;
		n -> y[3] = -3;
		n -> color[0] = 1;
		n -> color[1] = 0;
		n -> color[2] = 0;
	}else if(n -> type == 4){
		//S tetrimino
		n -> x[0] = 6;
		n -> y[0] = 0;
		n -> x[1] = 7;
		n -> y[1] = 0;
		n -> x[2] = 7;
		n -> y[2] = -1;
		n -> x[3] = 8;
		n -> y[3] = -1;
		n -> color[0] = 1;
		n -> color[1] = 0;
		n -> color[2] = 1;
	}else if(n -> type == 5){
		//L tetrimino
		n -> x[0] = 7;
		n -> y[0] = 0;
		n -> x[1] = 7;
		n -> y[1] = -1;
		n -> x[2] = 7;
		n -> y[2] = -2;
		n -> x[3] = 6;
		n -> y[3] = -2;
		n -> color[0] = 1;
		n -> color[1] = 0.65;
		n -> color[2] = 0;
	}else if(n -> type == 6){
        //T tetrimino
        n -> x[0] = 7;
        n -> y[0] = 0;
        n -> x[1] = 6;
        n -> y[1] = -1;
        n -> x[2] = 7;
        n -> y[2] = -1;
        n -> x[3] = 7;
        n -> y[3] = -2;
        n -> color[0] = 0;
        n -> color[1] = 1;
        n -> color[2] = 1;
	}
}
void rotate1(node *n){
	if(n -> type == 0){
		if(n -> rot == 0){
			if(m2[n -> y[0] - 1][n -> x[0]] != 1 && m2[n -> y[0] - 1][n -> x[0] + 1] != 1 && m2[n -> y[0] - 2][n -> x[0] + 1] != 1){
			if(n -> y[0] - 1 < maximum && n -> x[0] + 1 < maximum && n -> y[0] - 2 < maximum){
			if(n -> y[0] - 1 >= 0  && n -> x[0] + 1 >= 0  && n -> y[0] - 2 >= 0 ){
				n -> rot = 1;
				n -> x[1] = n -> x[0];
				n -> y[1] = n -> y[0] - 1;
				n -> x[2] = n -> x[0] + 1;
				n -> y[2] = n -> y[0] - 1;
				n -> x[3] = n -> x[0] + 1;
				n -> y[3] = n -> y[0] - 2;
			}
			}
			}
		}else{
			if(m2[n -> y[0]][n -> x[0] - 1] != 1 && m2[n-> y[0] - 1][n -> x[0] - 1] != 1 && m2[n -> y[0] - 1][n -> x[0] - 2] != 1){
			if(n -> x[0] - 1 < maximum && n-> y[0] - 1 < maximum && n -> x[0] - 2 < maximum){
			if(n -> x[0] - 1 >= 0  && n-> y[0] - 1 >= 0  && n -> x[0] - 2 >= 0 ){
				n -> rot = 0;
				n -> x[1] = n -> x[0] - 1;
				n -> y[1] = n -> y[0];
				n -> x[2] = n -> x[0] - 1;
				n -> y[2] = n -> y[0] - 1;
				n -> x[3] = n -> x[0] - 2;
				n -> y[3] = n -> y[0] - 1;
			}
			}
			}
		}
	}
	else if(n -> type == 1)
        return;
	else if(n -> type == 2){
		if(n -> rot == 0){
			if(m2[n -> y[0]][n -> x[0] - 1] != 1 && m2[n -> y[0]][n -> x[0] - 2] != 1 && m2[n -> y[0] - 1][n -> x[0] - 2] != 1){
			if(n -> y[0] - 1 < maximum && n -> x[0] - 1 < maximum && n -> x[0] - 2 < maximum){
			if(n -> y[0] - 1 >= 0  && n -> x[0] - 1 >= 1  && n -> x[0] - 2 >= 1 ){
				n -> rot = 1;
				n -> x[1] = n -> x[0] - 1;
				n -> y[1] = n -> y[0];
				n -> x[2] = n -> x[0] - 2;
				n -> y[2] = n -> y[0];
				n -> x[3] = n -> x[0] - 2;
				n -> y[3] = n -> y[0] - 1;
			}
			}
			}
		}else if(n -> rot == 1){
			if(m2[n -> y[0]][n -> x[0] - 1] != 1 && m2[n -> y[0] - 1][n -> x[0]] != 1 && m2[n -> y[0] - 2][n -> x[0]] != 1){
			if(n -> y[0] - 1 < maximum && n -> y[0] - 2 < maximum && n -> x[0] - 1 < maximum){
			if(n -> y[0] - 1 >= 0  && n -> y[0] - 2 >= 0  && n -> x[0] - 1 >= 0 ){
				n -> rot = 2;
				n -> x[1] = n -> x[0] - 1;
				n -> y[1] = n -> y[0];
				n -> x[2] = n -> x[0];
				n -> y[2] = n -> y[0] - 1;
				n -> x[3] = n -> x[0];
				n -> y[3] = n -> y[0] - 2;
			}
			}
			}
		}else if(n -> rot == 2){
			if(m2[n -> y[0] + 1][n -> x[0]] != 1 && m2[n -> y[0]][n -> x[0] - 1] != 1 && m2[n -> y[0]][n -> x[0] - 2] != 1){
			if(n -> y[0] + 1 < maximum && n -> x[0] - 1 < maximum && n -> x[0] - 2 < maximum){
			if(n -> y[0] + 1 >= 0  && n -> x[0] - 1 >= 0  && n -> x[0] - 2 >= 0){
				n -> rot = 3;
				n -> x[1] = n -> x[0];
				n -> y[1] = n -> y[0] + 1;
				n -> x[2] = n -> x[0] - 1;
				n -> y[2] = n -> y[0];
				n -> x[3] = n -> x[0] - 2;
				n -> y[3] = n -> y[0];
			}
			}
			}
		}else if(n -> rot == 3){
			if(m2[n -> y[0] - 1][n -> x[0]] != 1 && m2[n -> y[0] - 2][n -> x[0]] != 1 && m2[n -> y[0] - 2][n -> x[0] + 1] != 1){
			if(n -> y[0] - 1 < maximum && n -> x[0] + 1 < maximum && n -> y[0] - 2 < maximum){
			if(n -> y[0] - 1 >= 0  && n -> x[0] + 1 >= 0  && n -> y[0] - 2 >= 0){
				n -> rot = 0;
				n -> x[1] = n -> x[0];
				n -> y[1] = n -> y[0] - 1;
				n -> x[2] = n -> x[0];
				n -> y[2] = n -> y[0] - 2;
				n -> x[3] = n -> x[0] + 1;
				n -> y[3] = n -> y[0] - 2;
			}
			}
			}
		}
	}else if(n -> type == 3){
		if(n -> rot == 0){
			if(m2[n -> y[0]][n -> x[0] - 1] != 1 && m2[n -> y[0]][n -> x[0] + 1] != 1 && m2[n -> y[0]][n -> x[0] + 2] != 1){
			if(n -> x[0] - 1 < maximum && n -> x[0] + 1 < maximum && n -> x[0] + 2 < maximum){
			if(n -> x[0] - 1 >= 0  && n -> x[0] + 1 >= 0  && n -> x[0] + 2 >= 0 ){
			n -> rot = 1;
			n -> x[1] = n -> x[0] - 1;
			n -> y[1] = n -> y[0];
			n -> x[2] = n -> x[0] + 1;
			n -> y[2] = n -> y[0];
			n -> x[3] = n -> x[0] + 2;
			n -> y[3] = n -> y[0];
			}
			}
			}
		}else{
			if(m2[n -> y[0] - 1][n -> x[0]] != 1 && m2[n -> y[0] - 2][n -> x[0]] != 1 && m2[n -> y[0] - 3][n -> x[0]] != 1){
			if(n -> y[0] - 1 < maximum && n -> y[0] - 2 < maximum && n -> y[0] - 3 < maximum){
			if(n -> y[0] - 1 >= 0  && n -> y[0] - 2 >= 0  && n -> y[0] - 3 >= 0 ){
			n -> rot = 0;
			n -> x[1] = n -> x[0];
			n -> y[1] = n -> y[0] - 1;
			n -> x[2] = n -> x[0];
			n -> y[2] = n -> y[0] - 2;
			n -> x[3] = n -> x[0];
			n -> y[3] = n -> y[0] - 3;
			}
			}
			}
		}
	}else if(n -> type == 4){
		if(n -> rot == 0){
			if(m2[n -> y[0] - 1][n -> x[0]] != 1 && m2[n -> y[0] - 1][n -> x[0] - 1] != 1 && m2[n -> y[0] - 2][n -> x[0] - 1] != 1){
			if(n -> y[0] - 1 < maximum && n -> x[0] - 1 < maximum && n -> y[0] - 2 < maximum){
			if(n -> y[0] - 1 >= 0  && n -> x[0] - 1 >= 0  && n -> y[0] - 2 >= 0 ){
				n -> rot = 1;
				n -> x[1] = n -> x[0];
				n -> y[1] = n -> y[0] - 1;
				n -> x[2] = n -> x[0] - 1;
				n -> y[2] = n -> y[0] - 1;
				n -> x[3] = n -> x[0] - 1;
				n -> y[3] = n -> y[0] - 2;
			}
			}
			}
		}else{
			if(m2[n -> y[0]][n -> x[0] + 1] != 1 && m2[n-> y[0] - 1][n -> x[0] + 1] != 1 && m2[n -> y[0] - 1][n -> x[0] + 2] != 1){
			if(n -> x[0] + 1 < maximum && n-> y[0] - 1 < maximum && n -> x[0] + 2 < maximum){
			if(n -> x[0] + 1 >= 0  && n-> y[0] - 1 >= 0  && n -> x[0] + 2 >= 0 ){
				n -> rot = 0;
				n -> x[1] = n -> x[0] + 1;
				n -> y[1] = n -> y[0];
				n -> x[2] = n -> x[0] + 1;
				n -> y[2] = n -> y[0] - 1;
				n -> x[3] = n -> x[0] + 2;
				n -> y[3] = n -> y[0] - 1;
			}
			}
			}
		}
	}else if(n -> type == 5){
		if(n -> rot == 0){
			if(m2[n -> y[0]][n -> x[0] - 1] != 1 && m2[n -> y[0]][n -> x[0] - 2] != 1 && m2[n -> y[0] + 1][n -> x[0] - 2] != 1){
			if(n -> x[0] - 1 < maximum && n -> x[0] - 2 < maximum && n -> y[0] + 1 < maximum){
			if(n -> x[0] - 1 >= 0  && n -> x[0] - 2 >= 0  && n -> y[0] + 1 >= 0 ){
				n -> rot = 1;
				n -> x[1] = n -> x[0] - 1;
				n -> y[1] = n -> y[0];
				n -> x[2] = n -> x[0] - 2;
				n -> y[2] = n -> y[0];
				n -> x[3] = n -> x[0] - 2;
				n -> y[3] = n -> y[0] + 1;
			}
			}
			}
		}else if(n -> rot == 1){
			if(m2[n -> y[0]][n -> x[0] + 1] != 1 && m2[n-> y[0] - 1][n -> x[0]] != 1 && m2[n -> y[0] - 2][n -> x[0]] != 1){
			if(n -> x[0] + 1 < maximum && n -> y[0] - 1 < maximum && n -> y[0] - 2 < maximum){
			if(n -> x[0] + 1 >= 0  && n -> y[0] - 1 >= 0  && n -> y[0] - 2 >= 0 ){
				n -> rot = 2;
				n -> x[1] = n -> x[0] + 1;
				n -> y[1] = n -> y[0];
				n -> x[2] = n -> x[0];
				n -> y[2] = n -> y[0] - 1;
				n -> x[3] = n -> x[0];
				n -> y[3] = n -> y[0] - 2;
			}
			}
			}
		}else if(n -> rot == 2){
			if(m2[n -> y[0]][n -> x[0] - 1] != 1 && m2[n-> y[0] - 1][n -> x[0]] != 1 && m2[n -> y[0]][n -> x[0] - 2] != 1){
			if(n -> x[0] - 1 < maximum && n -> y[0] - 1 < maximum && n -> x[0] - 2 < maximum){
			if(n -> x[0] - 1 >= 0  && n -> y[0] - 1 >= 0  && n -> x[0] - 2 >= 0 ){
				n -> rot = 3;
				n -> x[1] = n -> x[0];
				n -> y[1] = n -> y[0] - 1;
				n -> x[2] = n -> x[0] - 1;
				n -> y[2] = n -> y[0];
				n -> x[3] = n -> x[0] - 2;
				n -> y[3] = n -> y[0];
			}
			}
			}
		}else if(n -> rot == 3){
			if(m2[n -> y[0] - 1][n -> x[0]] != 1 && m2[n-> y[0] - 2][n -> x[0]] != 1 && m2[n -> y[0] - 2][n -> x[0] - 1] != 1){
			if(n -> x[0] - 1 < maximum && n -> y[0] - 1 < maximum && n -> y[0] - 2 < maximum){
			if(n -> x[0] - 1 >= 0  && n -> y[0] - 1 >= 0  && n -> y[0] - 2 >= 0 ){
				n -> rot = 0;
				n -> x[1] = n -> x[0];
				n -> y[1] = n -> y[0] - 1;
				n -> x[2] = n -> x[0];
				n -> y[2] = n -> y[0] - 2;
				n -> x[3] = n -> x[0] - 1;
				n -> y[3] = n -> y[0] - 2;
			}
			}
			}
		}
	}else if(n -> type == 6){
        if(n -> rot == 0){
            if(m2[n -> y[0]][n -> x[0] - 1] != 1 && m2[n -> y[0]][n -> x[0] + 1] != 1 && m2[n -> y[0] + 1][n -> x[0]] != 1){
            if(n -> y[0] + 1 < maximum && n -> x[0] + 1 < maximum && n -> x[0] - 1 < maximum){
            if(n -> y[0] + 1 >= 0 && n -> x[0] + 1 >= 0 && n -> x[0] - 1 >=0){
                n -> rot = 1;
                n -> x[1] = n -> x[0] - 1;
                n -> y[1] = n -> y[0];
                n -> x[2] = n -> x[0] + 1;
                n -> y[2] = n -> y[0];
                n -> x[3] = n -> x[0];
                n -> y[3] = n -> y[0] + 1;
            }
            }
            }
        }else if(n -> rot == 1){
            if(m2[n -> y[0] - 1][n -> x[0]] != 1 && m2[n -> y[0]][n -> x[0] + 1] !=1 && m2[n -> y[0] + 1][n -> x[0]] != 1){
            if(n -> x[0] + 1 < maximum && n -> y[0] -1 < maximum && n -> y[0] + 1 < maximum){
            if(n -> x[0] + 1 >= 0 && n -> y[0] - 1 >= 0 && n -> y[0] + 1 >=0){
                n -> rot = 2;
                n -> x[1] = n -> x[0] + 1;
                n -> y[1] = n -> y[0];
                n -> x[2] = n -> x[0];
                n -> y[2] = n -> y[0] + 1;
                n -> x[3] = n -> x[0];
                n -> y[3] = n -> y[0] - 1;
            }
            }
            }
        }else if(n -> rot == 2){
            if(m2[n -> y[0] - 1][n -> x[0]] != 1 && m2[n -> y[0]][n -> x[0] + 1] != 1 && m2[n -> y[0]][n -> x[0] - 1] != 1){
            if(n -> y[0] - 1 < maximum && n -> x[0] - 1 < maximum && n -> x[0] + 1 < maximum){
            if(n -> y[0] - 1 >= 0 && n -> x[0] - 1 >=0 && n -> x[0] + 1 >=0){
                n -> rot =3;
                n -> x[1] = n -> x[0] - 1;
                n -> y[1] = n -> y[0];
                n -> x[2] = n -> x[0] + 1;
                n -> y[2] = n -> y[0];
                n -> x[3] = n -> x[0];
                n -> y[3] = n -> y[0] - 1;
            }
            }
            }
        }else if(n -> rot ==3){
            if(m2[n -> y[0] + 1][n -> x[0]] != 1 && m2[n -> y[0]][n -> x[0] - 1] != 1 && m2[n -> y[0] - 1][n -> x[0]] != 1){
            if(n -> y[0] + 1 < maximum && n -> x[0] - 1 < maximum && n -> y[0] - 1 < maximum){
            if(n -> y[0] + 1 >= 0 && n-> x[0] - 1 >= 0 && n -> y[0] - 1 >=0){
                n -> rot =0;
                n -> x[1] = n -> x[0] - 1;
                n -> y[1] = n -> y[0];
                n -> x[2] = n -> x[0];
                n -> y[2] = n -> y[0] + 1;
                n -> x[3] = n -> x[0];
                n -> y[3] = n -> y[0] - 1;
            }
            }
            }
        }
	}
}
void init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glLoadIdentity ();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	GLfloat acolor[] = {1.4, 1.4, 1.4, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, acolor);
}
void marg(node *n){
	int i;
	for(i = 0; i < 4; i++){
		if(n -> y[i] >= 0 && n -> x[i] >= 0 && n -> y[i] < maximum && n -> x[i] < maximum)
			m[n -> y[i]][n -> x[i]] = 1;
	}
}
void movex(node *n){
	int i;
	for(i = 0; i < 4; i++){
		n -> y[i] += 1;
	}
}
void back1(){
	int  i, j;
	for(i = 0; i < maximum; i++){
		for(j = 0; j < maximum; j++){
			m[i][j] = m2[i][j];
		}
	}
}
void Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w/(double)h, 0.1, 200.0);
}
void border(float x1, float y1, float z1, float w){
	glColor3fv(tet -> color);
	glBegin(GL_QUADS);
        glVertex3f(x1, y1, z1);
        glVertex3f(x1 - 2*w + 0.02, y1, z1);
        glVertex3f(x1 - 2*w + 0.02, y1 + 0.01, z1);
        glVertex3f(x1, y1 + 0.01, z1);
	glEnd();
	glBegin(GL_QUADS);
        glVertex3f(x1, y1 + 2*w, z1);
        glVertex3f(x1 - 2*w + 0.02, y1 + 2*w, z1);
        glVertex3f(x1 - 2*w + 0.02, y1 + 2*w + 0.01, z1);
        glVertex3f(x1, y1 + 2*w + 0.01, z1);
	glEnd();
	glBegin(GL_QUADS);
        glVertex3f(x1, y1, z1);
        glVertex3f(x1 + 0.01, y1, z1);
        glVertex3f(x1 + 0.01, y1 + 2*w, z1);
        glVertex3f(x1, y1 + 2*w, z1);
	glEnd();
	glBegin(GL_QUADS);
        glVertex3f(x1 - 2*w + 0.01, y1, z1);
        glVertex3f(x1 - 2*w + 0.02, y1, z1);
        glVertex3f(x1 - 2*w + 0.02, y1 + 2*w, z1);
        glVertex3f(x1 - 2*w + 0.01, y1 + 2*w, z1);
	glEnd();
}
void borderexit(float x1, float y1, float z1, float w){
	glColor3f(1,1,0);
	glBegin(GL_QUADS);
        glVertex3f(x1, y1, z1);
        glVertex3f(x1 - 2*w + 0.02, y1, z1);
        glVertex3f(x1 - 2*w + 0.02, y1 + 0.01, z1);
        glVertex3f(x1, y1 + 0.01, z1);
	glEnd();
	glBegin(GL_QUADS);
        glVertex3f(x1, y1 + 2*w, z1);
        glVertex3f(x1 - 2*w + 0.02, y1 + 2*w, z1);
        glVertex3f(x1 - 2*w + 0.02, y1 + 2*w + 0.01, z1);
        glVertex3f(x1, y1 + 2*w + 0.01, z1);
	glEnd();
	glBegin(GL_QUADS);
        glVertex3f(x1, y1, z1);
        glVertex3f(x1 + 0.01, y1, z1);
        glVertex3f(x1 + 0.01, y1 + 2*w, z1);
        glVertex3f(x1, y1 + 2*w, z1);
	glEnd();
	glBegin(GL_QUADS);
        glVertex3f(x1 - 2*w + 0.01, y1, z1);
        glVertex3f(x1 - 2*w + 0.02, y1, z1);
        glVertex3f(x1 - 2*w + 0.02, y1 + 2*w, z1);
        glVertex3f(x1 - 2*w + 0.01, y1 + 2*w, z1);
	glEnd();
}
void keyboardexit(unsigned char key, int x, int y)
{
	if(key == 27) {
		exit(0);
	}
        glutPostRedisplay();
}
void exitscreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();
	glTranslatef(0.0, 0.0, -2.0);
	glColor3f(1,1,1);
	float bo = -0.1*(maximum/2.0f);
	borderexit(bo - 0.01, -bo - 0.01,0.0, bo);
	drawTextTimes("GAME OVER",-0.2,0.3);
	char score[10];
	sprintf(score, "%d", points);
	char str[30] = "Your Score is: ";
	strcat(str, score);
	drawTextTimes(str,-0.25,0.1);
	drawTextHel("Developed by Saurabh Chalke & Sanjay M", -0.55, -0.6);
	glutSwapBuffers();
}
int exitscreenn()
{
	glutDestroyWindow(window);
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (0, 0);
	window=glutCreateWindow("Game Over - Saurabh Chalke & Sanjay M");
	init();
	glutDisplayFunc(exitscreen);
	glutIdleFunc(exitscreen);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyboardexit);
	glutMainLoop();
	return 0;
}
void win(){
	int i, j, k;
	for(i = 0; i < maximum; i++){
		int f = 0;
		for(j = 0; j < maximum; j++){
			if(m2[i][j] == 0) f = 1;
		}
		int l;
		if(!f){
			points = points + 30;
			for(l = i; l > 0; l--){
				for(k = 0; k < maximum; k++)
					m2[l][k] = m2[l - 1][k];
			}
			for(k = 0; k < maximum; k++)
				m2[0][k] = 0;
			back1();
			marg(tet);
			i--;
		}
	}
	for(i = 0; i < maximum; i++)
		if(m2[0][i] == 1){
                int i,j;
                for(i = 0; i < maximum; ++i)
                    for(j=0; j < maximum; ++j)
                        if(m2[i][j]==1)
                            points++;
		exitscreenn();
	}
}
void movey(node *n, int lf){
	if(lf){
		int i;
		for(i = 0; i < 4; i++){
			if(n -> x[i] + 1 > maximum - 1) return;
			if(m2[n -> y[i]][n -> x[i] + 1] == 1) return;
		}
		for(i = 0; i < 4; i++){
			n -> x[i] += 1;
		}
	}else{
		int i;
		for(i = 0; i < 4; i++){
			if(n -> x[i] - 1 < 0) return;
			if(m2[n -> y[i]][n -> x[i] - 1] == 1) return;
		}
		for(i = 0; i < 4; i++){
			n -> x[i] -= 1;
		}
	}
}

int check(node *n){
	int i, j, k, l;
	for(i = 0; i < 4; i++){
		if(m2[(n -> y[i]) + 1][n -> x[i]] == 1 || n -> y[i] == maximum - 1){
			if(n -> y[i] < 0)
				return 0;
			for(j = 0; j < 4; j++)
				m2[n -> y[j]][n -> x[j]] = 1;
			return 1;
		}
	}
	return 0;
}

void cube(float x1, float x2, float y1, float y2, float z1){
	glColor3fv(tet -> color);
	glBegin(GL_QUADS);
        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y1, z1);
        glVertex3f(x2, y2, z1);
        glVertex3f(x1, y2, z1);
	glEnd();
}



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();
	glTranslatef(0.0, 0.0, -2.0);
	int i,j;
	float x, y, z, c;
	float bo = -0.1*(maximum/2.0f);
	border(bo - 0.01, -bo - 0.01,0.0, bo);
	for(i = 0; i < maximum; i++){
		for(j = 0; j < maximum; j++){
			if(m[i][j] == 1)cube(bo + 0.1*j + 0.01, bo + 0.1*(j + 1) - 0.01, -bo - 0.1*i - 0.01, -bo - 0.1*(i + 1) + 0.01, 0.0);
		}
	}
	win();
	glutSwapBuffers();
}
void new1(){
	tet = (node *)malloc(sizeof(node));
	srand(time(NULL));
	int rx = rand() % 7;
	tet -> type = rx;
	tet -> rot = 0;
	type(tet);
}
void myIdleFunc(int a) {
	if(check(tet)){
		new1();
	}
	back1();
	marg(tet);
	movex(tet);
	glutPostRedisplay();
	glutTimerFunc(difficulty, myIdleFunc, 0);
}

void dropdown(node* n) {
    int i, j, k, l;
	for(i = 0; i < 4; i++)
	{
		if(m2[(n -> y[i]) + 1][n -> x[i]] == 1 || n -> y[i] == maximum - 1 )
		{
			return;
        }
    }
    movex(n);
    dropdown(n);
    return;
}

void keyboard(unsigned char key, int x, int y)
{
	if(key == 27) {
		printf("\n\nPoints : %d \n\n", points);
		exit(0);
	}else if((char)key == 'a'){
		movey(tet, 0);
		glutPostRedisplay();
	}else if((char)key == 'd'){
		movey(tet, 1);
		glutPostRedisplay();
	}else if((char)key == 'w'){
		rotate1(tet);
		glutPostRedisplay();
	}
	else if((char)key == 's'){
        dropdown(tet);
        glutPostRedisplay();
	}
}
void menu(int num){
	if(num == 0){
		int i,j;
                for(i = 0; i < maximum; ++i)
                    for(j=0; j < maximum; ++j)
                        if(m2[i][j]==1)
                            points++;
		exitscreenn();
	}else{
		if(num == 2){
			difficulty = 500;
		}
		else if(num == 1){
			int i, j;
			for(i = 0; i < maximum; i++)
				for(j = 0; j < maximum; j++){
					m [i][j] = 0;
					m2[i][j] = 0;
				}
			points = 0;
			difficulty = 500;
			tet = (node *)malloc(sizeof(node));
			srand(time(NULL));
			int rx = rand() % 7;
			tet -> type = rx;
			tet -> rot = 0;
			type(tet);
			marg(tet);
		}
		else if(num == 3){
			difficulty = 350;
		}
		else if(num == 4){
			difficulty = 200;
		}
	}
	glutPostRedisplay();
} 
void createMenu(void){     
	submenu_id = glutCreateMenu(menu);
	glutAddMenuEntry("Easy", 2);
	glutAddMenuEntry("Medium", 3);
	glutAddMenuEntry("Hard", 4);
	menu_id = glutCreateMenu(menu);
	glutAddSubMenu("Difficulty", submenu_id);
	glutAddMenuEntry("Restart", 1);
	glutAddMenuEntry("Quit", 0);     
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc, char** argv)
{
	int i, j;
	for(i = 0; i < maximum; i++)
		for(j = 0; j < maximum; j++){
			m [i][j] = 0;
			m2[i][j] = 0;
		}
	tet = (node *)malloc(sizeof(node));
	srand(time(NULL));
	int rx = rand() % 7;
	tet -> type = rx;
	tet -> rot = 0;
	type(tet);
	marg(tet);
	glutInit(&argc,argv);
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	window = glutCreateWindow("Tetris - Saurabh Chalke & Sanjay M");
	init();
	glutTimerFunc(difficulty, myIdleFunc, 0);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc( keyboard );
	glutDisplayFunc(display);
	createMenu();
	glutMainLoop();
}
