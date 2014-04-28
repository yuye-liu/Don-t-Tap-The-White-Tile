#include "ZenGameScene.h"
#include "VisibleRect.h"
#include "ZenGameColorButton.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"

USING_NS_CC;
using namespace std;


Scene* ZenGameScene::scene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ZenGameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ZenGameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(clickWhiteEffect_macro);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(clickBlackEffect_macro);
    
    LayerGradient * bgLayer = LayerGradient::create(Color4B(0, 255, 0,255), Color4B(0, 255, 0,255));
    bgLayer->setPosition(VisibleRect::leftBottom());
    addChild(bgLayer);
    
    Color4B color4B;
    bool getThisRoundBlackRect = false;
    
    for (int vertical = 0; vertical<totalVhertical; vertical++)
    {
        getThisRoundBlackRect = false;
        for (int horizontal=0; horizontal<horizontalNum_macro; horizontal++)
        {
            int isBlack;
            if(getRandomNumber(0,1)==0 && !getThisRoundBlackRect && totalVhertical!=vertical+1)
            {
                color4B = Color4B(0,0,0,255);
                getThisRoundBlackRect = true;
                blackRectTagVec.insert(blackRectTagVec.begin(),horizontal+4*vertical);
                isBlack = 1;
                
                if (totalVhertical-3 == vertical ||
                    totalVhertical-5 == vertical)
                {
                    UnderBottom_bottom_blackRectIndexVec.insert(UnderBottom_bottom_blackRectIndexVec.begin(),horizontal);
                }
            }
            else if(totalVhertical == vertical+1)
            {
                color4B = Color4B(255,215,0,255);
                isBlack = 2;
            }
            else
            {
                if(3 == horizontal && !getThisRoundBlackRect)
                {
                    color4B = Color4B(0,0,0,255);
                    getThisRoundBlackRect = true;
                    blackRectTagVec.insert(blackRectTagVec.begin(),horizontal+4*vertical);
                    isBlack = 1;

                    if (totalVhertical-3 == vertical ||
                        totalVhertical-5 == vertical)
                    {
                        UnderBottom_bottom_blackRectIndexVec.insert(UnderBottom_bottom_blackRectIndexVec.begin(),horizontal);
                    }
                }
                else
                {
                    color4B = Color4B(255,255,255,255);
                    isBlack = 0;
                }
            }
            ZenGameColorButton* layer = createRect(color4B,horizontal,vertical);
            layer->setTag(horizontal+horizontalNum_macro*vertical);
            layer->isBlack = isBlack;
        }
    }
    
    timeNum-=0.001;
    ostringstream oss;
    oss<<timeNum;
    string timeStr = oss.str();
    timeStr = timeStr.substr(0,5);
    timeStr = "'"+timeStr+"'";
    const char * time = timeStr.c_str();
    
    timeLabel = LabelTTF::create(time, "Arial", TimerSize_macro);
    timeLabel->setColor(Color3B::RED);
    timeLabel->setAnchorPoint(Point(0.5f,1.0f));
    timeLabel->setPosition(VisibleRect::top());
    this->addChild(timeLabel, 1);
    
    scheduleUpdate();
    
    return true;
}
ZenGameColorButton*  ZenGameScene::createRect(Color4B color4B,int horizontal,int vertical)
{
    ZenGameColorButton * layer = ZenGameColorButton::createWithColor(color4B, color4B);
    layer->getZenGameScenePoint(this);
    layer->myLevel = vertical;
    layer->ignoreAnchorPointForPosition(false);
    layer->setAnchorPoint(Point(0.0f,1.0f));
    layer->setContentSize(screenSize_macro/4);
    layer->setPosition(VisibleRect::leftTop()+Point(screenSize_macro.width/4*horizontal,
                             screenSize_macro.height/4-screenSize_macro.height/4*vertical));
    addChild(layer);
    
    return layer;
}
int ZenGameScene::getRandomNumber(int start,int end)
{
    return CCRANDOM_0_1()*(end+1-start)+start;
}

