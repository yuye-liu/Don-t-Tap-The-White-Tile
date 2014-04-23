#include "GameColorButton.h"
#include "VisibleRect.h"
#include "GameOverScene.h"
#include "Script.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include <sstream>

using namespace std;
GameColorButton::GameColorButton(void)
{
}
GameColorButton::~GameColorButton(void)
{
}
GameColorButton* GameColorButton::createWithColor(const Color4B& start, const Color4B& end)
{
    GameColorButton * layer = new GameColorButton();
    layer->initWithColor(start, end);
    layer->autorelease();
    return layer;
}
bool GameColorButton::initWithColor(const Color4B& start, const Color4B& end)
{
    if( LayerGradient::initWithColor(start, end) )
    {
        return true;
    }
    
    return false;
}
void GameColorButton::onEnter()
{
    LayerGradient::onEnter();
    
    // Register Touch Event
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(GameColorButton::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameColorButton::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameColorButton::onTouchEnded, this);
    
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

void GameColorButton::onExit()
{
    LayerGradient::onExit();
}
bool GameColorButton::containsTouchLocation(Touch* touch)
{
    return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}
Rect GameColorButton::getRect()
{
    auto s = getContentSize();
    return Rect(0, -s.height, s.width, s.height);
}

bool GameColorButton::onTouchBegan(Touch* touch, Event* event)
{
    if (aGameScene->isFirstIn)
    {
        aGameScene->isFirstIn = false;
        aGameScene->AllGameColorButtonMoveBy(Point(0,-VisibleRect::getVisibleRect().size.height*2),rectScrollSpeed_macro,0.0f);
        return false;
    }
    if(2 == isBlack)
    {
        return false;
    }
    if (aGameScene->isTouchLock)
    {
        return false;
    }
    if ( !containsTouchLocation(touch) )return false;
    if(0 == isBlack)
    {
        aGameScene->isTouchLock=true;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(clickWhiteEffect_macro );
        CallFuncN * callFuncN = CallFuncN::create( CC_CALLBACK_1(GameColorButton::replayGameOverScene, this, true));
        
        TintBy * tint = TintBy::create(0.3f, 240, 650, 85);
        auto reverse = tint->reverse();
        runAction(Sequence::create(tint,reverse,callFuncN,NULL));
    }
    else
    {
        /*
        for(int num:aGameScene->blackRectTagVec)
        {
            log("kk==%d",num);
        }
        log("%d;%d",getTag(),aGameScene->blackRectTagVec[0]);
         */
        if(getTag() != aGameScene->blackRectTagVec[0])
        {
            aGameScene->gameOver2();
        }
        else
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(clickBlackEffect_macro );
            CallFuncN * callFuncN = CallFuncN::create( CC_CALLBACK_1(GameColorButton::clickBlack, this, true));
            
            TintBy * tint = TintBy::create(0.3f, 192, 192, 192);
            runAction(Sequence::create(tint,callFuncN,NULL));
        }
    }
    return true;
}
void GameColorButton::onTouchMoved(Touch* touch, Event* event)
{

}
void GameColorButton::onTouchEnded(Touch* touch, Event* event)
{

}

DrawNode* GameColorButton::createDrawNode( const Point& pos )
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
void GameColorButton::simulationActionUpdate()
{
    
}
void GameColorButton::update(float delta)
{
    if(getPositionY()<0)
    {
        if (getTag() == aGameScene->blackRectTagVec[0])
        {
            aGameScene->gameOver2();
            return;
        }
        stopAllActions();
        
        int height = VisibleRect::getVisibleRect().size.height;
        
        //log("bottomLineVerticalNum:%d,%d",aGameScene->bottomLineVerticalNum,myLevel+1);
        /*
        GameColorButton * aObj;
        if(verticalNum_macro == aGameScene->bottomLineVerticalNum)
        {
           aObj = (GameColorButton * )aGameScene->getChildByTag(0);
        }
        else
        {
            aObj = (GameColorButton * )aGameScene->getChildByTag((myLevel+1)*4);
        }
        
        setPosition(Point(getPositionX(),aObj->getPositionY()+aObj->getContentSize().height-3));
        */
        setPosition(Point(getPositionX(),height+height/4));
        
        if(GameScene::getRandomNumber(0,1) == 0 && !aGameScene->isSettedWhiteRect)
        {
            setStartColor(Color3B(0.0f,0.0f,0.0f));
            setEndColor(Color3B(0.0f,0.0f,0.0f));
            aGameScene->isSettedWhiteRect = true;
            /*
            vector<int>::iterator iter = aGameScene->blackRectTagVec.begin();
            aGameScene->blackRectTagVec.erase(iter);
            */
            aGameScene->blackRectTagVec.push_back(getTag());
            isBlack = 1;
        }
        else
        {
            setStartColor(Color3B(255.0f,255.0f,255.0f));
            setEndColor(Color3B(255.0f,255.0f,255.0f));
            isBlack = 0;
        }
        
        aGameScene->countSameLevelRectNum++;
        if(aGameScene->countSameLevelRectNum>3)
        {
            aGameScene->isSettedWhiteRect = false;
            aGameScene->countSameLevelRectNum = 0;
            
            aGameScene->bottomLineVerticalNum--;
            if (aGameScene->bottomLineVerticalNum<0)
            {
                aGameScene->bottomLineVerticalNum = verticalNum_macro;
            }
        }
        
        Action * MoveBy = MoveBy::create(rectScrollSpeed_macro, Point(0,-height*2));
        this->runAction(MoveBy);
    }
}
void GameColorButton::replayGameOverScene(Ref* sender, bool cleanup)
{
    Director::getInstance()->replaceScene( GameOverScene::scene() );
}
void GameColorButton::clickBlack(Ref* sender, bool cleanup)
{
    vector<int>::iterator iter = aGameScene->blackRectTagVec.begin();
    aGameScene->blackRectTagVec.erase(iter);
   /*
    for(int num:aGameScene->blackRectTagVec)
    {
        log("%d",num);
    }
    */
    aGameScene->currentVerticalNum--;
    if(aGameScene->currentVerticalNum<0)
    {
        aGameScene->currentVerticalNum = verticalNum_macro;
    }
}
void GameColorButton::getGameScenePoint(GameScene * gameScene)
{
    aGameScene = gameScene;
}