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
#include "Model.h"
#include "soil\SOIL.h"
#include "tiny_obj_loader.h"

#include "bullet\btBulletDynamicsCommon.h"


#define DEG_TO_RAD 3.141592654 / 180.0

GLFWwindow *window;
Frame root;
Frame camctrl;

float cangle = 0.f;

void errorCallback(int error, const char* desc) {
	fputs(desc, stderr);
}

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void cright() {	cangle += 0.05f; }
void cleft() { cangle -=0.05f; }

void setup2D(double w, double h) {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.f, w, h, 0.f);
	glViewport(0, 0, (int)w, (int)h);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int main() {

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

	root = Frame(0, 0, width, height, 0, 19, false, "chicago");
	root.dontDrawChildren();

	camctrl = Frame(100, 300, 162, 50, 1, 0, true, "");

	Button clb = Button(0, 0, 80, 50, 1, "left", NULL, cleft);
	Button crb = Button(200, 0, 80, 50, 1, "right", NULL, cright);
	camctrl.attach(&clb);
	camctrl.attach(&crb);
	root.attach(&camctrl);

	bool click = false;
	double mouseX, mouseY;

	initText();
	Model puss = Model("pib2.obj");

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

		gluLookAt(0.f, 0.9f, 2.5f,
					0.f, 0.1f, 0.f,
					0.f, 1.f, 0.f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef(cangle, 0.f, 1.f, 0.f);			
		puss.render();

		setup2D(width, height);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		camctrl.draw(root.getBorderThickness(), root.getBorderThickness() + root.getTitleHeight());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwDestroyWindow(window);
	glfwTerminate();
	releaseText();
	exit(EXIT_SUCCESS);

}