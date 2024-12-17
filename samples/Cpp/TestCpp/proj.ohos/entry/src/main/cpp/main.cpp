#include "AppDelegate.h"
#include "cocos2d.h"
#include "CCEventType.h"
#include "CCLogOhos.h"

using namespace cocos2d;

extern "C"
{

void Cocos2dxRenderer_nativeInit(int w, int h)
{
    OHOS_LOGD("Cocos2dxRenderer_nativeInit() - window width:[%{public}d], height:[%{public}d]", w, h);
    if (!CCDirector::sharedDirector()->getOpenGLView())
    {
        CCEGLView *view = CCEGLView::sharedOpenGLView();
        view->setFrameSize(w, h);

        AppDelegate *pAppDelegate = new AppDelegate();
        CCApplication::sharedApplication()->run();
    }
    else
    {
        ccGLInvalidateStateCache();
        CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
        ccDrawInit();
        CCTextureCache::reloadAllTextures();
        CCNotificationCenter::sharedNotificationCenter()->postNotification(EVNET_COME_TO_FOREGROUND, NULL);
        CCDirector::sharedDirector()->setGLDefaultValues(); 
    }
}

}