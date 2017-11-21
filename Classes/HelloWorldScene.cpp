#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"

USING_NS_CC;

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

    // przycisk skoku
    auto closeItem = MenuItemImage::create(
                                           "images/buttons/Button_Jump.png",// po Button_Jump2.png można dopisać, i przed nawiasem dać inne funkncjonalności
                                           "images/buttons/Button_Jump2.png");//CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

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

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


    // przycisk prawy
    auto rightItem = MenuItemImage::create(
            "images/buttons/Button_Right.png",
            "images/buttons/Button_Right2.png");

    if (rightItem == nullptr ||
        rightItem->getContentSize().width <= 0 ||
        rightItem->getContentSize().height <= 0)
    {
        problemLoading("'Button_Right.png' and 'Button_Right2.png'");
    }
    else
    {
        float x = visibleSize.width/2.75 + origin.x;
        float y = origin.y + rightItem->getContentSize().height/1.5;
        rightItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu_2 = Menu::create(rightItem, NULL);
    menu_2->setPosition(Vec2::ZERO);
    this->addChild(menu_2, 1);

    // przycisk lewy
    auto leftItem = MenuItemImage::create(
            "images/buttons/Button_Left.png",
            "images/buttons/Button_Left2.png");

    if (leftItem == nullptr ||
        leftItem->getContentSize().width <= 0 ||
        leftItem->getContentSize().height <= 0)
    {
        problemLoading("'Button_Left.png' and 'Button_Left2.png'");
    }
    else
    {
        float x = visibleSize.width/7 + origin.x;
        float y = origin.y + leftItem->getContentSize().height/1.5;
        leftItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu_3 = Menu::create(leftItem, NULL);
    menu_3->setPosition(Vec2::ZERO);
    this->addChild(menu_3, 1);

    // 2. creating objects
    auto bg = Sprite::create("images/background/background.jpg");
    bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    bg->setScale(0.55, 0.55);
    this->addChild(bg);

    auto edgeBody = PhysicsBody::createEdgeBox( visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 0.1 );
    edgeBody->setCollisionBitmask( OBSTACLE_COLLISION_BITMASK );
    edgeBody->setContactTestBitmask( true );

    auto edgeNode = Node::create();
    edgeNode->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );

    edgeNode->setPhysicsBody( edgeBody );

    this->addChild( edgeNode );

    //auto scoreboard = Sprite::create("images/objects/Frame.png");
    //scoreboard->setPosition(Point((visibleSize.width/2) + origin.x, visibleSize.height));
    //scoreboard->setScale(0.75, 0.75);
    //this->addChild(scoreboard);

    auto butterfly_1 = Sprite::create("images/objects/Butterfly_1.png");
    butterfly_1->setPosition(Point((visibleSize.width/4) + origin.x, visibleSize.height/2));
    butterfly_1->setScale(0.75, 0.75);
    this->addChild(butterfly_1);

    auto butterfly_2 = Sprite::create("images/objects/Butterfly_2.png");
    butterfly_2->setPosition(Point((visibleSize.width/2) + origin.x, visibleSize.height));
    butterfly_2->setScale(0.75, 0.75);
    this->addChild(butterfly_2);

    auto butterfly_3 = Sprite::create("images/objects/Butterfly_3.png");
    butterfly_3->setPosition(Point((visibleSize.width/3) + origin.x, visibleSize.height/3));
    butterfly_3->setScale(0.75, 0.75);
    this->addChild(butterfly_3);

    character = Sprite::create("images/characters/Player.png");
    character->setPosition(Point((visibleSize.width/4.6) + origin.x, visibleSize.height/2));
    character->setScale(0.34, 0.34);
    this->addChild(character);

    ground = Sprite::create("images/background/Ground.jpg");
    ground->setPosition(Point((visibleSize.width/2) + origin.x, (visibleSize.height/3)));
    this->addChild(ground);

    bridge = Sprite::create("images/background/Bridge.png");
    bridge->setPosition(Point((visibleSize.width/2) + origin.x, (visibleSize.height/5)));
    this->addChild(bridge);

    //Ruch obiektow
    auto rotateAction = RotateBy::create(2,118);
    auto action_2 = Sequence::create(rotateAction, MoveBy::create(5,Point(100,80)),NULL);
    butterfly_1->runAction(action_2);

    //Audio
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/Theme.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/Theme.mp3", true);

    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)//funkcja wylaczajaca
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}





