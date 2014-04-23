#ifndef __GameColorButton_H__
#define __GameColorButton_H__

#include "cocos2d.h"
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

    GameColorButton(void);
    virtual ~GameColorButton(void);
    virtual void onEnter() override;
    virtual void onExit() override;
    
    bool initWithColor(const Color4B& start, const Color4B& end);
    
    bool containsTouchLocation(Touch* touch);
    Rect getRect();
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    DrawNode* createDrawNode( const Point& pos );
    void simulationActionUpdate();
    void update(float delta);
    void replayGameOverScene(Ref* sender, bool cleanup);
    void clickBlack(Ref* sender, bool cleanup);
};

#endif // __HELLOWORLD_SCENE_H__
