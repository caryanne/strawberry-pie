#include "GLFW\glfw3.h"
#include <math.h>

#define DEG_TO_RAD 3.141592654 / 180.0

void drawBox(float x, float y, float w, float h, float r, float g, float b, float a) {
	glColor4f(r, g, b, a);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glVertex2f(x, y + h);
	glVertex2f(x + w, y + h);
	glEnd();
}

void drawCircle(float x, float y, float radius, float r, float g, float b, float a) {
	glColor4f(r, g, b, a);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for(int i = 0; i <= 360; i += 18) {
		glVertex2f(x + radius * (float) cos(i * DEG_TO_RAD), y + radius * (float) sin(i * DEG_TO_RAD));
	}
	glEnd();
}