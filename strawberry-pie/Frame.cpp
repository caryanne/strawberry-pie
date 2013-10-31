#include <windows.h>
#include "GLFW/glfw3.h"
#include <gl/GLU.h>
#include "Frame.h"
#include "Shapes.h"
#include "Text.h"



bool Frame::mouseDown(float x, float y) {
	if(mMoveable && x >= mX && x <= mX + mWidth + mBorderThickness * 2.f && y >= mY && y <= mY + mTitleHeight + mBorderThickness) {
		mDrag = true;
		mDragX = x - mX;
		mDragY = y - mY;
		return true;
	}
	//else if(x >= mX && x <= mX + mWidth + mBorderThickness * 2.f && y >= mY && y <= mY + mHeight + mBorderThickness * 2.f) {
		for( vector<Component*>::iterator it = mChildren.begin(); it != mChildren.end(); ++it )
			(*it)->mouseDown(x - mX - mBorderThickness, y - mY - mBorderThickness - mTitleHeight);
	//}
	return false;
}

void Frame::mouseUp() {
	mDrag = false;
	for( vector<Component*>::iterator it = mChildren.begin(); it != mChildren.end(); ++it )
		(*it)->mouseUp();
}

Frame::Frame() {
	mDrawChildren = true;
	mX = 100.f;
	mY = 100.f;
	mR = 0.25f; mG = 0.25f;	mB = 0.25f;
	mDrag = false;
	mWidth = 400.f;
	mHeight = 300.f;
	mTitle = "new dialog Rect";
	mBorderThickness = 1.0f;
	mTitleHeight = 19.0f;
	mMoveable = true;

}
Frame::Frame(float x, float y, float width, float height, float borderThickness, float titleHeight, bool moveable, string title) {
	mDrawChildren = true;
	mX = x;	mY = y; mR = 0.25f; mG = 0.25f;	mB = 0.25f;
	mDrag = false;
	mWidth = width;
	mHeight = height;
	mTitle = title;
	mMoveable = moveable;
	mBorderThickness = borderThickness;
	mTitleHeight = titleHeight;

}

void Frame::update(float x, float y) {
	if(mDrag)
		setPosition(x - mDragX, y - mDragY);
	for( vector<Component*>::iterator it = mChildren.begin(); it != mChildren.end(); ++it ) {
		(*it)->update(x - mX - mBorderThickness, y - mY - mBorderThickness - mTitleHeight);
		if((*it)->getX() < 0.f)
			(*it)->setPosition(0.f, (*it)->getY());
		if((*it)->getY() < 0.f)
			(*it)->setPosition((*it)->getX(), 0.f);
		if((*it)->getX() + (*it)->getWidth() > mWidth - mBorderThickness * 2.f)
			(*it)->setPosition(mWidth - (*it)->getWidth() - mBorderThickness * 2.f, (*it)->getY());
		if((*it)->getY() + (*it)->getHeight() > mHeight - mBorderThickness * 2.f - mTitleHeight)
			(*it)->setPosition((*it)->getX(), mHeight - (*it)->getHeight() - mBorderThickness * 2.f - mTitleHeight);
	}

		
}

void Frame::draw() {
	draw(0.f, 0.f);
}

void Frame::draw(float xOffset, float yOffset) {
	if(mDrag)
		drawRect(mX + xOffset, mY + yOffset, mWidth, mHeight, mR * 0.7f, mG * 0.7f, mB * 0.7f, 1); //border & title bar
	else
		drawRect(mX + xOffset, mY + yOffset, mWidth, mHeight, mR * 0.9f, mG * 0.9f, mB * 0.9f, 1); //border & title bar
	drawRect(mX + xOffset + mBorderThickness, mY + yOffset + mBorderThickness + mTitleHeight,
		mWidth - 2 * mBorderThickness, mHeight - 2 * mBorderThickness - mTitleHeight, mR * 0.5f, mG * 0.5f, mB * 0.5f, 1); //inner section

	drawText(mX + xOffset + mWidth / 2.f, mY + yOffset + mTitleHeight * 0.8f, mTitleHeight + 1.f, true, 0.9f, 0.9f, 0.9f, mTitle.c_str()); //title
	if(!mDrawChildren)
		return;
	for(vector<Component*>::iterator it = mChildren.begin(); it != mChildren.end(); ++it) {
		(*it)->draw(mX + mBorderThickness + xOffset, mY + mBorderThickness + mTitleHeight + yOffset);
	}
}
void Frame::setup3D(float height, float yOffset) {
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	float w = mWidth - mBorderThickness * 2.f;
	float h = mHeight - mTitleHeight - mBorderThickness * 2.f;
	float x = mX + mBorderThickness;
	float y = height - (mY + mBorderThickness + mTitleHeight + yOffset);

	gluPerspective(45.f, w / h, 0.1f, 100.f);
	glViewport(x, y - h, w, h);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_FLAT);
	float pos[] = {20,3,20,0};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


}

void Frame::setTitle(string title) {
	mTitle = title;
}