#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "GameCommon.h"

class GameScene;

enum GameObjectType
{
	eGameObjectType = 0,
	eGameSpriteType
};

class GameObject
{
public:
	GameObject(GameScene *scene, int type);
	virtual ~GameObject();
	void drawObject(GLView *view, const matrix4f &modelMatrix, unsigned int flags);
	//events
	virtual void onUpdate(float dt);
	virtual void onDraw(GLView *view, unsigned int flags);
    //setters
	inline void setPosition(const vector3f &pos) { mPosition = pos; }
	inline void setPosition(float x, float y, float z) { mPosition.set(x, y, z); }
	inline void setRotation(float rot) { mRotation.z = rot; }
	inline void setScale(float scale) { mScale.set(scale, scale, scale); }
	inline void setName(const char *name) { strcpy(mName, name); }
	//getters
    inline int getType() const { return mType; }
    inline const vector3f &getPosition() const { return mPosition; }
    inline const vector3f &getRotation() const { return mRotation; }
    inline const vector3f &getScale() const { return mScale; }
    inline const char *getName() const { return mName; }

private:
    GameScene *mScene;
    int mType;
    vector3f mPosition;
    vector3f mRotation;
    vector3f mScale;
    matrix4f mModelMatrix;
    char mName[250];
};

#endif // GAMEOBJECT_H
