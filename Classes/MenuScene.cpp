#include "MenuScene.h"
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "MultiWorldScene.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "HelpScene.h"
#include "Definitions.h"


USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

static int register_all_packages()
{
    return 0; //flag for packages manager
}

Scene* MenuScene::createScene()
{
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto bg = Sprite::create("images/background/Menu_BG.jpg");
    bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(bg);


    logo = Sprite::create("images/background/Logo.png");
    logo->setPosition(Point(visibleSize.width*1.5, (visibleSize.height/4)*3.5));
    this->addChild(logo);

    auto action = MoveTo::create(1,Point(visibleSize.width/2, (visibleSize.height/4)*3.5));
    logo->runAction(EaseElasticIn::create(action));

    auto menu_item_single = MenuItemFont::create("Singleplayer", CC_CALLBACK_1(MenuScene::SceneCallback, this));
    menu_item_single->setPosition(Point(visibleSize.width/4, (visibleSize.height/4)*3));
    menu_item_single->setScale(0.8,0.8);
    auto menu_item_second = MenuItemFont::create("Multiplayer", CC_CALLBACK_1(MenuScene::SceneCallbackTwo, this));
    menu_item_second->setPosition(Point(visibleSize.width/4, (visibleSize.height/4)*2.2));
    menu_item_second->setScale(0.8,0.8);

    auto alpha = Sprite::create("images/background/Alpha.png");
    alpha->setPosition(Point(visibleSize.width/2.4, (visibleSize.height/4)*2.05));
    this->addChild(alpha);

    auto rank = Sprite::create("images/background/Rank.png");
    rank->setPosition(Point(visibleSize.width*0.55, ((visibleSize.height/4)*1.1)));
    this->addChild(rank);

    auto menu_item_third = MenuItemFont::create("Help", CC_CALLBACK_1(MenuScene::HelpCallback, this));
    menu_item_third->setPosition(Point(visibleSize.width/4, (visibleSize.height/4)*1.4));
    menu_item_third->setScale(0.8,0.8);

    auto *menu = Menu::create(menu_item_single, NULL);
    menu->setPosition(Point(0,0));
    this->addChild(menu);

    auto *menu_2 = Menu::create(menu_item_second, NULL);
    menu_2->setPosition(Point(0,0));
    this->addChild(menu_2);

    auto *menu_3 = Menu::create(menu_item_third, NULL);
    menu_3->setPosition(Point(0,0));
    this->addChild(menu_3);

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/MenuTheme.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/MenuTheme.mp3", true);

    return true;
}


void MenuScene::SceneCallback(Ref* pSender)
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("WKProject", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("WKProject");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
        // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
        // if the frame's height is smaller than the height of medium size.
    else
    {
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();//TUTAJ ZMIEN JAKBYS CHCIAL DOJEBCZYC HELLOWORLDSCENE

    // run
    director->runWithScene(scene);

}
void MenuScene::SceneCallbackTwo(Ref* pSender)
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("WKProject", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("WKProject");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
        // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
        // if the frame's height is smaller than the height of medium size.
    else
    {
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = MultiWorld::createScene();//TUTAJ ZMIEN JAKBYS CHCIAL DOJEBCZYC HELLOWORLDSCENE

    // run
    director->runWithScene(scene);

}

void MenuScene::HelpCallback(Ref* pSender)
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("WKProject", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("WKProject");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
        // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
        // if the frame's height is smaller than the height of medium size.
    else
    {
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }

    register_all_packages();
    auto scene = HelpScene::createScene( );

    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );

}
