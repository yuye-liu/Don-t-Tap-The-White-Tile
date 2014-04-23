#include "GameScene.h"
#include "VisibleRect.h"
#include "GameColorButton.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"

USING_NS_CC;
using namespace std;
Scene* GameScene::scene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(clickWhiteEffect_macro);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(clickBlackEffect_macro);
    
    Color4B color4B;
    bool getThisRoundBlackRect = false;
    
    
    std::vector<int > tempVec;
    
    for (int vertical = 0; vertical<verticalNum_macro+1; vertical++)
    {
        getThisRoundBlackRect = false;
        for (int horizontal=0; horizontal<4; horizontal++)
        {
            int isBlack;
            if(getRandomNumber(0,1)==0 && !getThisRoundBlackRect && verticalNum_macro!=vertical)
            {
                color4B = Color4B(0,0,0,255);
                getThisRoundBlackRect = true;
                tempVec.push_back(horizontal+4*vertical);
                isBlack = 1;
            }
            else if(verticalNum_macro == vertical)
            {
                color4B = Color4B(255,215,0,255);
                isBlack = 2;
            }
            else
            {
                color4B = Color4B(255,255,255,255);
                isBlack = 0;
            }
            GameColorButton* layer = createRect(color4B,horizontal,vertical);
            layer->setTag(horizontal+4*vertical);
            gameColorButtonVec.push_back(layer);
            layer->isBlack = isBlack;
            /*
            Action * MoveBy = MoveBy::create(rectScrollSpeed_macro, Point(0,-VisibleRect::getVisibleRect().size.height*2));
            layer->runAction(MoveBy);
             */
        }
    }

    for (int i = 0; i<tempVec.size(); i++)
    {
        blackRectTagVec.push_back(tempVec[tempVec.size()-1-i]);
    }
    
    return true;
}
GameColorButton*  GameScene::createRect(Color4B color4B,int horizontal,int vertical)
{
    Size size = VisibleRect::getVisibleRect().size;
    GameColorButton * layer = GameColorButton::createWithColor(color4B, color4B);
    layer->getGameScenePoint(this);
    layer->myLevel = vertical;
    layer->ignoreAnchorPointForPosition(false);
    layer->setAnchorPoint(Point(0.0f,1.0f));
    layer->setContentSize(size/4);
    layer->setPosition(VisibleRect::leftTop()+Point(size.width/4*horizontal,
                             size.height/4-size.height/4*vertical));
    addChild(layer);
    
    return layer;
}
vector<int > GameScene::getRandomVect(int start,int end)
{
    vector<int > randomVect;
    
    int quantity = 12;
    int total = abs(end - start);
    if (quantity >total)
    {
        log("随机数错误");
    }
    int sequence[total];  //存放随机数的数组
    int output[quantity]; //最终生成的不重复一系列随机数
    
    //将sequence 初始化
    for (int i = 0; i < total; i++)
    {
        sequence[i] = start+i;
    }
    //随机数种子
    timeval psv;
    gettimeofday(&psv, NULL);
    unsigned long int seed = psv.tv_sec*1000 + psv.tv_usec/1000;
    srand(seed);
    
    for (int i = 0; i < quantity; i++)
    {
        int num = GameScene::getRandomNumber(0, end - 1);//在指定范围下产生随机数
        output[i] = sequence[num];//将产生的随机数存储
        randomVect[i] = sequence[num];
        sequence[num] = sequence[end-1];//将最后个下标的值填充到随机产生的下标中
        end--;//在指定范围 向前移
    }
    
    return randomVect;
}
int GameScene::getRandomNumber(int start,int end)
{
    return CCRANDOM_0_1()*(end+1-start)+start;
}

void GameScene::AllGameColorButtonMoveBy(const Point& MoveByD,float duration,float rate)
{
    for(GameColorButton* obj:gameColorButtonVec)
    {
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
}
void GameScene::stopAllGameColorButtonSchedule()
{
    for(GameColorButton* obj:gameColorButtonVec)
    {
        obj->stopAllActions();
        obj->unscheduleAllSelectors();
    }
}
void GameScene::gameOver2()
{
    GameColorButton* missedRect = (GameColorButton *)getChildByTag(blackRectTagVec[0]);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(clickBlackEffect_macro );

    isTouchLock = true;
    stopAllGameColorButtonSchedule();
    AllGameColorButtonMoveBy(Point(0.0f,missedRect->getContentSize().height*2),0.5f,0.5f);
    
    CallFuncN * callFuncN = CallFuncN::create( CC_CALLBACK_1(GameScene::replaceGameOverScene, this, true));
    
    TintBy * tint = TintBy::create(0.3f, 192, 192, 192);
    Repeat * repeat = Repeat::create(tint, 4);
    
    missedRect->runAction(Sequence::create(repeat,callFuncN,NULL));
}
void GameScene::replaceGameOverScene(Ref* sender, bool cleanup)
{
    Director::getInstance()->replaceScene( GameOverScene::scene() );
}

