#ifndef __ZenGameScene_H__
#define __ZenGameScene_H__

#include "cocos2d.h"
#include "Script.h"
USING_NS_CC;

class ZenGameColorButton;
class ZenGameScene : public cocos2d::Layer
{
public:
    int currentVerticalNum = 4;
    int bottomLineVerticalNum = verticalNum_macro-1;
    int countSameLevelRectNum = 0;
    bool isSettedWhiteRect = false;
    int  missedZenGameColorButtonTag;
    bool isTouchLock = false;
    std::vector<int > blackRectTagVec;
    std::vector<int > UnderBottom_bottom_blackRectIndexVec;
    int twoLineCount = 0;
    bool isFirstIn = true;
    int ZenGameTotalLine = 0;
    LabelTTF * timeLabel;
    float timeNum = totalTime_macro;
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
    CREATE_FUNC(ZenGameScene);
    
    static std::vector<int > getRandomVect(int start,int end);
    static int getRandomNumber(int start,int end);
    void AllZenGameColorButtonMoveBy(const Point& MoveByD,float duration,float rate);
    void stopAllZenGameColorButtonSchedule();
    void ZenGameOver2();
    void createFillRect();
    void replaceZenGameOverScene(Ref* sender, bool cleanup);
    void OneLinePass();
    void RecordNewUnderBottom_blackRectIndex();
    
protected:
    int totalHorizontal = horizontalNum_macro;
    int totalVhertical = verticalNum_macro;
    
    
    const cocos2d::Size screenSize_macro = VisibleRect::getVisibleRect().size;
    const float screenHeight = VisibleRect::getVisibleRect().size.height;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    ZenGameColorButton * createRect(Color4B color4B,int horizontal,int vertical);
    void update(float delta);
};

#endif // __ZenGameScene_SCENE_H__
