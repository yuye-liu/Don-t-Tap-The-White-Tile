#include "GameOverScene.h"
#include "VisibleRect.h"
#include "ColorButton.h"
#include "HelloWorldScene.h"
#include "GameScene.h"

USING_NS_CC;
using namespace std;
Scene* GameOverScene::scene()
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
    
    LayerGradient * layer = LayerGradient::create(Color4B(240, 65, 85,255), Color4B(240, 65, 85,255));
    layer->setPosition(VisibleRect::leftBottom());
    addChild(layer);

    
    titleLabel = LabelTTF::create(titleStr, "Arial", 24*1.5);
    titleLabel->setColor(Color3B(255,255,255));
    titleLabel->setAnchorPoint(Point(0.5f,0.5f));
    // position the label on the center of the screen
    titleLabel->setPosition(Point(VisibleRect::center().x,VisibleRect::top().y-60));
    
    // add the label as a child to this layer
    layer->addChild(titleLabel, 1);
    
    resultLabel = LabelTTF::create(resultStr, "Arial", 24*4);
    resultLabel->setColor(Color3B(0,0,0));
    resultLabel->setAnchorPoint(Point(0.5f,0.5f));
    // position the label on the center of the screen
    resultLabel->setPosition(VisibleRect::center()+Point(0.0f,30.0f));
    
    // add the label as a child to this layer
    layer->addChild(resultLabel, 1);
    
    auto menu = Menu::create();
    menu->setPosition(Point::ZERO);
    layer->addChild(menu, 1);

    shareItem = MenuItemFont::create("分享",
                                     CC_CALLBACK_1(GameOverScene::share, this));
    shareItem->setFontSizeObj(24);
    shareItem->setColor(Color3B(255,255,255));
    shareItem->setPosition(VisibleRect::bottom()-Point(100,-100));
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
    replayItem->setPosition(VisibleRect::bottom()-Point(-100,-100));
    menu->addChild(replayItem);
                           
    return true;
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
    Director::getInstance()->replaceScene( GameScene::scene() );
}

