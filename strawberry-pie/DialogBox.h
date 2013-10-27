#ifndef DIALOGBOX_H
#define DIALOGBOX_H

#include <string>
#include "Component.h"

using namespace std;

class DialogBox: public Component {

private:
	string mTitle;
	float mBorderThickness;
	float mTitleHeight;
	bool mDrag;
	float mDragX;
	float mDragY;
	bool mMoveable;

public:
	DialogBox();
	DialogBox(float x, float y, float width, float height, float borderThickness, float titleHeight, bool moveable, string title);

	virtual void update(float x, float y);
	virtual void draw();
	virtual void draw(float x, float y);
	
	virtual bool mouseDown(float x, float y);
	virtual void mouseUp();

	void setTitle(string title);

};

#endif