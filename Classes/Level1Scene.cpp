#include "Level1Scene.h"
#include "GameScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* Level1Scene::createScene()
{


    auto scene = Scene::createWithPhysics();
    PhysicsWorld* world = scene->getPhysicsWorld();

    auto layer = Level1Scene::create();
    layer->SetPysicsWorld( scene->getPhysicsWorld( ) );

    scene->addChild(layer);
  
    return scene;
}


// on "init" you need to initialize your instance
bool Level1Scene::init()
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
    background->setPosition(250,165);
    this->addChild(background);

    auto pico = Sprite::create("classic.png");
    pico->setPosition(20,87);
    pico->setScale(0.5);



    this->addChild(pico, 1);
    
  
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

    auto playbtn = MenuItemImage::create("level2button.png","level2button.png", CC_CALLBACK_1(Level1Scene::GoToGameScene, this));
    playbtn->setScale(0.5);
    playbtn->setPosition(Point(450,250));

    auto menu = Menu::create(playbtn,NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    return true;
}

void Level1Scene::GoToGameScene(cocos2d::Ref* sender)
{
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

