#include "deprecated/CCSet.h"
#include "CCDirector.h"
#include "CCTouch.h"
#include "platform/ohos/CCGLView.h"
#include "platform/ohos/CCLogOhos.h"

using namespace cocos2d;

extern "C" {
    void Cocos2dxRenderer_nativeTouchesBegin(intptr_t id, float x, float y) {
        cocos2d::Director::sharedDirector()->getOpenGLView()->handleTouchesBegin(1, &id, &x, &y);
    }

    void Cocos2dxRenderer_nativeTouchesEnd(intptr_t id, float x, float y) {
        cocos2d::Director::sharedDirector()->getOpenGLView()->handleTouchesEnd(1, &id, &x, &y);
    }

    void Cocos2dxRenderer_nativeTouchesMove(intptr_t id, float x, float y) {
       cocos2d::Director::sharedDirector()->getOpenGLView()->handleTouchesMove(1, &id, &x, &y);
    }

    void Cocos2dxRenderer_nativeTouchesCancel(intptr_t id, float x, float y) {
       cocos2d::Director::sharedDirector()->getOpenGLView()->handleTouchesCancel(1, &id, &x, &y);
    }

    #define KEYCODE_BACK 0x04
    #define KEYCODE_MENU 0x52

    bool Cocos2dxRenderer_nativeKeyDown(int keyCode) {
       Director* pDirector = Director::sharedDirector();
       switch (keyCode) {
           case KEYCODE_BACK:
                    // TBD need fixed 
//                 if (pDirector->getKeypadDispatcher()->dispatchKeypadMSG(kTypeBackClicked))
                   return true;
               break;
           case KEYCODE_MENU:
//               if (pDirector->getKeypadDispatcher()->dispatchKeypadMSG(kTypeMenuClicked))
                   return true;
               break;
           default:
               return false;
       }
        return 0;
    }
}
