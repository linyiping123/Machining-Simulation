#define GLEW_STATIC
#include <iostream>  
using namespace std;
#include<GL/glew.h>  
#include<GLFW/glfw3.h>
#include<GL/glut.h>

GLfloat transx, transy;
GLfloat scale;

int primw = 300;
int primh = 300;
GLfloat rotatex = 0, rotatey = 0;
GLint mousepx, mousepy;

void rend(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(8); // ���õ�Ĵ�С
    glLineWidth(2); // �����ߵĿ��

    glPushMatrix();
    glTranslatef(transx, transy, 0);
    glRotatef(rotatex, 1, 0, 0);
    glRotatef(rotatey, 0, 1, 0);
    glBegin(GL_LINES);
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 2, 0);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(2, 0, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 2);
    glEnd();
    glPopMatrix();
    //������ʱ�����еĵ�Χ�ɵ�ƽ��Ϊ����
    glFrontFace(GL_CCW);
    // ���ò����Ʊ��棬��ʡ����ͬʱ������ֱ��渲����������
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glPushMatrix();
    // ���������λ�ú��ӽ�
    /*gluLookAt(2, 2, 2, 0.0, 0.0, 0.0, -1, -1, 1);*/
    // �����Ƹ���������ת
    glRotatef(rotatex, 1, 0, 0);
    glRotatef(rotatey, 0, 1, 0);
    // ����������İ˸���������
    static const GLfloat vertex[][3] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f
    };
    // ���û���������ʱ�����˳��
    static const GLint index[][4] = {
        0, 2, 3, 1,
        0, 4, 6, 2,
        0, 1, 5, 4,
        4, 5, 7, 6,
        1, 3, 7, 5,
        2, 6, 7, 3
    };
    // ����������
    glBegin(GL_QUADS);
    for (unsigned int i = 0; i < 6; i++)
        for (unsigned int j = 0; j < 4; j++) {
            // ÿ�������RGB��ɫֵ���䶥��λ������һ��
            glColor3fv(vertex[index[i][j]]);
            glVertex3fv(vertex[index[i][j]]);
        }
    glEnd();
    glPopMatrix();
    glFlush(); // ˢ�¶���
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // �����޼���
    if (w <= h)
        gluOrtho2D(-10, 10, -10.0 / w * h, 10.0 / w * h);
    else
        gluOrtho2D(-10.0 / h * w, 10.0 / h * w, -10, 10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // ������ʼ�շ��ڴ��ڵ����½�
    if (w <= h)
    {   
        transx = (50 - w / 2.0) * 20.0 / w;
        transy = (50 - h / 2.0) * 20.0 / w;
    }
    else
    {
        transx = (50 - w / 2.0) * 20.0 / h;
        transy = (50 - h / 2.0) * 20.0 / h;
    }
}

void motion(int x, int y)//��갴���ƶ�
{
    int w, h;
    w = glutGet(GLUT_WINDOW_WIDTH); // ��ǰ���ڵĿ��
    h = glutGet(GLUT_WINDOW_HEIGHT); // ��ǰ���ڵĸ߶�
    if (0 <= x && x <= w && 0 <= y && y <= h)
    {
        rotatex = -(mousepy - y) / (GLfloat)h * 360;
        rotatey = -(mousepx - x) / (GLfloat)w * 360;
        glutPostRedisplay();
    }
}

void mousedown(int mouse, int state, int x, int y)
{
    if (state == GLUT_DOWN)// ��갴��
    {
        mousepx = x;
        mousepy = y;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(primw, primh);
    glutCreateWindow("coordination");

    glClearColor(1, 1, 1, 0);
    glutDisplayFunc(rend); // ��ʾ�ص����������ڻ��ƴ���
    glutMotionFunc(motion); // ��갴���¼�
    glutMouseFunc(mousedown); // ע�ᵱǰ���ڵ����ص�����
    glutReshapeFunc(reshape); // �����ͻص���������Ӧ���Ĵ��ڴ�С�¼�
    glutMainLoop(); // ��glut��ܿ�ʼ���У����лص�������ʼִ��ֱ���������

    return 0;

}