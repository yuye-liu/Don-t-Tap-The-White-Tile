#ifndef __GameOverScene_H__
#define __GameOverScene_H__

#include "cocos2d.h"
USING_NS_CC;

class GameOverScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    const char * titleStr = "经典模式";
    
    const char * resultStr = "败了!";
    
    LabelTTF * titleLabel;
    
    LabelTTF * resultLabel;
    
    MenuItemFont * shareItem;
    
    MenuItemFont * backItem;
    
    MenuItemFont * replayItem;
    
    
    void share(Ref* pSender);
    void back(Ref* pSender);
    void replay(Ref* pSender);
    
    CREATE_FUNC(GameOverScene);
};

#endif // __GameOverScene_SCENE_H__
