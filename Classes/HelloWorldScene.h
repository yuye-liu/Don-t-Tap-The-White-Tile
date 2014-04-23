#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class ColorButton;
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    ColorButton*  createRect(Color4B color4B1,Color4B color4B2,int horizontal,int vertical);
    
    void createLabel(ColorButton* layer,std::vector<const char *> labelTitleVec,Color3B color3B,int horizontal,int vertical);
    
    void createLastRectLabel(ColorButton* layer,Color3B color3B);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
