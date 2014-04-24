#include "CommonGameColorButton.h"

#include "GameOverScene.h"
#include "Script.h"
#include "SimpleAudioEngine.h"
#include "CommonGameScene.h"
#include <sstream>

using namespace std;
CommonGameColorButton::CommonGameColorButton(void)
{
}
CommonGameColorButton::~CommonGameColorButton(void)
{
}
CommonGameColorButton* CommonGameColorButton::createWithColor(const Color4B& start, const Color4B& end)
{
    CommonGameColorButton * layer = new CommonGameColorButton();
    layer->initWithColor(start, end);
    layer->autorelease();
    return layer;
}
bool CommonGameColorButton::initWithColor(const Color4B& start, const Color4B& end)
{
    if( LayerGradient::initWithColor(start, end) )
    {
        return true;
    }
    
    return false;
}
void CommonGameColorButton::onEnter()
{
    LayerGradient::onEnter();
    
    // Register Touch Event
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(CommonGameColorButton::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(CommonGameColorButton::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(CommonGameColorButton::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    rectStroke = createDrawNode( Point(0.0f,getRect().size.height));
    scheduleUpdate();
   
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

void CommonGameColorButton::onExit()
{
    LayerGradient::onExit();
}
bool CommonGameColorButton::containsTouchLocation(Touch* touch)
{
    return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}
Rect CommonGameColorButton::getRect()
{
    auto s = getContentSize();
    return Rect(0, -s.height, s.width, s.height);
}

bool CommonGameColorButton::onTouchBegan(Touch* touch, Event* event)
{
    if ( !containsTouchLocation(touch) )return false;
    if (aCommonGameScene->isTouchLock)
    {
        return false;
    }
    if(2 == isBlack)
    {
        return false;
    }
    
    if(0 == isBlack)
    {
        aCommonGameScene->isTouchLock=true;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(clickWhiteEffect_macro );
        CallFuncN * callFuncN = CallFuncN::create( CC_CALLBACK_1(CommonGameColorButton::replayCommonGameOverScene, this, true));
        
        TintBy * tint = TintBy::create(0.3f, 240, 650, 85);
        auto reverse = tint->reverse();
        runAction(Sequence::create(tint,reverse,callFuncN,NULL));
    }
    else
    {
        if(getTag() != aCommonGameScene->blackRectTagVec[0])
        {
            return false;
        }
        else
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(clickBlackEffect_macro );
            
            setStartColor(Color3B(192, 192, 192));
            setEndColor(Color3B(192, 192, 192));
            
            aCommonGameScene->commonGameTotalLine --;
            if(aCommonGameScene->commonGameTotalLine != -2)
            {
                aCommonGameScene->AllCommonGameColorButtonMoveBy(Point(0.0f,-this->getContentSize().height),0.5f,0.0f);
            }
            else
            {
                aCommonGameScene->AllCommonGameColorButtonMoveBy(Point(0.0f,-this->getContentSize().height*2.5),0.5f,0.0f);
            }
            
            clickBlack();
        }
    }
    return true;
}
void CommonGameColorButton::onTouchMoved(Touch* touch, Event* event)
{

}
void CommonGameColorButton::onTouchEnded(Touch* touch, Event* event)
{

}

DrawNode* CommonGameColorButton::createDrawNode( const Point& pos )
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
void CommonGameColorButton::simulationActionUpdate()
{
    
}

void CommonGameColorButton::update(float delta)
{
    if(getPositionY()<VisibleRect::bottom().y && 0<aCommonGameScene->commonGameTotalLine)
    {
        setPosition(Point(getPositionX(),VisibleRect::top().y+screenHeight/4));
        if(CommonGameScene::getRandomNumber(0,1) == 0 && !aCommonGameScene->isSettedWhiteRect)
        {
            setStartColor(Color3B(0.0f,0.0f,0.0f));
            setEndColor(Color3B(0.0f,0.0f,0.0f));
            aCommonGameScene->isSettedWhiteRect = true;

            aCommonGameScene->blackRectTagVec.push_back(getTag());
            isBlack = 1;
            aCommonGameScene->RecordNewUnderBottom_blackRectIndex();
        }
        else
        {
            if(3 == aCommonGameScene->countSameLevelRectNum && !aCommonGameScene->isSettedWhiteRect)
            {
                setStartColor(Color3B(0.0f,0.0f,0.0f));
                setEndColor(Color3B(0.0f,0.0f,0.0f));
                aCommonGameScene->isSettedWhiteRect = true;
                
                aCommonGameScene->blackRectTagVec.push_back(getTag());
                isBlack = 1;
                aCommonGameScene->RecordNewUnderBottom_blackRectIndex();
            }
            else
            {
            setStartColor(Color3B(255.0f,255.0f,255.0f));
            setEndColor(Color3B(255.0f,255.0f,255.0f));
            isBlack = 0;
            }
        }
        
        aCommonGameScene->OneLinePass();
    }
}
void CommonGameColorButton::replayCommonGameOverScene(Ref* sender, bool cleanup)
{
    Director::getInstance()->replaceScene( GameOverScene::scene() );
}
void CommonGameColorButton::clickBlack()
{
    vector<int>::iterator iter = aCommonGameScene->blackRectTagVec.begin();
    aCommonGameScene->blackRectTagVec.erase(iter);
  
    aCommonGameScene->currentVerticalNum--;
    if(aCommonGameScene->currentVerticalNum<0)
    {
        aCommonGameScene->currentVerticalNum = verticalNum_macro-1;
    }
}

void CommonGameColorButton::getCommonGameScenePoint(CommonGameScene * CommonGameScene)
{
    aCommonGameScene = CommonGameScene;
}