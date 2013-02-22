#include "GLPlus.h"

void glRenderCube(float x, float y, float z) { }
void glPushTexture(GLTexture *tex) { }
void glPopTexture() { }
void glMultMatrix(const matrix4f& mat) { }
void glColor(Color c) { }
void glBeginPicking(int x, int y, float sense) { }
int glEndPicking() { return 0; }


vector3f glGetPoint3D(int x, int y)
{
    double modelview[16], projection[16];
    int viewport[4];
    float z;
	double vx, vy, vz;

    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetIntegerv( GL_VIEWPORT, viewport );

    glReadPixels( x, viewport[3]-y, 1, 1,
		 GL_DEPTH_COMPONENT, GL_FLOAT, &z );

    gluUnProject( x, viewport[3]-y, z, modelview,
		projection, viewport, &vx, &vy, &vz );

	return vector3f(vx, vy, vz);
}


vector2f glGetPoint2D(vector3f pos)
{
    double modelview[16], projection[16];
    int viewport[4];
	double vx, vy, vz;

    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetIntegerv( GL_VIEWPORT, viewport );

    gluProject(pos.x, pos.y, pos.z, modelview, projection, viewport, &vx, &vy, &vz);

    return vector2f(vx, viewport[3] - vy);
}
