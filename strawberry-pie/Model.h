#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <map>
#include "tiny_obj_loader.h"

using namespace std;

class Model {

private:
	map<string,unsigned> mTextures;
	vector<tinyobj::shape_t> mModel;

public:
	Model(string filename);
	void load(string filename);
	void render();

};

#endif