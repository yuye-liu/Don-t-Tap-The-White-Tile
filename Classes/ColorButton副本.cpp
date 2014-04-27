#include "ColorButton.h"
#include "VisibleRect.h"
#include "GameScene.h"
#include "CommonGameScene.h"
#include "ZenGameScene.h"

ColorButton::ColorButton(void)
{
}

ColorButton::~ColorButton(void)
{
}
ColorButton* ColorButton::createWithColor(const Color4B& start, const Color4B& end)
{
    ColorButton * layer = new ColorButton();
    layer->initWithColor(start, end);
    layer->autorelease();
    
    return layer;
}
bool ColorButton::initWithColor(const Color4B& start, const Color4B& end)
{
    if( LayerGradient::initWithColor(start, end) )
    {
        return true;
    }
    
    return false;
}
void ColorButton::onEnter()
{
    LayerGradient::onEnter();
    
    // Register Touch Event
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(ColorButton::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(ColorButton::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(ColorButton::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void ColorButton::onExit()
{
    //    auto director = Director::getInstance();
    //    director->getTouchDispatcher()->removeDelegate(this);
    LayerGradient::onExit();
}
bool ColorButton::containsTouchLocation(Touch* touch)
{
    
    return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}
Rect ColorButton::getRect()
{
    auto s = getContentSize();
    return Rect(0, -s.height, s.width, s.height);
}

bool ColorButton::onTouchBegan(Touch* touch, Event* event)
{
    CCLOG("Paddle::onTouchBegan id = %d, x = %f, y = %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);
    
    if ( !containsTouchLocation(touch) )return false;

   // log("%d",this->getTag());
    switch (this->getTag())
    {
        case 0:
            Director::getInstance()->replaceScene( CommonGameScene::scene() );
            break;
        case 1:
            Director::getInstance()->replaceScene( GameScene::scene() );
            break;
        case 2:
            Director::getInstance()->replaceScene( ZenGameScene::scene() );
            break;
        case 3:
            ;
            break;
            
        default:
            break;
    }
  /*
    auto scene = new GameScene();
    auto layer = Layer::create();
    scene->addChild( layer, 0 );
    Director::getInstance()->replaceScene(TransitionFlipX::create(2, scene) );
    scene->release();
    */
    
    
    return true;
}
void ColorButton::onTouchMoved(Touch* touch, Event* event)
{

}
void ColorButton::onTouchEnded(Touch* touch, Event* event)
{

}



