#include "HelloWorldScene.h"
#include "HelpScene.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "AppDelegate.h"
#include "cocos2d.h"
#include "GameOverScene.h"
#include "Definitions.h"

#include <iostream>

USING_NS_CC;

//Tworzenie sceny
Scene* HelpScene::createScene()
{
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = HelpScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

bool HelpScene::init()
{
    //Inicjalizacja
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create("images/background/End_BG.jpg");
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    backgroundSprite->setScale(0.7, 0.7);
    this->addChild( backgroundSprite );


    //Tworzenie prawego przycisku
    auto back = MenuItemImage::create(
            "images/buttons/menu.png",
            "images/buttons/menuclicked.png",
            CC_CALLBACK_1(HelpScene::GoToMainMenuScene, this));

    back->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 3.5 ) );
    //Tworzenie "menu", tj. miejsca pod przycisk
    auto menu_2 = Menu::create(back, NULL);
    menu_2->setPosition(Vec2::ZERO);
    this->addChild(menu_2, 1);

    //Audio
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/MenuTheme.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/MenuTheme.mp3", true);


    return true;
}

void HelpScene::GoToMainMenuScene( cocos2d::Ref *sender )
{
    auto scene = MenuScene::createScene( );

    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}