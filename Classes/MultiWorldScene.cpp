#include "MultiWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"
#include <iostream>

USING_NS_CC;

//Tworzenie sceny
Scene* MultiWorld::createScene()
{
    auto scene = Scene::createWithPhysics();
    //Poniższą linijkę można wyłączyć dodając ją jako komentarz. Jest ona odpowiedzialna za wyrysowanie kolizji
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);//wyrysowanie, daj jako komentarz jesli chcesz usunac czerwona otoczke

    scene->getPhysicsWorld()->setGravity(Vect(0,0));//Vect(20,20) np., daj (0,0) zeby wylaczyc latanie do gory pilki

    auto layer = MultiWorld::create();
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

bool MultiWorld::init()
{
    //Inicjalizacja
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT, 3);

    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width/2 + origin.x , visibleSize.height/2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);

    this->addChild(edgeNode);

    //Tworzenie przycisku skoku
    auto closeItem = MenuItemImage::create(
                    "images/buttons/Button_Jump.png",
                    "images/buttons/Button_Jump2.png",
                    CC_CALLBACK_1(MultiWorld::menuJumpCallback, this)
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
        //moze dodaj grawitacje zalezna od przycisku?
        closeItem->setPosition(Vec2(x,y));
    }

    //Tworzenie "menu", tj. miejsca pod przycisk
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    //Tworzenie prawego przycisku
    auto rightItem = MenuItemImage::create(
            "images/buttons/Button_Right.png",
            "images/buttons/Button_Right2.png",
            CC_CALLBACK_1(MultiWorld::menuRightCallback, this));

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

    //Tworzenie "menu", tj. miejsca pod przycisk
    auto menu_2 = Menu::create(rightItem, NULL);
    menu_2->setPosition(Vec2::ZERO);
    this->addChild(menu_2, 1);

    // przycisk lewego przycisku
    auto leftItem = MenuItemImage::create(
            "images/buttons/Button_Left.png",
            "images/buttons/Button_Left2.png",
            CC_CALLBACK_1(MultiWorld::menuLeftCallback, this));

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

    //Tworzenie "menu", tj. miejsca pod przycisk
    auto menu_3 = Menu::create(leftItem, NULL);
    menu_3->setPosition(Vec2::ZERO);
    this->addChild(menu_3, 1);

    //Tworzenie tla
    auto bg = Sprite::create("images/background/Pirates_BG.jpg");
    bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    bg->setScale(0.7, 0.7);
    this->addChild(bg);

    auto water = Sprite::create("images/objects/Water.png");
    water->setPosition(Vec2(origin.x + visibleSize.width / 2, (visibleSize.height/5)-22));
    water->setScale(1 , 0.2);
    this->addChild(water);
    auto waterAnim = RepeatForever::create(Sequence::create(MoveTo::create(2, Point(origin.x + visibleSize.width/2 + 10, (visibleSize.height/5) - 22)),
                                      MoveTo::create(3, Point(origin.x + visibleSize.width/2 - 10, (visibleSize.height/5) - 22)), NULL));//missing sentinel

    water->runAction(waterAnim);


    //secondScoreLabel->setPosition(visibleSize.width/1.6,visibleSize.height/1.2);
    //Tworzenie tablicy wyników
    auto scoreboard = Sprite::create("images/objects/Frame.png");
    scoreboard->setPosition(Point((visibleSize.width/2) + origin.x, visibleSize.height));
    scoreboard->setScale(0.3, 0.3);
    this->addChild(scoreboard);


    //Tworzenie pilki
    ball = Sprite::create("images/objects/Ball.png");
    ball->setPosition(visibleSize.width/2, visibleSize.height/2.3);
    ball->setScale(0.3,0.3);
    auto ballBody = PhysicsBody::createCircle(ball->getContentSize().width/2, PhysicsMaterial(0,1,0));
    ball->setPhysicsBody(ballBody);
    ballBody->setCollisionBitmask(2);
    ballBody->setContactTestBitmask(true);

    this->addChild(ball);

    auto ballStartingAnimation = JumpBy::create(1, Point(0,0),50,1);
    ball->runAction(ballStartingAnimation);

    if(ball->getPosition().y < visibleSize.width/2 )
    {
        auto ballAnim = RepeatForever::create(RotateBy::create(1,90));
        ball->runAction(ballAnim);
    }

    //Tworzenie obiektu do single_player
    enemy = Sprite::create("images/characters/Player_2.png");
    enemy->setPosition(visibleSize.width/1.3, visibleSize.height/2);
    enemy->setScale(0.34,0.34);
    auto enemyBody = PhysicsBody::createBox(enemy->getContentSize(), PhysicsMaterial(0,1,0));
    enemyBody->setDynamic(false);
    enemy->setPhysicsBody(enemyBody);
    enemyBody->setCollisionBitmask(3);
    enemyBody->setContactTestBitmask(true);
    this->addChild(enemy);

    //Tworzenie gracza
    character = Sprite::create("images/characters/Player.png");
    character->setPosition(Point((visibleSize.width/4.4) + origin.x, visibleSize.height/2));
    auto characterBody = PhysicsBody::createBox(character->getContentSize(), PhysicsMaterial(0,1,0));
    characterBody->setDynamic(false);
    character->setScale(0.34, 0.34);
    character->setPhysicsBody(characterBody);
    characterBody->setDynamic(false);
    characterBody->setCollisionBitmask(1);
    characterBody->setContactTestBitmask(true);
    this->addChild(character);

    goalone = Sprite::create("images/objects/Goal.png");
    goalone->setPosition(Point(visibleSize.width/20.3, visibleSize.height/1.55));
    goalone->setScale(0.3, 0.4);
    auto goaloneBody = PhysicsBody::createBox(goalone->getContentSize(), PhysicsMaterial(0,1,0));
    goaloneBody->setDynamic(false);
    goalone->setPhysicsBody(goaloneBody);
    goaloneBody->setCollisionBitmask(4);
    goaloneBody->setContactTestBitmask(true);
    this->addChild(goalone);

    goaltwo = Sprite::create("images/objects/Goal2.png");
    goaltwo->setPosition(Point(visibleSize.width/1.05, visibleSize.height/1.55));
    goaltwo->setScale(0.3, 0.4);
    auto goaltwoBody = PhysicsBody::createBox(goaltwo->getContentSize(), PhysicsMaterial(0,1,0));
    goaltwoBody->setDynamic(false);
    goaltwo->setPhysicsBody(goaltwoBody);
    goaltwoBody->setCollisionBitmask(5);
    goaltwoBody->setContactTestBitmask(true);
    this->addChild(goaltwo);


    //Tworzenie mostu
    bridge = Sprite::create("images/background/Bridge.png");//Ładowanie grafiki
    bridge->setPosition(Point((visibleSize.width/2) + origin.x, (visibleSize.height/5.1)));
    auto bridgeBody = PhysicsBody::createBox(bridge->getContentSize(), PhysicsMaterial(0,1,0));//mozesz dac enemy by sprawdzic fizyke
    bridgeBody->setDynamic(false);
    bridge->setPhysicsBody(bridgeBody);
    this->addChild(bridge);

    //Wywołanie efektów audio
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/MainTheme.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/MainTheme.mp3", true);

    //Zmienne odpowiedzialne za sprawdzanie czy nastąpił kontakt, tj. kolizja
    //Kreator
    auto contactListener = EventListenerPhysicsContact::create();
    //Przypisanie elementu funkcji
    contactListener->onContactBegin = CC_CALLBACK_1(MultiWorld::onContactBegin, this);
    //Wywołanie
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    return true;
}

