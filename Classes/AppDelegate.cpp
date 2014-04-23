#include "AppDelegate.h"

#include <vector>
#include <string>

#include "HelloWorldScene.h"


USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate() {
    
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview)
    {
        glview = GLView::create("Cpp Empty Test");
        director->setOpenGLView(glview);
    }
    
    director->setOpenGLView(glview);
    
    // Set the design resolution
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    // a bug in DirectX 11 level9-x on the device prevents ResolutionPolicy::NO_BORDER from working correctly
    glview->setDesignResolutionSize(320, 480, ResolutionPolicy::SHOW_ALL);
#else
    glview->setDesignResolutionSize(320, 480, ResolutionPolicy::NO_BORDER);
#endif
    
	Size frameSize = glview->getFrameSize();
    
    vector<string> searchPath;
    /*
    searchPath.push_back("iphone");
    searchPath.push_back("ipad");
    searchPath.push_back("ipadhd");
    */
    searchPath.push_back("soundEffect");
    //searchPath.push_back("piano");
    
    director->setContentScaleFactor(3);
	
    // set searching path
    FileUtils::getInstance()->setSearchPaths(searchPath);
	
    // turn on display FPS
    director->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();
    
    // run
    director->runWithScene(scene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
