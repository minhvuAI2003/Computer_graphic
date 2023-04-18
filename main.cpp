#include "glut.h"
#include <gl\glu.h>
#include <gl\gl.h>
static GLfloat spin = 0.0; 
char k;    
float a;
void init(void) 
{
    glClearColor (0, 0, 0, 0);
    glShadeModel (GL_SMOOTH);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glPushMatrix();
    if(k=='l' ||k=='r')
        glRotatef(spin, 0, 1, 0);  // nếu nhấn phím r hoặc l thì xoay quanh trục Oy
    else if(k=='u' ||k=='d')
        glRotatef(spin, 1, 0, 0); // nếu nhấn phím u hoặc d thì xoay quanh trục Ox
    else
        glRotatef(spin, 1.0, 1.0, 1.0); // còn lại xoay 2 trục Ox và Oy
    gluLookAt (10, 10, 10, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0); // góc nhìn
    glTranslatef (2.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    /* Vẽ đa giác */
     /* Xóa window */   
    glClear(GL_COLOR_BUFFER_BIT);
    /* Vẽ đa giác */
    glBegin(GL_POLYGON); 
    glColor3f(1.9, 0.6, 0.6); // tô màu hình thang (màu hồng)
    glVertex2f(-40, -25); // tọa độ đỉnh
    glVertex2f(-25, 25); 
    glVertex2f(25, 25); 
    glVertex2f(40, -25); 
    glEnd();
    glFlush(); // vẽ các mặt cho hình lập phương 
    glPopMatrix();
    glutSwapBuffers();  // thực hiện việc hoán đổi 2 buffer 
}

void spinDisplay(void)
{
   spin = spin + 0.05;  // xoay thêm 0.05 độ cho mỗi lần lặp 
   if (spin > 360.0)
	spin = spin - 360.0;
    glutPostRedisplay();// thông báo cho chương trình cần phải thực hiện việc vẽ lại
}

void spinDisplay_P(void) // hàm xoay hình theo phím
{
    spin = spin + a;  // xoay thêm a độ cho mỗi lần lặp 
    if (spin > 360.0)
    spin = spin - 360.0;
    glutPostRedisplay(); 
}

/* Hàm dùng bàn phím */
void keyboard (unsigned char key, int x, int y) 
{ 
    switch (key) 
    { 
        case 'l': 
            glutIdleFunc(spinDisplay_P);
            a=-0.05; // nhấn phím l góc xoay giảm 0.05 độ 
            k='l'; // cho biến k = l để xoay theo trục Oy
            glutPostRedisplay(); 
        break; 
        case 'r':
            glutIdleFunc(spinDisplay_P);
            a=0.05; // nhấn phím l góc xoay tăng 0.05 độ
            k='r';
            glutPostRedisplay(); 
        break; 
        case 'u': 
            glutIdleFunc(spinDisplay_P);
            a=-0.05;
            k='u'; // cho biến k = u để xoay theo trục Ox
            glutPostRedisplay(); 
        break; 
        case 'd': 
            glutIdleFunc(spinDisplay_P);
            a=0.05;
            k='d';
            glutPostRedisplay(); 
            break; 
        default: 
        break; 
   } 
} 

void mouse(int button, int state, int x, int y) 
{
    switch (button) 
    {
        case GLUT_LEFT_BUTTON:  // khi nhấn chuột trái 
        if (state == GLUT_DOWN)
        glutIdleFunc(spinDisplay); // chương trình đang ngừng thì thực hiện hàm spinDisplay 
        break;
        case GLUT_MIDDLE_BUTTON:  // khi nhấn nút giữa 
        if (state == GLUT_DOWN)
        glutIdleFunc(0); // chương trình ngừng xoay 
        break;
        default:
        break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv); // gọi glutInit trước các lệnh khác
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500); // kích thước cửa sổ giao diện
    // vị trí hiện cửa sổ giao diện
    glutCreateWindow("Nhom 8"); // tên cửa sổ giao diện
    glutDisplayFunc(display); // gọi hàm display
    init(); // khởi tạo// giống 7 dòng đầu trong hàm main của mục A. Vẽ hình thang cân
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse); 
    glutMainLoop();
    return 0;
}