//Funkcja wprawiająca postać w skok po wciśnięciu przycisku skoku
void MultiWorld::menuJumpCallback(Ref* pSender)
{
    //Zmienne zawierające widoczny rozmiar ekranu oraz "pochodzenie" wywołane lokalnie
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto action = JumpBy::create(1, Point(0,0),100,1);//Akcja odpowiedzialna za skok
    character->runAction(action);//Wywołanie akcji
}

//Funkcja wprawiająca postać w ruch po wciśnięciu prawego przycisku
void MultiWorld::menuRightCallback(Ref* pSender)
{
    //Zmienne zawierające widoczny rozmiar ekranu oraz "pochodzenie" wywołane lokalnie
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto action = MoveBy::create(1,Point(80,0));//Akcja odpowiedzialna za ruch w prawo
    character->runAction(action);//Wywołanie akcji

    //Tymczasowy warunek sprawiający, że odległość na jaką może iść postać w prawo jest ograniczona
   if(character->getPositionX() > visibleSize.width)
   {
    character->setPositionX(visibleSize.width - 25);
   }
}

//Funkcja wprawiająca postać w ruch po wciśnięciu lewego przycisku
void MultiWorld::menuLeftCallback(Ref* pSender)
{
    //Zmienne zawierające widoczny rozmiar ekranu oraz "pochodzenie" wywołane lokalnie
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto action = MoveBy::create(1,Point(-80,0));//Akcja odpowiedzialna za ruch w lewo
    character->runAction(action);//Wywołanie akcji
}

