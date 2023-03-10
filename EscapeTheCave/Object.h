#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "Types.h"
#include "Game.h"
#include "Window.h"
#include "Geometry.h"

class Object {
private:
    float posX, posY, posZ;
    Geometry* bbox;

protected:
    static Window* & window;
    static Game* & game;
    static float & gameTime;

    const float & x = posX;
    const float & y = posY;
    const float & z = posZ;

    uint type;
public:
    Object();
    virtual ~Object();

    virtual float X() const;
    virtual float Y() const;
    virtual float Z() const;

    virtual uint Type() const;

    virtual void BBox(Geometry* bb);

    virtual Geometry* BBox() const;

    virtual void Translate(float dx, float dy, float dz = 0.0f);

    virtual void MoveTo(float px, float py, float pz);

    virtual void MoveTo(float px, float py);

    virtual void OnCollision(Object* obj);

    virtual void Update() = 0;
    virtual void Draw() = 0;
};

inline float Object::X() const
{ return posX; }

inline float Object::Y() const
{ return posY; }

inline float Object::Z() const
{ return posZ; }

inline uint Object::Type() const
{ return type; }

inline Geometry* Object::BBox() const
{ return bbox; }

#endif
