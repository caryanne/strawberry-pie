
#include <math.h>
#include <windows.h>
#include "GLFW/glfw3.h"
#include <gl/GLU.h>
#include <stdio.h>
#include <stdlib.h>
#include "Shapes.h"
#include "Shapes3d.h"
#include "Text.h"

#include "Frame.h"
#include "Button.h"

#define DEG_TO_RAD 3.141592654 / 180.0

Frame root;

Frame twrctrl;
Frame camctrl;

float bx;
float by;
float tangle;
float cangle;


void errorCallback(int error, const char* desc) {
	fputs(desc, stderr);
}

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void cright() {
	cangle += 0.05f;
}
void cleft() {
	cangle -=0.05f;
}

void right() {
	tangle -= 0.05f;
}
void left() {
	tangle += 0.05f;
}

void up() {
	bx += cos(tangle * DEG_TO_RAD) * 0.001f;
	by -= sin(tangle * DEG_TO_RAD) * 0.001f;
}
void down() {
	bx -= cos(tangle * DEG_TO_RAD) * 0.001f;
	by += sin(tangle * DEG_TO_RAD) * 0.001f;
}

void setup2D(double w, double h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.f, w, h, 0.f);
	glViewport(0, 0, w, h);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void setup3D(double x, double y, double w, double h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(45.f, w / h, 0.1f, 100.f);
	glViewport(x, y - h, w, h);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float pos[] = {0, 1, -1, 0};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glShadeModel(GL_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

int main() {
	GLFWwindow *window;
	
	bx = 0.f;
	by = 0.f;
	tangle = 0.f;

	glfwSetErrorCallback(errorCallback);
	if(!glfwInit())
		exit(EXIT_FAILURE);
	

	window = glfwCreateWindow(1360, 768, "strawberry pie", glfwGetPrimaryMonitor(), NULL);
	if(!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, keyCallback);	
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	
	initText();
	root = Frame(0,0,width,height,0,19,false,"strawberry pie");

	root.dontDrawChildren();

	twrctrl = Frame(0,0,282,141,1,19,true,"car control");
	camctrl = Frame(2000,0,162,141,1,19,true,"camera control");


	Button lb = Button(0,0,80,120,1,"left",NULL,left);
	Button rb = Button(200,0,80,120,1,"right",NULL,right);
	Button ub = Button(80,0,120,60,1,"fwd",NULL,up);
	Button db = Button(80,60,120,60,1,"back",NULL,down);

	Button clb = Button(0,0,80,120,1,"left",NULL,cleft);
	Button crb = Button(200,0,80,120,1,"right",NULL,cright);


	
	twrctrl.attach(&rb);
	twrctrl.attach(&lb);
	twrctrl.attach(&ub);
	twrctrl.attach(&db);
	camctrl.attach(&clb);
	camctrl.attach(&crb);
	root.attach(&twrctrl);
	root.attach(&camctrl);
	
	cangle = 0.f;
	bool click = false;
	double mouseX, mouseY;
	while(!glfwWindowShouldClose(window)) {
		
		glfwGetCursorPos(window, &mouseX, &mouseY);
		
		if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS && click == false) {
			click = true;
			root.mouseDown(mouseX, mouseY);
		}
		if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE && click == true) {
			click = false;
			root.mouseUp();
		}
		root.update(mouseX, mouseY);

		
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		
		setup2D(width, height);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		root.draw();
		
		
		root.setup3D(height, 0.f);
		
		gluLookAt(10 * sin(cangle * DEG_TO_RAD),5,10 * cos(cangle * DEG_TO_RAD),0,0,0,0,1,0);


		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0,-0.5f,0);
		drawBox(10,0.1f,10,0.5f,0.5f,0,1);
		glTranslatef(0,0.5f,0);
		glTranslatef(bx,0.f,by);
		glRotatef(tangle + 90,0,1,0);
		
		drawBox(2,1,3,0,0.5f,0,1);
		glTranslatef(0,0.75f,1);
		drawBox(1,0.5f,1,0.75f,0,0,1);

		setup2D(width, height);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		twrctrl.draw(root.getBorderThickness(), root.getBorderThickness() + root.getTitleHeight());
		camctrl.draw(root.getBorderThickness(), root.getBorderThickness() + root.getTitleHeight());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwDestroyWindow(window);
	glfwTerminate();
	releaseText();
	exit(EXIT_SUCCESS);

}