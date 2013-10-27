#include "GLFW\glfw3.h"
#include "DialogBox.h"
#include "Shapes.h"
#include "Text.h"



bool DialogBox::mouseDown(float x, float y) {
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

void DialogBox::mouseUp() {
	mDrag = false;
	for( vector<Component*>::iterator it = mChildren.begin(); it != mChildren.end(); ++it )
		(*it)->mouseUp();
}

DialogBox::DialogBox() {
	mX = 100.f;
	mY = 100.f;
	mR = 1.f; mG = 1.f;	mB = 1.f;
	mDrag = false;
	mWidth = 400.f;
	mHeight = 300.f;
	mTitle = "new dialog box";
	mBorderThickness = 1.0f;
	mTitleHeight = 19.0f;
	mMoveable = true;

}
DialogBox::DialogBox(float x, float y, float width, float height, float borderThickness, float titleHeight, bool moveable, string title) {
	mX = x;	mY = y; mR = 1.f; mG = 1.f;	mB = 1.f;
	mDrag = false;
	mWidth = width;
	mHeight = height;
	mTitle = title;
	mMoveable = moveable;
	mBorderThickness = borderThickness;
	mTitleHeight = titleHeight;

}

void DialogBox::update(float x, float y) {
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

void DialogBox::draw() {
	draw(0.f, 0.f);
}

void DialogBox::draw(float xOffset, float yOffset) {
	if(mDrag)
		drawBox(mX + xOffset, mY + yOffset, mWidth, mHeight, mR * 0.7f, mG * 0.7f, mB * 0.7f, 1); //border & title bar
	else
		drawBox(mX + xOffset, mY + yOffset, mWidth, mHeight, mR * 0.9f, mG * 0.9f, mB * 0.9f, 1); //border & title bar
	drawBox(mX + xOffset + mBorderThickness, mY + yOffset + mBorderThickness + mTitleHeight,
		mWidth - 2 * mBorderThickness, mHeight - 2 * mBorderThickness - mTitleHeight, mR * 0.5f, mG * 0.5f, mB * 0.5f, 1); //inner section

	drawText(mX + xOffset + mWidth / 2.f, mY + yOffset + mTitleHeight * 0.8f, mTitleHeight + 1.f, true, 0.9f, 0.9f, 0.9f, mTitle.c_str()); //title
	for( vector<Component*>::iterator it = mChildren.begin(); it != mChildren.end(); ++it ) {
		(*it)->draw(mX + mBorderThickness + xOffset, mY + mBorderThickness + mTitleHeight + yOffset);
	}
}

void DialogBox::setTitle(string title) {
	mTitle = title;
}