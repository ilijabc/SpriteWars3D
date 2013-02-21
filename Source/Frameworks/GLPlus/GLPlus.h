/*
 * GLPlus.h
 *
 *  Created on: Jun 22, 2012
 *      Author: Ilija
 */

#ifndef GLPLUS_H_
#define GLPLUS_H_

#include <GL/gl.h>
#include <GL/glu.h>

#include "GLCamera.h"
#include "GLFont.h"
#include "GLMaterial.h"
#include "GLMath.h"
#include "GLModel.h"
#include "GLNode.h"
#include "GLParticleSystem.h"
#include "GLTexture.h"
#include "GLView.h"

#include "GLTerrain.h"
#include "GLSprite.h"

void glRenderCube(float x, float y, float z);
void glPushTexture(GLTexture *tex);
void glPopTexture();
void glMultMatrix(const matrix4f& mat);
void glColor(Color c);
void glBeginPicking(int x, int y, float sense);
int glEndPicking();
vector3f glGetPoint3D(int x, int y);

#endif /* GLPLUS_H_ */
