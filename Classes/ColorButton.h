#ifndef __ColorButton_H__
#define __ColorButton_H__

#include "cocos2d.h"
USING_NS_CC;

class ColorButton : public LayerGradient
{
public:
    ColorButton(void);
    virtual ~ColorButton(void);
    virtual void onEnter() override;
    virtual void onExit() override;
    
    bool initWithColor(const Color4B& start, const Color4B& end);
   
    bool containsTouchLocation(Touch* touch);
    Rect getRect();
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
    static ColorButton* createWithColor(const Color4B& start, const Color4B& end);
};

#endif // __HELLOWORLD_SCENE_H__