//Funkcja zawierająca kolizję
bool MultiWorld::onContactBegin(cocos2d::PhysicsContact &contact)
{
    //Zmienne zawierające widoczny rozmiar ekranu oraz "pochodzenie" wywołane lokalnie
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //Tworzenie ciał fizycznych, zawierających kształt obiektu
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    PhysicsBody *c = contact.getShapeA()->getBody();
    PhysicsBody *d = contact.getShapeA()->getBody();
    PhysicsBody *e = contact.getShapeA()->getBody();


    int firstplayerscore = 0;
    int secondplayerscore = 0;

    //Warunek na kolizję piłki i pierwszego gracza, możliwe, że będzie trzeba usunąć
    //(ball->getPositionX() > visibleSize.height/2.3)
    if ((ball->getPositionX() > visibleSize.height/2.3) and ( 1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask() )
         || ( 2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask() ) )
    {
        int *firstpscore = &firstplayerscore;
        auto ballStartingAnimation = JumpBy::create(2, Point(150, 0), 50, 3);//Tworzenie zmiennej zawierającej animację skoku piłki
        ball->runAction(ballStartingAnimation);//Wywołanie animacji
    }


    //Warunek na kolizję piłki i przeciwnika, możesz spróbować z pierwszym warunkiem if-a
    if((ball->getPositionX() > visibleSize.height/2.3) and ( 3 == c->getCollisionBitmask() && 2 == b->getCollisionBitmask() )
       || ( 2 == c->getCollisionBitmask() && 3 == b->getCollisionBitmask() ) )
    {
        auto ballStartingAnimation = JumpTo::create(2, Point(-450, visibleSize.height/2.3 - 20 ),
                                                    50, 3);//Tworzenie skoku, spróbuj zmanipulować
        // to visibleSize - 20. Liczba ustala w którym miejscu ma się odnowić piłka, możliwe,
        //że zastąpi nam to warunek na przenikanie piłki przez most
        ball->runAction(ballStartingAnimation);//Wywołanie animacji
    }

    if((ball->getPositionX() > visibleSize.height/2.3) and ( 4 == c->getCollisionBitmask() && 2 == b->getCollisionBitmask() )
       || ( 2 == c->getCollisionBitmask() && 4 == b->getCollisionBitmask() ) )
    {
        ball->setPosition(visibleSize.width/2, visibleSize.height/2.3);
        secondplayerscore += 1;
    }

    if((ball->getPositionX() > visibleSize.height/2.3) and ( 5 == c->getCollisionBitmask() && 2 == b->getCollisionBitmask() )
       || ( 2 == c->getCollisionBitmask() && 5 == b->getCollisionBitmask() ) )
    {
        ball->setPosition(visibleSize.width/2, visibleSize.height/2.3);
        secondplayerscore += 1;
    }

    __String *firstscore = __String::createWithFormat("%i", firstplayerscore);
    auto firstScoreLabel = Label::createWithTTF(firstscore->getCString(), "fonts/arial.ttf", 32.0f);
    firstScoreLabel->setColor(Color3B::WHITE);
    firstScoreLabel->setPosition(visibleSize.width/2.65,visibleSize.height/1.05);
    this->addChild(firstScoreLabel, 10000);

    __String *secondscore = __String::createWithFormat("%i", secondplayerscore);
    auto secondScoreLabel = Label::createWithTTF(secondscore->getCString(), "fonts/arial.ttf", 32.0f);
    secondScoreLabel->setColor(Color3B::WHITE);
    secondScoreLabel->setPosition(visibleSize.width/1.65,visibleSize.height/1.05);
    this->addChild(secondScoreLabel, 10000);

    /////////
    //Dodaj warunek sprawiający, że piłka nie może spać poniżej mostu

    return true;
}



