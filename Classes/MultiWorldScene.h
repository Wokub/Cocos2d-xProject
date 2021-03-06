#ifndef __MULTIWORLD_SCENE_H__
#define __MULTIWORLD_SCENE_H__

#include "cocos2d.h"

class MultiWorld : public cocos2d::Scene {
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
    unsigned int firstscore;
    unsigned int secondscore;

    cocos2d::Label *scoreLabel;
    cocos2d::Label *secondscoreLabel;

    //tworzenie glownej funkcji
    CREATE_FUNC(MultiWorld);
private:
    cocos2d::PhysicsWorld *sceneWorld;

    void SetPhysicsWorld (cocos2d::PhysicsWorld *world)
    {
        sceneWorld = world;
    }
};


#endif // __MULTIWORLD_SCENE_H__
