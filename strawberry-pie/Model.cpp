#include "GLFW\glfw3.h"
#include "Model.h"
#include "soil\SOIL.h"

Model::Model(string filename) {
	load(filename);
}

void Model::load(string filename) { //add error handling to this bullshit
	tinyobj::LoadObj(mModel, filename.c_str());
	for(unsigned i = 0; i < mModel.size(); i++) {
		if(mTextures.find(mModel[i].material.diffuse_texname) == mTextures.end()) {
			mTextures[mModel[i].material.diffuse_texname] =
				SOIL_load_OGL_texture(mModel[i].material.diffuse_texname.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y|SOIL_FLAG_NTSC_SAFE_RGB);
			printf("loading texture %s..\n", mModel[i].material.diffuse_texname.c_str());
		}
	}
}

void Model::render() {
	for(unsigned i = 0; i < mModel.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, mTextures[mModel[i].material.diffuse_texname]);
		glBegin(GL_TRIANGLES);
		for(unsigned f = 0; f < mModel[i].mesh.indices.size(); f++) {
			glNormal3f(mModel[i].mesh.normals[3*mModel[i].mesh.indices[f]],
				mModel[i].mesh.normals[3*mModel[i].mesh.indices[f]+1],
				mModel[i].mesh.normals[3*mModel[i].mesh.indices[f]+2]);
			glTexCoord2f(mModel[i].mesh.texcoords[2*mModel[i].mesh.indices[f]],
				mModel[i].mesh.texcoords[2*mModel[i].mesh.indices[f]+1]);
			glVertex3f(mModel[i].mesh.positions[3*mModel[i].mesh.indices[f]],
				mModel[i].mesh.positions[3*mModel[i].mesh.indices[f]+1],
				mModel[i].mesh.positions[3*mModel[i].mesh.indices[f]+2]);
		}
		glEnd();
	}
}