#ifndef DIALOGBOX_H
#define DIALOGBOX_H

#include <string>
#include "Component.h"

using namespace std;

class DialogBox: public Component {


private:


	string mTitle;
	static const float mBorderThickness;
	static const float mTitleHeight;
	bool mDrag;
	float mDragX;
	float mDragY;

public:
	DialogBox();
	DialogBox(float x, float y, float width, float height, string title);

	virtual void update(float x, float y);
	virtual void draw();
	virtual void draw(float x, float y);
	
	virtual bool mouseDown(float x, float y);
	virtual void mouseUp();


	void setSize(float width, float height);
	void setTitle(string title);

};

#endif