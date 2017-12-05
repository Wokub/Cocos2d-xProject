#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

class MenuScene : public cocos2d::Scene {
public:
    static cocos2d::Scene *createScene();

    //funkcja inicjalizujaca bool
    virtual bool init();

    void SceneCallback(cocos2d::Ref *pSender);

    void multiplayer(Ref *pSender);
    void inform(Ref *pSender);

    //tworzenie glownej funkcji
    CREATE_FUNC(MenuScene);
};


#endif // __MENU_SCENE_H__
