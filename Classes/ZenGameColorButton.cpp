#include "ZenGameColorButton.h"

#include "GameOverScene.h"
#include "Script.h"
#include "SimpleAudioEngine.h"
#include "ZenGameScene.h"
#include <sstream>

using namespace std;
ZenGameColorButton::ZenGameColorButton(void)
{
}
ZenGameColorButton::~ZenGameColorButton(void)
{
}
ZenGameColorButton* ZenGameColorButton::createWithColor(const Color4B& start, const Color4B& end)
{
    ZenGameColorButton * layer = new ZenGameColorButton();
    layer->initWithColor(start, end);
    layer->autorelease();
    return layer;
}
bool ZenGameColorButton::initWithColor(const Color4B& start, const Color4B& end)
{
    if( LayerGradient::initWithColor(start, end) )
    {
        return true;
    }
    
    return false;
}
void ZenGameColorButton::onEnter()
{
    LayerGradient::onEnter();
    
    // Register Touch Event
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(ZenGameColorButton::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(ZenGameColorButton::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(ZenGameColorButton::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    rectStroke = createDrawNode( Point(0.0f,getRect().size.height));
    //scheduleUpdate();
   
    ostringstream oss;
    oss<<myLevel;
    
    auto label = LabelTTF::create(oss.str(), "Arial", bigTitleSize_macro);
    label->setColor(Color3B::RED);
    label->setAnchorPoint(Point(0.5f,0.5f));
    // position the label on the center of the screen
    label->setPosition(Point(this->getContentSize().width/2,
                             this->getContentSize().height/2));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
}

void ZenGameColorButton::onExit()
{
    LayerGradient::onExit();
}
bool ZenGameColorButton::containsTouchLocation(Touch* touch)
{
    return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}
Rect ZenGameColorButton::getRect()
{
    auto s = getContentSize();
    return Rect(0, -s.height, s.width, s.height);
}

bool ZenGameColorButton::onTouchBegan(Touch* touch, Event* event)
{
    if ( !containsTouchLocation(touch) )return false;
    if (aZenGameScene->isTouchLock)
    {
        return false;
    }
    if(2 == isBlack)
    {
        return false;
    }
    
    if(0 == isBlack)
    {
        aZenGameScene->isTouchLock=true;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(clickWhiteEffect_macro );
        CallFuncN * callFuncN = CallFuncN::create( CC_CALLBACK_1(ZenGameColorButton::replayZenGameOverScene, this, true));
        
        TintBy * tint = TintBy::create(0.3f, 240, 650, 85);
        auto reverse = tint->reverse();
        runAction(Sequence::create(tint,reverse,callFuncN,NULL));
    }
    else
    {
        if(getTag() != aZenGameScene->blackRectTagVec[0])
        {
            return false;
        }
        else
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(clickBlackEffect_macro );
            
            setStartColor(Color3B(192, 192, 192));
            setEndColor(Color3B(192, 192, 192));
            
            aZenGameScene->ZenGameTotalLine ++;
             aZenGameScene->AllZenGameColorButtonMoveBy(Point(0.0f,-this->getContentSize().height),0.5f,0.0f);
            clickBlack();
        }
    }
    return true;
}
void ZenGameColorButton::onTouchMoved(Touch* touch, Event* event)
{

}
void ZenGameColorButton::onTouchEnded(Touch* touch, Event* event)
{

}

DrawNode* ZenGameColorButton::createDrawNode( const Point& pos )
{
    auto drawNode = DrawNode::create();
    float width = getRect().size.width;
    float height = getRect().size.height;
    Point origin = getRect().origin;
    
    Size size = getRect().size;
    Point point = getRect().origin;
    Point points[4] =
    {
        origin,
        origin+Point(width,0),
        origin+Point(width,height),
        origin+Point(0,height),
    };
    drawNode->drawPolygon(points,4,Color4F(0,0,0,0),0.5,Color4F::BLACK);
    drawNode->setPosition(pos);
    this->addChild(drawNode);
    return drawNode;
}
/*
void ZenGameColorButton::update(float delta)
{
    if(getPositionY()<VisibleRect::bottom().y)
    {
        setPosition(Point(getPositionX(),VisibleRect::top().y+screenHeight/4));
        if(ZenGameScene::getRandomNumber(0,1) == 0 && !aZenGameScene->isSettedWhiteRect)
        {
            setStartColor(Color3B(0.0f,0.0f,0.0f));
            setEndColor(Color3B(0.0f,0.0f,0.0f));
            aZenGameScene->isSettedWhiteRect = true;

            aZenGameScene->blackRectTagVec.push_back(getTag());
            isBlack = 1;
            aZenGameScene->RecordNewUnderBottom_blackRectIndex();
        }
        else
        {
            if(3 == aZenGameScene->countSameLevelRectNum && !aZenGameScene->isSettedWhiteRect)
            {
                setStartColor(Color3B(0.0f,0.0f,0.0f));
                setEndColor(Color3B(0.0f,0.0f,0.0f));
                aZenGameScene->isSettedWhiteRect = true;
                
                aZenGameScene->blackRectTagVec.push_back(getTag());
                isBlack = 1;
                aZenGameScene->RecordNewUnderBottom_blackRectIndex();
            }
            else
            {
            setStartColor(Color3B(255.0f,255.0f,255.0f));
            setEndColor(Color3B(255.0f,255.0f,255.0f));
            isBlack = 0;
            }
        }
        
        aZenGameScene->OneLinePass();
    }
}
 */
void ZenGameColorButton::replayZenGameOverScene(Ref* sender, bool cleanup)
{
    auto scene =  GameOverScene::scene();
    auto gameOverScene = (GameOverScene*)scene->getChildByTag(1001);
    gameOverScene->setUpScene(Color4B(255,0,0,255),"禅","失败!",Zen_enum);
    Director::getInstance()->replaceScene(scene);
}
void ZenGameColorButton::clickBlack()
{
    vector<int>::iterator iter = aZenGameScene->blackRectTagVec.begin();
    aZenGameScene->blackRectTagVec.erase(iter);
  
    aZenGameScene->currentVerticalNum--;
    if(aZenGameScene->currentVerticalNum<0)
    {
        aZenGameScene->currentVerticalNum = verticalNum_macro-1;
    }
}

void ZenGameColorButton::getZenGameScenePoint(ZenGameScene * ZenGameScene)
{
    aZenGameScene = ZenGameScene;
}