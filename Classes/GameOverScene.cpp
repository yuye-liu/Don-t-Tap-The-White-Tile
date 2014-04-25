#include "GameOverScene.h"
#include "VisibleRect.h"
#include "ColorButton.h"
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "ZenGameScene.h"
#include "CommonGameScene.h"

USING_NS_CC;
using namespace std;
Scene* GameOverScene::scene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();

    // add layer as a child to scene
    scene->addChild(layer,0,1001);
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
    
    return true;
}
void GameOverScene::setUpScene(Color4B bgColor,const char *titleStr,const char * resultStr,int Scene)
{
    sceneState = Scene;
    LayerGradient * layer = LayerGradient::create(bgColor, bgColor);
    layer->setPosition(VisibleRect::leftBottom());
    addChild(layer);
    
    
    titleLabel = LabelTTF::create(titleStr, "Arial", 24*1.5);
    titleLabel->setColor(Color3B(255,255,255));
    titleLabel->setPosition(VisibleRect::top()-Point(0,60.0f));
    this->addChild(titleLabel, 1);
    log("resultStr=%s",resultStr);
    resultLabel = LabelTTF::create(resultStr, "Arial", 24*4);
    resultLabel->setColor(Color3B(0,0,0));
    resultLabel->setAnchorPoint(Point(0.5f,0.0f));
    resultLabel->setPosition(VisibleRect::center());
    this->addChild(resultLabel, 1);
    
    auto menu = Menu::create();
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    shareItem = MenuItemFont::create("分享",
                                     CC_CALLBACK_1(GameOverScene::share, this));
    shareItem->setFontSizeObj(24);
    shareItem->setColor(Color3B(255,255,255));
    shareItem->setPosition(VisibleRect::leftBottom()+Point(60,100));
    menu->addChild(shareItem);
    
    backItem = MenuItemFont::create("返回",
                                    CC_CALLBACK_1(GameOverScene::back, this));
    backItem->setFontSizeObj(24);
    backItem->setColor(Color3B(255,255,255));
    backItem->setPosition(VisibleRect::bottom()-Point(0,-100));
    menu->addChild(backItem);
    
    replayItem = MenuItemFont::create("重来",
                                      CC_CALLBACK_1(GameOverScene::replay, this));
    replayItem->setFontSizeObj(24);
    replayItem->setColor(Color3B(255,255,255));
    replayItem->setPosition(VisibleRect::rightBottom()+Point(-60,100));
    menu->addChild(replayItem);
}
void GameOverScene::share(Ref* pSender)
{
}
void GameOverScene::back(Ref* pSender)
{
    Director::getInstance()->replaceScene( HelloWorld::createScene() );
}
void GameOverScene::replay(Ref* pSender)
{
    log("sceneState = %d",sceneState);
    switch (sceneState)
    {
        case Common_enum:
            Director::getInstance()->replaceScene( CommonGameScene::scene() );
            break;
        case Zen_enum:
            Director::getInstance()->replaceScene( ZenGameScene::scene() );
            break;
        case Street_enum:
            Director::getInstance()->replaceScene( GameScene::scene() );
            break;
        default:
            break;
    }
}
