#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>

class Component {

private:
public:

	std::vector<Component*> mChildren;
	void attach(Component *component);
	float mX;
	float mY;
	float mWidth;
	float mHeight;
	float mR;
	float mG;
	float mB;
	
	Component() { mX = 0.f; mY = 0.f; }
	virtual void update(float x, float y) = 0;
	virtual void draw() = 0;
	virtual void draw(float xOffset, float yOffset) = 0;

	virtual bool mouseDown(float x, float y) = 0;
	virtual void mouseUp() = 0;

	float getX() { return mX; }
	float getY() { return mY; }
	float getWidth() { return mWidth; }
	float getHeight() { return mHeight; }
	void setSize(float width, float height) { mWidth = width; mHeight = height; }
	void setPosition(float x, float y) { mX = x; mY = y; }
	void setColor(float r, float g, float b) { mR = r; mG = g; mB = b; }

};

#endif