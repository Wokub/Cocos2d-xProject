#include "HelloWorldScene.h"
#include "HelpScene.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "AppDelegate.h"
#include "cocos2d.h"

#include <iostream>

USING_NS_CC;

//Tworzenie sceny
Scene* HelloWorld::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vect(0,0));

    auto layer = HelloWorld::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);

    return scene;
}

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);


//Error, gdy cos sie nie zgodzi
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool HelpScene::init()
{
    //Inicjalizacja
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //Tworzenie przycisku skoku
    auto closeItem = MenuItemImage::create(
                    "images/buttons/Exit_Button.png",
                    "images/buttons/Button_Jump2.png",
                    CC_CALLBACK_1(HelpScene::BackCallback, this)
           // , CC_CALLBACK_0(HelloWorld::JumpSoundEffect, this)
    );

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'Button_Jump.png' and 'Button_Jump2.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width/1.2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    //Tworzenie "menu", tj. miejsca pod przycisk
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


    //Tworzenie tla
    auto bg = Sprite::create("images/background/background.jpg");
    bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    bg->setScale(0.55, 0.55);
    this->addChild(bg);

    //Audio
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/MainTheme.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/MainTheme.mp3", true);


    return true;
}


void HelpScene::BackCallback(Ref* pSender) {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("WKProject", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("WKProject");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height,
                                    ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height) {
        director->setContentScaleFactor(
                MIN(largeResolutionSize.height / designResolutionSize.height,
                    largeResolutionSize.width / designResolutionSize.width));
    }
        // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height) {
        director->setContentScaleFactor(
                MIN(mediumResolutionSize.height / designResolutionSize.height,
                    mediumResolutionSize.width / designResolutionSize.width));
    }
        // if the frame's height is smaller than the height of medium size.
    else {
        director->setContentScaleFactor(
                MIN(smallResolutionSize.height / designResolutionSize.height,
                    smallResolutionSize.width / designResolutionSize.width));
    }

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = MenuScene::createScene();//TUTAJ ZMIEN JAKBYS CHCIAL DOJEBCZYC HELLOWORLDSCENE

    // run
    director->runWithScene(scene);
}





