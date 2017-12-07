#ifndef __HELP_SCENE_H__
#define __HELP_SCENE_H__

#include "cocos2d.h"

class HelpScene : public cocos2d::Scene {
public:
    //tworzenie sceny
    static cocos2d::Scene *createScene();

    //funkcja inicjalizujaca bool
    virtual bool init();
    void BackCallback(cocos2d::Ref *pSender);
    //tworzenie psychiki
    cocos2d::PhysicsWorld *sceneWorld;

    //tworzenie glownej funkcji
    CREATE_FUNC(HelpScene);
};


#endif // __HELP_SCENE_H__
