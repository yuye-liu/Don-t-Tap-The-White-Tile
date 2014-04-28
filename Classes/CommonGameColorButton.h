#ifndef __CommonGameColorButton_H__
#define __CommonGameColorButton_H__

#include "cocos2d.h"
#include "VisibleRect.h"
USING_NS_CC;

class CommonGameScene;
class CommonGameColorButton : public LayerGradient
{
public:
    int isBlack;
    int myLevel;
    
    static CommonGameColorButton* createWithColor(const Color4B& start, const Color4B& end);
    void getCommonGameScenePoint(CommonGameScene * CommonGameScene);
    
protected:
    DrawNode* rectStroke;
    CommonGameScene * aCommonGameScene;
    
    const cocos2d::Size screenSize_macro = VisibleRect::getVisibleRect().size;
    const float screenHeight = VisibleRect::getVisibleRect().size.height;
    
    CommonGameColorButton(void);
    virtual ~CommonGameColorButton(void);
    virtual void onEnter() override;
    virtual void onExit() override;
    
    bool initWithColor(const Color4B& start, const Color4B& end);
    
    bool containsTouchLocation(Touch* touch);
    Rect getRect();
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    DrawNode* createDrawNode( const Point& pos );

    void replayCommonGameOverScene(Ref* sender, bool cleanup);
    void replaceGameOverScene(float dt);
    void clickBlack();
};

#endif // __HELLOWORLD_SCENE_H__
