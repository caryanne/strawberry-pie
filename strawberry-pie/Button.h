#ifndef BUTTON_H
#define BUTTON_H

#include <string>

#include "Component.h"

using namespace std;

class Button : public Component {
private:
	string mLabel;
	bool mClick;
	bool mOver;
	float mBorderThickness;
	void (*mCallback)();

public:
	Button();
	Button(float x, float y, float width, float height, float borderThickness, string label, void (*callback)());

	virtual void update(float x, float y);
	virtual void draw();
	virtual void draw(float x, float y);
	
	virtual bool mouseDown(float x, float y);
	virtual void mouseUp();


	void setLabel(string label);
};

#endif