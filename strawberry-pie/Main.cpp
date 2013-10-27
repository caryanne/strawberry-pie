
#include <math.h>
#include "GLFW/glfw3.h"
#include <stdio.h>
#include <stdlib.h>
#include "Shapes.h"
#include "Text.h"

#include "DialogBox.h"

DialogBox root;


void errorCallback(int error, const char* desc) {
	fputs(desc, stderr);
}

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}



int main() {
	GLFWwindow *window;
	

	glfwSetErrorCallback(errorCallback);
	if(!glfwInit())
		exit(EXIT_FAILURE);
	

	window = glfwCreateWindow(1360, 768, "spreadem", glfwGetPrimaryMonitor(), NULL);
	if(!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, keyCallback);	
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.f, width, height, 0.f, 0.f, 1.f);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	initText();
	root = DialogBox(0,0,width,height,"spread'em 2014");
	DialogBox helloworld = DialogBox(200,100,500,300,"fuck fuck fuck");
	DialogBox kid = DialogBox(10,10,150,50,"kid");
	root.attach(&helloworld);
	helloworld.attach( &kid);
	
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
		//helloworld.setPosition(400 + 200 * sin(glfwGetTime()), 200 + 100 * sin(glfwGetTime() * 3.0));
		//kid.setPosition(200 + 100 * sin(glfwGetTime() * 1.5), 50 + 25 * sin(glfwGetTime() * 5.0));

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//dialog box
		root.draw();
		
		//input/output
		drawCircle(400,300,3,0.9f,0.9f,0.9f,1);
		drawCircle(400,300,2,0.1f,0.1f,0.1f,1);

		//button
		drawBox(100,400,180,25,0.9f,0.9f,0.9f,1);
		drawBox(101,401,178,23,0.5f,0.5f,0.5f,1);
		drawText( 190,420,20,true,1,1,1,"fuck");

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwDestroyWindow(window);
	glfwTerminate();
	releaseText();
	exit(EXIT_SUCCESS);

}