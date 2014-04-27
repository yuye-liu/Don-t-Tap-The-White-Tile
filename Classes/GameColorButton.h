#ifndef __GameColorButton_H__
#define __GameColorButton_H__

#include "cocos2d.h"
#include "VisibleRect.h"
USING_NS_CC;

class GameScene;
class GameColorButton : public LayerGradient
{
public:
    int isBlack;
    int myLevel;
    
    static GameColorButton* createWithColor(const Color4B& start, const Color4B& end);
    void getGameScenePoint(GameScene * gameScene);
    
protected:
    DrawNode* rectStroke;
    GameScene * aGameScene;
    
    const cocos2d::Size screenSize_macro = VisibleRect::getVisibleRect().size;
    const float screenHeight = VisibleRect::getVisibleRect().size.height;
    
    GameColorButton(void);
    virtual ~GameColorButton(void);
    virtual void onEnter() override;
    virtual void onExit() override;
    
    bool initWithColor(const Color4B& start, const Color4B& end);
    
    bool containsTouchLocation(Touch* touch);
    Rect getRect();
    bool onTouchBegan(Touch* touch, Event* event);
    DrawNode* createDrawNode( const Point& pos );
    void replayGameOverScene(Ref* sender, bool cleanup);
    void clickBlack();
};

#endif // __HELLOWORLD_SCENE_H__
