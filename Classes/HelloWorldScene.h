#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene {
public:
    //tworzenie sceny
    static cocos2d::Scene *createScene();

    //funkcja inicjalizujaca bool
    virtual bool init();

    //tworzenie psychiki
    //cocos2d::PhysicsWorld *sceneWorld;


    //tworzenie funkcji
    void menuJumpCallback(cocos2d::Ref *pSender);
    //void SetPhysicsWorld(cocos2d::PhysicsWorld *world){sceneWorld = world;};
    void menuLeftCallback(cocos2d::Ref *pSender);
    void menuRightCallback(cocos2d::Ref *pSender);

    //tworzenie zmiennych
    cocos2d::Sprite *character;
    cocos2d::Sprite *bridge;
    cocos2d::Sprite *ground;
    cocos2d::Sprite *ball;
    cocos2d::Sprite *enemy;
    cocos2d::Sprite *goalone;
    cocos2d::Sprite *goaltwo;
    bool onContactBegin(cocos2d::PhysicsContact &contact);

    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

    //tworzenie glownej funkcji
    CREATE_FUNC(HelloWorld);
private:
    cocos2d::PhysicsWorld *sceneWorld;

    void SetPhysicsWorld (cocos2d::PhysicsWorld *world)
    {
        sceneWorld = world;
    }
};


#endif // __HELLOWORLD_SCENE_H__
