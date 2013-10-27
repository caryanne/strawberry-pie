#include "GLFW\glfw3.h"
extern "C" {
#include "fontstash.h"
}

struct sth_stash *stash;
int font;

void initText() {
	stash = sth_create(512, 512);
	font = sth_add_font(stash, "regular.ttf");
}
void releaseText() {
	sth_delete(stash);
}
void drawText(float x, float y, float size, bool c, float r, float g, float b, const char *text){
	

	sth_begin_draw(stash);
	glColor3f(r, g, b);
	if(c)
		sth_draw_text(stash, font, size, x - get_text_width(stash, font, size, text) / 2.f, y, text, &x);
	else
		sth_draw_text(stash, font, size, x, y, text, &x);
	
	sth_end_draw(stash);

}