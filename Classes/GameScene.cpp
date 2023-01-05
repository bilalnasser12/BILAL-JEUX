
#include "GameScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    PhysicsWorld* world = scene->getPhysicsWorld();
    auto layer = GameScene::create();
    layer->SetPysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}
// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {

        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto background = Sprite::create("background.png");
    background->setScaleX(1.3);
    background->setPosition(250, 165);
    this->addChild(background);

    auto dontpush = Sprite::create("don'tpushbutton.png");
    dontpush->setScale(0.15);
    dontpush->setPosition(200,75);
    this->addChild(dontpush , 2);
     
    auto exit = Sprite::create("exitbutton.webp");
    exit->setScale(0.5);
    exit->setPosition(450,250);
    this->addChild(exit,2);

    auto pico = Sprite::create("classic.png");
    pico->setPosition(20, 87);
    pico->setScale(0.5);

    this->addChild(pico, 2);
    auto eventListner = EventListenerKeyboard::create();
    eventListner->onKeyPressed = [](EventKeyboard::KeyCode KeyCode, Event* event) {
        Vec2 loc = event->getCurrentTarget()->getPosition();
        switch (KeyCode)
        {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case EventKeyboard::KeyCode::KEY_A:
            event->getCurrentTarget()->runAction(MoveBy::create(0.09f, Vec2(-20, 0)));

            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case EventKeyboard::KeyCode::KEY_D:
            event->getCurrentTarget()->runAction(MoveBy::create(0.09f, Vec2(20, 0)));
            break;

        case EventKeyboard::KeyCode::KEY_SPACE:
        case EventKeyboard::KeyCode::KEY_W:

            event->getCurrentTarget()->runAction(JumpBy::create(0.5, Vec2(30, 0), 30, 1));
            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        case EventKeyboard::KeyCode::KEY_S:
            event->getCurrentTarget()->runAction(JumpBy::create(0.5, Vec2(-30, 0), 30, 1));
            break;
        }

    };
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListner, pico);
    this->scheduleUpdate();


    Rect frame = Rect(0, 0, 01000, 1000);
    auto followplayer = Follow::create(pico, frame);
    this->runAction(followplayer);




    return true;
}


