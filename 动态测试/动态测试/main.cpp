
#define _CRT_SECURE_NO_WARNINGS      

#include <stdio.h>      
#include <string.h>      
#include<time.h>    
#include <stdlib.h>    
#include"test.h"      
#include"fluid.h"

# define  white  1.0 ,  1.0  ,  1.0   // ����ɫ�ĺ궨��
# define  green  0.0 ,  0.502,  0.0
# define  red    0.8 ,  0.0  ,  0.0
# define  gray   0.502, 0.502,0.502
# define  hgray  0.117, 0.180,0.227
# define  blue   0.0  , 0.0  ,  1.0
# define  pi  3.14159265
# define  gold   1.0,215.0/255.0,0.0
# define  hgreen 0.0,100.0/255.0,0.0
# define  brown  210.0/255.0, 105.0/255.0,  30.0/255.0
# define  nbrown 128.0/255.0, 64.0/255.0, 64.0/255.0
# define  men   244.0/255.0 ,164.0/255.0 , 96.0/255.0
# define  menba   139.0/255.0 ,69.0/255.0,19.0/255.0
# define water 141.0/255.0, 193.0/255.0, 241.0/255.0
# define orange 255.0/255.0, 128.0/255.0, 0.0/255.0
# define sunshine 255.0/255.0, 210.0/255.0, 166.0/255.0

//��������  
GLuint texture[13];

//����      
float whRatio;
int wHeight = 0;
int wWidth = 0;
//����
Fluid *f;

//�ӵ�      
float center[] = { 27, 10, 0 };
float eye[] = { 27, -50, 50 };

double fang[8][3];             // ���峤�����8������
// ����constract����  �������������������ĵ�ʱ��
// ���������7������ ����ֵ��fang

void drawScene()
{
	static int count = 0;
	count++;
	if (count > 1000) {
		count = 0;
		f->Evaluate();
	}
	f->draw();
}

void updateView(int height, int width)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);//���þ���ģʽΪͶӰ       
	glLoadIdentity();   //��ʼ������Ϊ��λ����          
	whRatio = (GLfloat)width / (GLfloat)height;  //������ʾ����     
	gluPerspective(45.0f, whRatio, 1.0f, 150.0f); //͸��ͶӰ        
	//glFrustum(-3, 3, -3, 3, 3,100);      
	glMatrixMode(GL_MODELVIEW);  //���þ���ģʽΪģ��    
}

void reshape(int width, int height)
{
	if (height == 0)      //����߶�Ϊ0          
	{
		height = 1;   //�ø߶�Ϊ1��������ַ�ĸΪ0������          
	}

	wHeight = height;
	wWidth = width;

	updateView(wHeight, wWidth); //�����ӽ�          
}


void idle()
{
	glutPostRedisplay();
}


void init()
{
	srand(unsigned(time(NULL)));
	glEnable(GL_DEPTH_TEST);//������Ȳ���       

	glEnable(GL_LIGHTING);  //��������ģʽ       

	//	Fluid(long n, long m, float d, float t, float c, float mu);

	glGenTextures(1, texture);
	loadTex(0, "D://code//VS code//��̬����//water.bmp", texture);
	/*
	n = 10
	m = 10
	d = 1
	t = 1
	c = 0.5
	u = 0
	*/
	f = new Fluid(10, 10, 5, 2, 0.5, 0, texture[0]);
}

void constract(double x, double y, double z, double x1, double y1, double z1){ //������
	fang[0][0] = x;
	fang[0][1] = y;
	fang[0][2] = z;        //  ��0����

	fang[1][0] = x;
	fang[1][1] = y;
	fang[1][2] = z + z1;     //  ��һ����

	fang[2][0] = x + x1;
	fang[2][1] = y;
	fang[2][2] = z + z1;     //  �ڶ�����

	fang[3][0] = x + x1;
	fang[3][1] = y;
	fang[3][2] = z;        //  ��������
	for (int i = 0; i<4; i++){  // for()ѭ�������������ĸ���
		for (int j = 0; j<3; j++){
			if (j == 1)
				fang[i + 4][j] = fang[i][j] + y1;
			else
				fang[i + 4][j] = fang[i][j];
		}
	}
}

