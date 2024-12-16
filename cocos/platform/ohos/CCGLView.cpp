/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "CCGLView.h"

#include "base/CCDirector.h"
#include "base/ccMacros.h"
#include "base/CCIMEDispatcher.h"
#include "platform/CCGLViewProtocol.h"
#include "napi/helper/Js_Cocos2dxHelper.h"
#include "CCGL.h"

#include <stdlib.h>
#include "CCLogOhos.h"
#include "napi/helper/NapiHelper.h"

#include <EGL/egl.h>
PFNGLGENVERTEXARRAYSOESPROC glGenVertexArraysOESEXT = 0;
PFNGLBINDVERTEXARRAYOESPROC glBindVertexArrayOESEXT = 0;
PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArraysOESEXT = 0;

void initExtensions() {
     glGenVertexArraysOESEXT = (PFNGLGENVERTEXARRAYSOESPROC)eglGetProcAddress("glGenVertexArraysOES");
     glBindVertexArrayOESEXT = (PFNGLBINDVERTEXARRAYOESPROC)eglGetProcAddress("glBindVertexArrayOES");
     glDeleteVertexArraysOESEXT = (PFNGLDELETEVERTEXARRAYSOESPROC)eglGetProcAddress("glDeleteVertexArraysOES");
}

NS_CC_BEGIN

GLView::GLView()
{
    initExtensions();
}

GLView::~GLView()
{

}

bool GLView::initWithRect(const std::string& viewName, Rect rect, float frameZoomFactor)
{
    return true;
}

bool GLView::initWithFullScreen(const std::string& viewName)
{
    return true;
}

bool GLView::isOpenGLReady()
{
    return (_screenSize.width != 0 && _screenSize.height != 0);
}

void GLView::end()
{
    OHOS_LOGD("GLView terminateProcess");
    Js_Cocos2dxHelper::terminateProcess();
}

void GLView::swapBuffers()
{
}

GLView* GLView::sharedOpenGLView()
{
    static GLView instance;
    return &instance;
}

void GLView::setIMEKeyboardState(bool bOpen)
{
    if (bOpen) {
        std::string pszText = IMEDispatcher::sharedDispatcher()->getContentText();
        JSFunction::getFunction("DiaLog.showTextInputDialog").invoke<void>(pszText);
    } else {
        JSFunction::getFunction("DiaLog.hideTextInputDialog").invoke<void>();
    }
}

GLView* GLView::createWithRect(const std::string& viewName, Rect rect, float frameZoomFactor)
{
    auto ret = new GLView;
    if(ret && ret->initWithRect(viewName, rect, frameZoomFactor)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

GLView* GLView::create(const std::string& viewName)
{
    auto ret = new GLView;
    if(ret && ret->initWithFullScreen(viewName)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

GLView* GLView::createWithFullScreen(const std::string& viewName)
{
    auto ret = new GLView();
    if(ret && ret->initWithFullScreen(viewName)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}


NS_CC_END
