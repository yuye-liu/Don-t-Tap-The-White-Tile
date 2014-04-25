#ifndef __GameOverScene_H__
#define __GameOverScene_H__

#include "cocos2d.h"
USING_NS_CC;

enum sceneName
{
    Common_enum,
    Zen_enum,
    Street_enum,
};


class GameOverScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    /*
    std::string titleStr;
    
    std::string resultStr;
    
    Color4B bgColor;
    */
    
    int sceneState;
    
    LabelTTF * titleLabel;
    
    LabelTTF * resultLabel;
    
    MenuItemFont * shareItem;
    
    MenuItemFont * backItem;
    
    MenuItemFont * replayItem;
    
    void setUpScene(Color4B bgColor,const char *titleStr,const char * resultStr,int Scene);
    void share(Ref* pSender);
    void back(Ref* pSender);
    void replay(Ref* pSender);
    
    CREATE_FUNC(GameOverScene);
};

#endif // __GameOverScene_SCENE_H__
