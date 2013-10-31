
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

#include "soil\SOIL.h"
#include "tiny_obj_loader.h"

#define DEG_TO_RAD 3.141592654 / 180.0

Frame root;

Frame camctrl;

float cangle;

unsigned tex1;
unsigned tex2;
unsigned tex3;

vector<tinyobj::shape_t> shapes;

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

void setup2D(double w, double h) {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.f, w, h, 0.f);
	glViewport(0, 0, w, h);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

/*void setup3D(double x, double y, double w, double h) {
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(45.f, w / h, 0.1f, 100.f);
	glViewport(x, y - h, w, h);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_FLAT);
	float pos[] = {0, 1, -1, 0};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_TEXTURE_2D);
	
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}*/

void loadMedia() {
	tinyobj::LoadObj(shapes,"pib2.obj");
	tex2 = SOIL_load_OGL_texture("p2.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y|SOIL_FLAG_NTSC_SAFE_RGB);
	tex1 = SOIL_load_OGL_texture("p1.jpg",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y|SOIL_FLAG_NTSC_SAFE_RGB);
	tex3 = SOIL_load_OGL_texture("1174.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y|SOIL_FLAG_NTSC_SAFE_RGB);
}


int main() {
	
	GLFWwindow *window;
	
	glfwSetErrorCallback(errorCallback);
	if(!glfwInit())
		exit(EXIT_FAILURE);
	

	window = glfwCreateWindow(1360,768, "strawberry pie", glfwGetPrimaryMonitor(), NULL);
	if(!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, keyCallback);	
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	
	initText();
	root = Frame(0,0,width,height,0,19,false,"chicago");

	root.dontDrawChildren();

	camctrl = Frame(100,300,162,50,1,0,true,"");

	Button clb = Button(0,0,80,50,1,"left",NULL,cleft);
	Button crb = Button(200,0,80,50,1,"right",NULL,cright);

	camctrl.attach(&clb);
	camctrl.attach(&crb);
	root.attach(&camctrl);
	
	cangle = 0.f;
	bool click = false;
	double mouseX, mouseY;
	loadMedia();
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

		gluLookAt(0,0.9f,2.5f,0,0.1f,0,0,1,0);
		
		glShadeModel(GL_SMOOTH);
		glDisable(GL_BLEND);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//glScalef(10.01f,10.01f,10.01f);
		glRotatef(cangle,0,1.f,0);
		//glRotatef(-90,1,0,0);
			
		
		for (size_t i = 0; i < shapes.size(); i++) {

			if(shapes[i].material.diffuse_texname == string("p1.jpg")){
				glBindTexture(GL_TEXTURE_2D,tex1);}
			if(shapes[i].material.diffuse_texname == string("p2.png")){
				glBindTexture(GL_TEXTURE_2D,tex2);}
			if(shapes[i].material.diffuse_texname == string("1174.png")){
				glBindTexture(GL_TEXTURE_2D,tex3);}

			glBegin(GL_TRIANGLES);
			for (size_t f = 0; f < shapes[i].mesh.indices.size(); f++) {
				glNormal3f(shapes[i].mesh.normals[3*shapes[i].mesh.indices[f]],
					shapes[i].mesh.normals[3*shapes[i].mesh.indices[f]+1],
					shapes[i].mesh.normals[3*shapes[i].mesh.indices[f]+2]);
				
				glTexCoord2f(shapes[i].mesh.texcoords[2*shapes[i].mesh.indices[f]],
					shapes[i].mesh.texcoords[2*shapes[i].mesh.indices[f]+1]);

				glVertex3f(shapes[i].mesh.positions[3*shapes[i].mesh.indices[f]],
					shapes[i].mesh.positions[3*shapes[i].mesh.indices[f]+1],
					shapes[i].mesh.positions[3*shapes[i].mesh.indices[f]+2]);
			}
			glEnd();
		}

		

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