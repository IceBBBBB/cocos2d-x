#include "AppDelegate.h"

#include "cocos2d.h"
#include "controller.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    // SimpleAudioEngine::end();
    cocos2d::extension::CCArmatureDataManager::purge();
    cocos2d::extension::DictionaryHelper::purgeDictionaryHelper();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // As an example, load config file
    // XXX: This should be loaded before the Director is initialized,
    // XXX: but at this point, the director is already initialized
    CCConfiguration::sharedConfiguration()->loadConfigFile("configs/config-example.plist");

    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->setDisplayStats(true);
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();

    CCSize designSize = CCSizeMake(screenSize.width/3, screenSize.height/3);

    CCFileUtils* pFileUtils = CCFileUtils::sharedFileUtils();
    std::vector<std::string> searchPaths;

    if (screenSize.height > 320)
    {
        CCSize resourceSize = CCSizeMake(screenSize.width, screenSize.height);
        searchPaths.push_back("hd");
        searchPaths.push_back("ccs-res/hd");
        searchPaths.push_back("ccs-res/hd/scenetest/ArmatureComponentTest");
        searchPaths.push_back("ccs-res/hd/scenetest/AttributeComponentTest");
        searchPaths.push_back("ccs-res/hd/scenetest/BackgroundComponentTest");
        searchPaths.push_back("ccs-res/hd/scenetest/EffectComponentTest");
        searchPaths.push_back("ccs-res/hd/scenetest/LoadSceneEdtiorFileTest");
        searchPaths.push_back("ccs-res/hd/scenetest/ParticleComponentTest");
        searchPaths.push_back("ccs-res/hd/scenetest/SpriteComponentTest");
        searchPaths.push_back("ccs-res/hd/scenetest/TmxMapComponentTest");
        searchPaths.push_back("ccs-res/hd/scenetest/UIComponentTest");
        searchPaths.push_back("ccs-res/hd/scenetest/TriggerTest");
        searchPaths.push_back("ccs-res");
        pDirector->setContentScaleFactor(resourceSize.height/designSize.height);
    }
    else
    {
        searchPaths.push_back("ccs-res");
        searchPaths.push_back("ccs-res/scenetest/ArmatureComponentTest");
        searchPaths.push_back("ccs-res/scenetest/AttributeComponentTest");
        searchPaths.push_back("ccs-res/scenetest/BackgroundComponentTest");
        searchPaths.push_back("ccs-res/scenetest/EffectComponentTest");
        searchPaths.push_back("ccs-res/scenetest/LoadSceneEdtiorFileTest");
        searchPaths.push_back("ccs-res/scenetest/ParticleComponentTest");
        searchPaths.push_back("ccs-res/scenetest/SpriteComponentTest");
        searchPaths.push_back("ccs-res/scenetest/TmxMapComponentTest");
        searchPaths.push_back("ccs-res/scenetest/UIComponentTest");
        searchPaths.push_back("ccs-res/scenetest/TriggerTest");
    }
    pFileUtils->setSearchPaths(searchPaths);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionShowAll);
#else
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionNoBorder);
#endif

    CCScene * pScene = CCScene::create();
    CCLayer * pLayer = new TestController();
    pLayer->autorelease();

    pScene->addChild(pLayer);
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}

void AppDelegate::applicationScreenSizeChanged(int newWidth, int newHeight) {
    auto director = CCDirector::sharedDirector();
    auto glview = director->getOpenGLView();
    if (glview != NULL) {
        glview->setFrameSize(newWidth, newHeight);
        // Set the design resolution to a proper value. here use a value
        // different with the game is started.
        glview->setDesignResolutionSize(newWidth / 2, newHeight / 2, kResolutionNoBorder);
    }
}
