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
    glPointSize(8); // 设置点的大小
    glLineWidth(2); // 设置线的宽度

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
    //设置逆时针排列的点围成的平面为正面
    glFrontFace(GL_CCW);
    // 设置不绘制背面，节省算力同时不会出现背面覆盖正面的情况
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glPushMatrix();
    // 设置相机的位置和视角
    /*gluLookAt(2, 2, 2, 0.0, 0.0, 0.0, -1, -1, 1);*/
    // 设置绕给定的轴旋转
    glRotatef(rotatex, 1, 0, 0);
    glRotatef(rotatey, 0, 1, 0);
    // 设置立方体的八个顶点坐标
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
    // 设置绘制六个面时顶点的顺序
    static const GLint index[][4] = {
        0, 2, 3, 1,
        0, 4, 6, 2,
        0, 1, 5, 4,
        4, 5, 7, 6,
        1, 3, 7, 5,
        2, 6, 7, 3
    };
    // 绘制六个面
    glBegin(GL_QUADS);
    for (unsigned int i = 0; i < 6; i++)
        for (unsigned int j = 0; j < 4; j++) {
            // 每个顶点的RGB颜色值和其顶点位置坐标一致
            glColor3fv(vertex[index[i][j]]);
            glVertex3fv(vertex[index[i][j]]);
        }
    glEnd();
    glPopMatrix();
    glFlush(); // 刷新队列
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // 定义修剪区
    if (w <= h)
        gluOrtho2D(-10, 10, -10.0 / w * h, 10.0 / w * h);
    else
        gluOrtho2D(-10.0 / h * w, 10.0 / h * w, -10, 10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // 将坐标始终放在窗口的左下角
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

void motion(int x, int y)//鼠标按下移动
{
    int w, h;
    w = glutGet(GLUT_WINDOW_WIDTH); // 当前窗口的宽度
    h = glutGet(GLUT_WINDOW_HEIGHT); // 当前窗口的高度
    if (0 <= x && x <= w && 0 <= y && y <= h)
    {
        rotatex = -(mousepy - y) / (GLfloat)h * 360;
        rotatey = -(mousepx - x) / (GLfloat)w * 360;
        glutPostRedisplay();
    }
}

void mousedown(int mouse, int state, int x, int y)
{
    if (state == GLUT_DOWN)// 鼠标按下
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
    glutDisplayFunc(rend); // 显示回调函数，用于绘制窗口
    glutMotionFunc(motion); // 鼠标按下事件
    glutMouseFunc(mousedown); // 注册当前窗口的鼠标回调函数
    glutReshapeFunc(reshape); // 再整型回调函数，响应更改窗口大小事件
    glutMainLoop(); // 让glut框架开始运行，所有回调函数开始执行直到程序结束

    return 0;

}