void ZenGameScene::AllZenGameColorButtonMoveBy(const Point& MoveByD,float duration,float rate)
{
    for(int i = 0;i<totalVhertical*horizontalNum_macro;i++)
    {
        ZenGameColorButton * obj = (ZenGameColorButton * )getChildByTag(i);
        MoveBy * moveByD = MoveBy::create(duration, MoveByD);
        if(0 == rate)
        {
            obj->runAction(moveByD);
        }
        else
        {
            EaseIn * easeIn = EaseIn::create(moveByD, rate);
            obj->runAction(easeIn);
        }
    }
    CallFuncN * callFuncN = CallFuncN::create( CC_CALLBACK_1(ZenGameScene::loopRoll, this, true));
    runAction(Sequence::create(DelayTime::create(rectScrollSpeed_macro),callFuncN,NULL));
}
void ZenGameScene::loopRoll(Ref* sender, bool cleanup)
{
    for(int i = 0;i<4;i++)
    {
        ZenGameColorButton * gameColorButton = (ZenGameColorButton * )getChildByTag(bottomLineVerticalNum*4+i);
        
        int topLine = bottomLineVerticalNum+1;
        if (topLine>4)
        {
            topLine = 0;
        }
        ZenGameColorButton * topButton = (ZenGameColorButton * )getChildByTag(topLine*4);
        
        gameColorButton->setPosition(Point(gameColorButton->getPositionX(),topButton->getPosition().y+gameColorButton->getContentSize().height));
        if(ZenGameScene::getRandomNumber(0,1) == 0 && !isSettedWhiteRect)
        {
            gameColorButton->setStartColor(Color3B(0.0f,0.0f,0.0f));
            gameColorButton->setEndColor(Color3B(0.0f,0.0f,0.0f));
            isSettedWhiteRect = true;
            
            blackRectTagVec.push_back(gameColorButton->getTag());
            gameColorButton->isBlack = 1;
            RecordNewUnderBottom_blackRectIndex(i);
        }
        else
        {
            if(!isSettedWhiteRect)
            {
                gameColorButton->setStartColor(Color3B(0.0f,0.0f,0.0f));
                gameColorButton->setEndColor(Color3B(0.0f,0.0f,0.0f));
                isSettedWhiteRect = true;
                
                blackRectTagVec.push_back(gameColorButton->getTag());
                gameColorButton->isBlack = 1;
                RecordNewUnderBottom_blackRectIndex(i);
            }
            else
            {
                gameColorButton->setStartColor(Color3B(255.0f,255.0f,255.0f));
                gameColorButton->setEndColor(Color3B(255.0f,255.0f,255.0f));
                gameColorButton->isBlack = 0;
            }
        }
    }
    OneLinePass();
}
void ZenGameScene::stopAllZenGameColorButtonSchedule()
{
    for(int i = 0;i<totalVhertical*horizontalNum_macro;i++)
    {
        ZenGameColorButton * obj = (ZenGameColorButton * )getChildByTag(i);
        obj->stopAllActions();
        obj->unscheduleAllSelectors();
    }
}
void ZenGameScene::ZenGameOver2()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(clickBlackEffect_macro );
    
    createFillRect();
    
    ZenGameColorButton* missedRect = (ZenGameColorButton *)getChildByTag(blackRectTagVec[0]);
    isTouchLock = true;
    stopAllZenGameColorButtonSchedule();
 
    AllZenGameColorButtonMoveBy(Point(0.0f,missedRect->getContentSize().height*2),0.5f,0.5f);
    
    CallFuncN * callFuncN = CallFuncN::create( CC_CALLBACK_1(ZenGameScene::replaceZenGameOverScene, this, true));
    
    TintBy * tint = TintBy::create(0.3f, 192, 192, 192);
    Repeat * repeat = Repeat::create(tint, 10);
    
    missedRect->runAction(Sequence::create(repeat,callFuncN,NULL));
}
void ZenGameScene::createFillRect()
{
    for (int i = 0; i<4; i++)
    {
        ZenGameColorButton * zenGameColorButton = (ZenGameColorButton * )getChildByTag(bottomLineVerticalNum*4+i);
        zenGameColorButton->setPosition(Point(zenGameColorButton->getPositionX(),VisibleRect::top().y+zenGameColorButton->getContentSize().height));
    }
    
    Color4B color4B;
    for (int vertical = 0; vertical<2; vertical++)
    {
        for (int horizontal=0; horizontal<horizontalNum_macro; horizontal++)
        {
            color4B = Color4B(255,255,255,255);
            if(horizontal == UnderBottom_bottom_blackRectIndexVec[0] && vertical == 0)
            {
                color4B = Color4B(0,0,0,255);
            }
            else if(horizontal == UnderBottom_bottom_blackRectIndexVec[1] && vertical == 1)
            {
                color4B = Color4B(0,0,0,255);
            }
            ZenGameColorButton * layer = ZenGameColorButton::createWithColor(color4B, color4B);
            layer->getZenGameScenePoint(this);
            layer->myLevel = totalVhertical;
            layer->ignoreAnchorPointForPosition(false);
            layer->setAnchorPoint(Point(0.0f,1.0f));
            layer->setContentSize(screenSize_macro/4);
            layer->setPosition(VisibleRect::leftBottom()+Point(screenSize_macro.width/4*horizontal,-screenSize_macro.height/4*vertical));
            addChild(layer);
            
            layer->setTag(horizontal+totalHorizontal*totalVhertical);
        }
        totalVhertical++;
    }
}
void ZenGameScene::replaceZenGameOverScene(Ref* sender, bool cleanup)
{
    Director::getInstance()->replaceScene( GameOverScene::scene() );
}
void ZenGameScene::OneLinePass()
{
    isSettedWhiteRect = false;
    
    bottomLineVerticalNum--;
    if (bottomLineVerticalNum<0)
    {
        bottomLineVerticalNum = totalVhertical-1;
    }
    
    twoLineCount++;
    if(twoLineCount>1)
    {
        twoLineCount = 0;
    }
}
void ZenGameScene::RecordNewUnderBottom_blackRectIndex(int whiteIdx)
{
    if (1 == twoLineCount)
    {
        vector<int>::iterator iter = UnderBottom_bottom_blackRectIndexVec.begin();
        UnderBottom_bottom_blackRectIndexVec.erase(iter);
        UnderBottom_bottom_blackRectIndexVec.push_back(whiteIdx);
    }
}
void ZenGameScene::update(float delta)
{
    timeNum-=0.001;
    ostringstream oss;
    oss<<timeNum;
    string timeStr = oss.str();
    timeStr = timeStr.substr(0,5);
    timeStr = "'"+timeStr+"'";
    const char * time = timeStr.c_str();
    timeLabel->setString(time);
    if(0 == timeNum && !isTouchLock)
    {
        auto scene =  GameOverScene::scene();
        auto gameOverScene = (GameOverScene*)scene->getChildByTag(1001);
        gameOverScene->setUpScene(Color4B(255,0,0,255),"禅","失败!",Zen_enum);
        Director::getInstance()->replaceScene(scene);
    }
}
