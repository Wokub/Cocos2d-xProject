#include "GameOverScene.h"
#include "HelloWorldScene.h"
#include "MenuScene.h"
#include "Definitions.h"
#include "MultiWorldScene.h"

USING_NS_CC;


Scene* GameOverScene::createScene()
{

    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create("images/background/End_BG.jpg");
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    backgroundSprite->setScale(0.7, 0.7);
    this->addChild( backgroundSprite );

    //auto retryItem = MenuItemImage::create( "Retry Button.png", "Retry Button Clicked.png", CC_CALLBACK_1( GameOverScene::GoToGameScene, this ) );
    //retryItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 3 ) );

    //auto mainMenuItem = MenuItemImage::create( "Menu Button.png", "Menu Button Clicked.png", CC_CALLBACK_1( GameOverScene::GoToMainMenuScene, this ) );
    //mainMenuItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 4 ) );

    //auto menu = Menu::create( retryItem, mainMenuItem, NULL );
    //menu->setPosition( Point::ZERO );

    //this->addChild( menu );

    auto retry = MenuItemImage::create(
            "images/buttons/retry.png",
            "images/buttons/retryclicked.png",
            CC_CALLBACK_1(GameOverScene::GoToGameScene, this)
            // , CC_CALLBACK_0(HelloWorld::JumpSoundEffect, this)
    );

    retry->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 2 ) );
    //Tworzenie "menu", tj. miejsca pod przycisk
    auto menu = Menu::create(retry, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    //Tworzenie prawego przycisku
    auto back = MenuItemImage::create(
            "images/buttons/menu.png",
            "images/buttons/menuclicked.png",
            CC_CALLBACK_1(GameOverScene::GoToMainMenuScene, this));

    back->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 3.5 ) );
    //Tworzenie "menu", tj. miejsca pod przycisk
    auto menu_2 = Menu::create(back, NULL);
    menu_2->setPosition(Vec2::ZERO);
    this->addChild(menu_2, 1);

    return true;
}

void GameOverScene::GoToMainMenuScene( cocos2d::Ref *sender )
{
    auto scene = MenuScene::createScene( );

    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

void GameOverScene::GoToGameScene( cocos2d::Ref *sender )
{
    auto scene = HelloWorld::createScene( );

    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}
