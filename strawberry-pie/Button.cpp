#include "GLFW\glfw3.h"
#include "Button.h"
#include "Shapes.h"
#include "Text.h"

void Button::setLabel(string label) {
	mLabel = label;
}

Button::Button() {
	mR = 0.25f; mG = 0.25f;	mB = 0.25f;
	mX = 100.f;
	mY = 100.f;
	mClick = false;
	mOver = false;
	mWidth = 100.f;
	mHeight = 50.f;
	mLabel = "new button";
	mBorderThickness = 1.f;
	mClickCallback = NULL;
	mHoldCallback = NULL;
}
Button::Button(float x, float y, float width, float height, float borderThickness, string label, void (*clickCallback)(), void (*holdCallback)()) {
	mX = x;	mY = y; mR = 0.25f; mG = 0.25f;	mB = 0.25f;
	mClick = false;
	mOver = false;
	mWidth = width;
	mBorderThickness = borderThickness;
	mHeight = height;
	mLabel = label;
	mClickCallback = clickCallback;
	mHoldCallback = holdCallback;

}

void Button::draw() {
	draw(0.f, 0.f);
}

void Button::draw(float xOffset, float yOffset) {
	float color;
	if(mOver && mClick)
		color = 0.75f;
	else if(mOver)
		color = 0.8f;
	else
		color = 1.f;
	drawBox(mX + xOffset, mY + yOffset, mWidth, mHeight, mR * 0.9f, mG * 0.9f, mB * 0.9f, 1);
	drawBox(mX + xOffset + mBorderThickness, mY + yOffset + mBorderThickness,
		mWidth - 2 * mBorderThickness, mHeight - 2 * mBorderThickness, mR * color, mG * color, mB * color, 1);

	drawText(mX + xOffset + mWidth / 2.f, mY + yOffset + mHeight / 2.f + 7.f, 20.f, true, 0.9f, 0.9f, 0.9f, mLabel.c_str());

	for( vector<Component*>::iterator it = mChildren.begin(); it != mChildren.end(); ++it ) {
		(*it)->draw(mX + mBorderThickness + xOffset, mY + mBorderThickness + yOffset);
	}
}

bool Button::mouseDown(float x, float y) {
	if(x >= mX && x <= mX + mWidth + mBorderThickness * 2.f && y >= mY && y <= mY + mHeight) {
		mClick = true;
		return true;
	}
	for( vector<Component*>::iterator it = mChildren.begin(); it != mChildren.end(); ++it )
			(*it)->mouseDown(x - mX - mBorderThickness, y - mY - mBorderThickness);
	return false;
}

void Button::mouseUp() {
	
	if(mOver && mClick) {
		if(mClickCallback != NULL)
			mClickCallback();
	}
	mClick = false;
	for( vector<Component*>::iterator it = mChildren.begin(); it != mChildren.end(); ++it )
		(*it)->mouseUp();
}

void Button::update(float x, float y) {
	mOver = (x >= mX && x <= mX + mWidth + mBorderThickness * 2.f && y >= mY && y <= mY + mHeight);	
	if(mOver && mClick && mHoldCallback != NULL)
		mHoldCallback();
}