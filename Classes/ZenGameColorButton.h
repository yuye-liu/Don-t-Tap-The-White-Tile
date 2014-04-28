#ifndef __ZenGameColorButton_H__
#define __ZenGameColorButton_H__

#include "cocos2d.h"
#include "VisibleRect.h"
USING_NS_CC;

class ZenGameScene;
class ZenGameColorButton : public LayerGradient
{
public:
    int isBlack;
    int myLevel;
    
    static ZenGameColorButton* createWithColor(const Color4B& start, const Color4B& end);
    void getZenGameScenePoint(ZenGameScene * ZenGameScene);
    
protected:
    DrawNode* rectStroke;
    ZenGameScene * aZenGameScene;
    
    const cocos2d::Size screenSize_macro = VisibleRect::getVisibleRect().size;
    const float screenHeight = VisibleRect::getVisibleRect().size.height;
    
    ZenGameColorButton(void);
    virtual ~ZenGameColorButton(void);
    virtual void onEnter() override;
    virtual void onExit() override;
    
    bool initWithColor(const Color4B& start, const Color4B& end);
    
    bool containsTouchLocation(Touch* touch);
    Rect getRect();
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    DrawNode* createDrawNode( const Point& pos );
    //void update(float delta);
    void replayZenGameOverScene(Ref* sender, bool cleanup);
    void clickBlack();
};

#endif // __HELLOWORLD_SCENE_H__
