#ifndef __TouchesNapi_H__
#define __TouchesNapi_H__

#include "cocoa/CCSet.h"
#include "keypad_dispatcher/CCKeypadDispatcher.h"
#include "touch_dispatcher/CCTouch.h"
#include "touch_dispatcher/CCTouchDispatcher.h"

#include "CCLogOhos.h"

using namespace cocos2d;

extern "C" {
    void Cocos2dxRenderer_nativeTouchesBegin(int num, int ids[], float xs[], float ys[]);
    void Cocos2dxRenderer_nativeTouchesEnd(intptr_t id, float x, float y);
    void Cocos2dxRenderer_nativeTouchesMove(int num, int ids[], float xs[], float ys[]);
    void Cocos2dxRenderer_nativeTouchesCancel(int num, int ids[], float xs[], float ys[]);
    bool Cocos2dxRenderer_nativeKeyDown(int keyCode);
}

#endif