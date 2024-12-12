#ifndef __TouchesNapi_H__
#define __TouchesNapi_H__

#include "deprecated/CCSet.h"
#include "CCDirector.h"
#include "CCTouch.h"
#include "platform/ohos/CCGLView.h"
#include "iostream"
#include "platform/ohos/CCLogOhos.h"

using namespace cocos2d;

extern "C" {
    void Cocos2dxRenderer_nativeTouchesBegin(int num, intptr_t ids[], float xs[], float ys[]);
    void Cocos2dxRenderer_nativeTouchesEnd(intptr_t id, float x, float y);
    void Cocos2dxRenderer_nativeTouchesMove(int num, intptr_t ids[], float xs[], float ys[]);
    void Cocos2dxRenderer_nativeTouchesCancel(int num, intptr_t ids[], float xs[], float ys[]);
    bool Cocos2dxRenderer_nativeKeyDown(int keyCode);
}

#endif