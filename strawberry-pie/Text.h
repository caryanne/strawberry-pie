#ifndef TEXT_H
#define TEXT_H

void initText();
void releaseText();
void drawText(float x, float y, float size, bool c, float r, float g, float b, const char *text);

#endif