#include "HelloWorldScene.h"
#include "HelpScene.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "AppDelegate.h"
#include "cocos2d.h"
#include "GameOverScene.h"

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

    //Tworzenie tla
    auto bg = Sprite::create("images/background/Pirates_BG.jpg");
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





