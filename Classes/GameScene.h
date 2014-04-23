#ifndef __GameScene_H__
#define __GameScene_H__

#include "cocos2d.h"
#include "Script.h"
USING_NS_CC;

class GameColorButton;
class GameScene : public cocos2d::Layer
{
public:
    int currentVerticalNum = 4;
    int bottomLineVerticalNum = verticalNum_macro;
    int countSameLevelRectNum = 0;
    bool isSettedWhiteRect = false;
    int  missedGameColorButtonTag;
    bool isTouchLock = false;
    std::vector<int > blackRectTagVec;
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
    CREATE_FUNC(GameScene);
    
    static std::vector<int > getRandomVect(int start,int end);
    static int getRandomNumber(int start,int end);
    void AllGameColorButtonMoveBy(const Point& MoveByD);
    void stopAllGameColorButtonSchedule();
    void gameOver2();
    void replaceGameOverScene(Ref* sender, bool cleanup);
    
protected:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    std::vector<GameColorButton * > gameColorButtonVec;
    GameColorButton * createRect(Color4B color4B,int horizontal,int vertical);
    
};

#endif // __GameScene_SCENE_H__
