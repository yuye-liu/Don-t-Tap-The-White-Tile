#include "HelloWorldScene.h"
#include "VisibleRect.h"
#include "ColorButton.h"
#include "GameOverScene.h"
#include "Script.h"

USING_NS_CC;
using namespace std;
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    vector<const char *> labelTitleVec;
    labelTitleVec.push_back("经典");
    labelTitleVec.push_back("街机");
    labelTitleVec.push_back("禅");
    
    Color4B color4B1;
    Color4B color4B2;
    Color3B color3B;
    int drawWhite = 0;
    
    for (int vertical = 0; vertical<2; vertical++)
    {
        for (int horizontal=0; horizontal<2; horizontal++)
        {
            if (0 == drawWhite)
            {
                color4B1 = Color4B(255,255,255,255);
                color3B = Color3B(0, 0, 0);
            }
            else
            {
                color4B1 = Color4B(0, 0, 0,255);
                color3B = Color3B(255,255,255);
            }
            color4B2 = Color4B(255,179,167,255);
            
            ColorButton* layer = createRect(color4B1,color4B2,horizontal,vertical);
            
            if (horizontal+vertical*2!=labelTitleVec.size())
            {
                createLabel(layer,labelTitleVec,color3B,horizontal,vertical);
            }
            else
            {
                createLastRectLabel(layer,color3B);
            }
            
            drawWhite++;
            if (drawWhite>2)
            {
                drawWhite = 0;
            }
        }
    }
    return true;
}
ColorButton*  HelloWorld::createRect(Color4B color4B1,Color4B color4B2,int horizontal,int vertical)
{
    Size rect = VisibleRect::getVisibleRect().size;

    
    ColorButton * layer = ColorButton::createWithColor(color4B1, color4B1);
    layer->setTag(horizontal+vertical*2);
    layer->setAnchorPoint(Point(0.0f,1.0f));
    layer->ignoreAnchorPointForPosition(false);
    layer->setContentSize(rect/2);
    layer->setPosition(VisibleRect::leftTop()+Point(rect.width/2*horizontal,-rect.height/2*vertical));
    addChild(layer);
    
    return layer;
}

void HelloWorld::createLabel(ColorButton* layer,vector<const char *> labelTitleVec,Color3B color3B,int horizontal,int vertical)
{
    auto label = LabelTTF::create(labelTitleVec.at(horizontal+vertical*2), "Arial", bigTitleSize_macro);
    label->setColor(color3B);
    label->setAnchorPoint(Point(0.5f,0.5f));
    // position the label on the center of the screen
    label->setPosition(Point(layer->getContentSize().width/2,
                             layer->getContentSize().height/2));
    
    // add the label as a child to this layer
    layer->addChild(label, 1);
}

void HelloWorld::createLastRectLabel(ColorButton* layer,Color3B color3B)
{
    vector<const char *> labelTitleVec;
    labelTitleVec.push_back("指引:关");
    labelTitleVec.push_back("排行榜");
    labelTitleVec.push_back("评分");
    labelTitleVec.push_back("更多游戏");
    
    auto menu = Menu::create();
    menu->setPosition(Point::ZERO);
    layer->addChild(menu, 1);
    
    for(int i = 0 ;i<4;i++)
    {
        auto closeItem = MenuItemFont::create(labelTitleVec.at(i),
                                              CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
        closeItem->setFontSizeObj(bigTitleSize_macro);
        closeItem->setColor(color3B);
        closeItem->setTag(i);
        closeItem->setPosition(Point(layer->getContentSize().width/2 ,
                                     layer->getContentSize().height-layer->getContentSize().height*(i+2)/(labelTitleVec.size()+2)));
        
        menu->addChild(closeItem);
    }

}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    MenuItemFont * aItem = (MenuItemFont *)pSender;
    switch (aItem->getTag())
    {
        case 0:
            Director::getInstance()->replaceScene( GameOverScene::scene() );
            break;
        case 1:
            //Director::getInstance()->replaceScene( GameOverScene::scene() );
            break;
        case 2:
            Director::getInstance()->replaceScene( GameOverScene::scene() );
            break;
        case 3:
            //Director::getInstance()->replaceScene( GameOverScene::scene() );
            break;
            
        default:
            break;
    }
}



