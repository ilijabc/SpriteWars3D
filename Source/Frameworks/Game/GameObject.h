#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "GameCommon.h"

class GameScene;

class GameObject
{
public:
	GameObject(GameScene *scene, int type);
	virtual ~GameObject();
	//events
	virtual void onUpdate(float dt);
	virtual void onDraw(GLView *view, unsigned int flags);
    //setters
	inline void setPosition(const GLFloat3 &pos) { mPosition = pos; }
	inline void setPosition(float x, float y, float z) { mPosition.set(x, y, z); }
	inline void setRotation(float rot) { mRotation = rot; }
	inline void setName(const char *name) { strcpy(mName, name); }
	//getters
    inline int getType() const { return mType; }
    inline const GLFloat3 &getPosition() const { return mPosition; }
    inline float getRotation() const { return mRotation; }
    inline const char *getName() const { return mName; }

private:
    GameScene *mScene;
    int mType;
    GLFloat3 mPosition;
    float mRotation;
    char mName[250];
};

#endif // GAMEOBJECT_H
