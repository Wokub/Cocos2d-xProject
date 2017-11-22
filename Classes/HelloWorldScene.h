#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene {
public:
    static cocos2d::Scene *createScene();

    virtual bool init();

    // a selector callback
    cocos2d::PhysicsWorld *sceneWorld;
    CREATE_FUNC(HelloWorld);

    void menuCloseCallback(cocos2d::Ref *pSender);
    void SetPhysicsWorld(cocos2d::PhysicsWorld *world){sceneWorld = world;};
    /////////////////////
    // creating own variables

    cocos2d::Sprite *character;
    cocos2d::Sprite *bridge;
    cocos2d::Sprite *ground;


    // Character *character;
    bool onContactBegin(cocos2d::PhysicsContact &contact);
    /////////////////////
    // touch

    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

    // implement the "static create()" method manually

};


#endif // __HELLOWORLD_SCENE_H__
