#ifndef FRAME_H
#define FRAME_H

#include <string>
#include "Component.h"

using namespace std;

class Frame: public Component {

private:

	string mTitle;
	float mBorderThickness;
	float mTitleHeight;
	bool mDrag;
	float mDragX;
	float mDragY;
	bool mMoveable;
	bool mDrawChildren;

public:
	Frame();
	Frame(float x, float y, float width, float height, float borderThickness, float titleHeight, bool moveable, string title);

	virtual void update(float x, float y);
	virtual void draw();
	virtual void draw(float x, float y);
	
	virtual bool mouseDown(float x, float y);
	virtual void mouseUp();
	
	void setup3D(float height, float yOffset);

	void setTitle(string title);

	float getTitleHeight() { return mTitleHeight; }
	float getBorderThickness() { return mBorderThickness; }
	void drawChildren() { mDrawChildren = true; }
	void dontDrawChildren() { mDrawChildren = false; }


};

#endif