void build(){
	glBegin(GL_POLYGON);
	//glColor3f(red);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(fang[0][0], fang[0][1], fang[0][2]);
	glVertex3f(fang[1][0], fang[1][1], fang[1][2]);
	glVertex3f(fang[2][0], fang[2][1], fang[2][2]);
	glVertex3f(fang[3][0], fang[3][1], fang[3][2]);
	glEnd();   //     �µ�

	glBegin(GL_POLYGON);
	//glColor3f(green);
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(fang[1][0], fang[1][1], fang[1][2]);
	glVertex3f(fang[0][0], fang[0][1], fang[0][2]);
	glVertex3f(fang[4][0], fang[4][1], fang[4][2]);
	glVertex3f(fang[5][0], fang[5][1], fang[5][2]);
	glEnd();   //     ����

	glBegin(GL_POLYGON);
	//glColor3f(green);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(fang[7][0], fang[7][1], fang[7][2]);
	glVertex3f(fang[6][0], fang[6][1], fang[6][2]);
	glVertex3f(fang[2][0], fang[2][1], fang[2][2]);
	glVertex3f(fang[3][0], fang[3][1], fang[3][2]);
	glEnd();   //     ����

	glBegin(GL_POLYGON);
	//glColor3f(green);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(fang[5][0], fang[5][1], fang[5][2]);
	glVertex3f(fang[6][0], fang[6][1], fang[6][2]);
	glVertex3f(fang[2][0], fang[2][1], fang[2][2]);
	glVertex3f(fang[1][0], fang[1][1], fang[1][2]);
	glEnd();   //     ǰ��

	glBegin(GL_POLYGON);
	//glColor3f(green);
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(fang[0][0], fang[0][1], fang[0][2]);
	glVertex3f(fang[3][0], fang[3][1], fang[3][2]);
	glVertex3f(fang[7][0], fang[7][1], fang[7][2]);
	glVertex3f(fang[4][0], fang[4][1], fang[4][2]);
	glEnd();   //     ����

	glBegin(GL_POLYGON);
	//glColor3f(red);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(fang[4][0], fang[4][1], fang[4][2]);
	glVertex3f(fang[7][0], fang[7][1], fang[7][2]);
	glVertex3f(fang[6][0], fang[6][1], fang[6][2]);
	glVertex3f(fang[5][0], fang[5][1], fang[5][2]);
	glEnd();   //     ����
}

void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����ɫ����Ȼ���        
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();   //��ʼ������Ϊ��λ����          
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0, 1, 0);                // ������0��0��0)��Y������      
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	// ���ù��ռ���    
	glEnable(GL_LIGHTING);
	// ָ��������ǿ�ȣ�RGBA��    
	GLfloat ambientLight[] = { 2.0f, 2.0f, 2.0f, 1.0f };

	// ���ù���ģ�ͣ���ambientLight��ָ����RGBAǿ��ֵӦ�õ�������    
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	// ������ɫ׷��    
	glEnable(GL_COLOR_MATERIAL);
	// ���ö��������Ļ������ɢ���������ԣ�׷��glColor    
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);




	drawScene();//���Ƴ��� 	
	//
	//////****************************���ӵ���װ壨��ɫΪ ��ɫ��********
	//glBegin(GL_POLYGON);
	//constract(-200, 0, -200, 1100, 10, 800);
	//glColor3f(green);
	//build();

	//////****************************���Ӵ�ز�********
	//glBegin(GL_POLYGON);
	//constract(-200, -5, -200, 1100, 1, 900);
	//glColor3f(nbrown);
	//build();      
	glutSwapBuffers();//����������      
}

int main(int argc, char *argv[])
{

	glutInit(&argc, argv);//��glut�ĳ�ʼ��             
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	//��ʼ����ʾģʽ:RGB��ɫģ�ͣ���Ȳ��ԣ�˫����               
	glutInitWindowSize(500, 500);//���ô��ڴ�С             
	int windowHandle = glutCreateWindow("Simple GLUT App");//���ô��ڱ���               
	glutDisplayFunc(redraw); //ע����ƻص�����             
	glutReshapeFunc(reshape);   //ע���ػ�ص�����             

	glutIdleFunc(idle);//ע��ȫ�ֻص�����������ʱ����           

	init();
	glutMainLoop();  // glut�¼�����ѭ��           
	return 0;
}