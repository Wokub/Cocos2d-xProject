#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}



// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto bg = Sprite::create("images/background.jpg");
    bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    bg->setScale(0.55, 0.55);
    this->addChild(bg);

    auto scoreboard = Sprite::create("images/Frame.png");
    scoreboard->setPosition(Point((visibleSize.width/2) + origin.x, visibleSize.height));
    scoreboard->setScale(0.75, 0.75);
    this->addChild(scoreboard);


    mySprite = Sprite::create("images/Player.png");
    mySprite->setPosition(Point((visibleSize.width/4.6) + origin.x, (visibleSize.height/4.2)+origin.y));
    mySprite->setScale(0.34, 0.34);
    this->addChild(mySprite);

    auto ground = Sprite::create("images/Ground.png");
    ground->setPosition(Point((visibleSize.width/2) + origin.x, origin.y));
    ground->setScale(0.25, 0.2);
    this->addChild(ground);

    auto grass = Sprite::create("images/Grass.png");
    grass->setPosition(Point((visibleSize.width/2) + origin.x, (visibleSize.height/9) + origin.y));
    grass->setScale(0.15, 0.1);
    this->addChild(grass);



    //Audio
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/Theme.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/Theme.mp3", true);

    //Background

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
