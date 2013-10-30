#include "GLFW\glfw3.h"
#include <math.h>

void drawBox(float width, float height, float length, float r, float g, float b, float a) {
	//glDisable(GL_LIGHTING);
	glBegin(GL_QUADS);
	float topY = height / 2.f; float bottomY = height / -2.f;
	float rightX = width / 2.f;	float leftX = width / -2.f;
	float frontZ = length / 2.f; float backZ = length / -2.f;

	float bottomBackLeft[] = {leftX, bottomY, backZ};
	float bottomBackRight[] = {rightX, bottomY, backZ};
	float bottomFrontRight[] = {rightX, bottomY, frontZ};
	float bottomFrontLeft[] = {leftX, bottomY, frontZ};
	float topBackLeft[] = {leftX, topY, backZ};
	float topBackRight[] = {rightX, topY, backZ};
	float topFrontRight[] = {rightX, topY, frontZ};
	float topFrontLeft[] = {leftX, topY, frontZ};
	
	float color[] = {r, g, b, a};
	glMaterialfv(GL_FRONT,GL_DIFFUSE,color);


	glNormal3f(1.f,0.f,0.f);//left
	glTexCoord2f(0.f,0.f);
	glVertex3fv(bottomBackLeft);
	glTexCoord2f(1.f,0.f);
	glVertex3fv(bottomFrontLeft);
	glTexCoord2f(1.f,1.f);
	glVertex3fv(topFrontLeft);
	glTexCoord2f(0.f,1.f);
	glVertex3fv(topBackLeft);

	
	glNormal3f(-1.f,0.f,0.f);//right
	glTexCoord2f(0.f,0.f);
	glVertex3fv(bottomBackRight);
	glTexCoord2f(1.f,0.f);
	glVertex3fv(bottomFrontRight);
	glTexCoord2f(1.f,1.f);
	glVertex3fv(topFrontRight);
	glTexCoord2f(0.f,1.f);
	glVertex3fv(topBackRight);
	
	
	glNormal3f(0.f,0.f,1.f);//back
	glTexCoord2f(0.f,0.f);
	glVertex3fv(bottomBackRight);
	glTexCoord2f(1.f,0.f);
	glVertex3fv(bottomBackLeft);
	glTexCoord2f(1.f,1.f);
	glVertex3fv(topBackLeft);
	glTexCoord2f(0.f,1.f);
	glVertex3fv(topBackRight);


	glNormal3f(0.f,0.f,-1.f);//front
	glTexCoord2f(0.f,0.f);
	glVertex3fv(bottomFrontRight);
	glTexCoord2f(1.f,0.f);
	glVertex3fv(bottomFrontLeft);
	glTexCoord2f(1.f,1.f);
	glVertex3fv(topFrontLeft);
	glTexCoord2f(0.f,1.f);
	glVertex3fv(topFrontRight);


	glNormal3f(0.f,1.f,0.f);//top
	glTexCoord2f(0.f,0.f);
	glVertex3fv(topFrontRight);
	glTexCoord2f(1.f,0.f);
	glVertex3fv(topFrontLeft);
	glTexCoord2f(1.f,1.f);
	glVertex3fv(topBackLeft);
	glTexCoord2f(0.f,1.f);
	glVertex3fv(topBackRight);
	
	glNormal3f(0.f,-1.f,0.f);//bottom
	glTexCoord2f(0.f,0.f);
	glVertex3fv(bottomFrontRight);
	glTexCoord2f(1.f,0.f);
	glVertex3fv(bottomFrontLeft);
	glTexCoord2f(1.f,1.f);
	glVertex3fv(bottomBackLeft);
	glTexCoord2f(0.f,1.f);
	glVertex3fv(bottomBackRight);
	glEnd();
	//glEnable(GL_LIGHTING);
}