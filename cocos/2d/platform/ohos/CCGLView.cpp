#include "CCGLView.h"

#include "2d/CCDirector.h"
#include "CCEventDispatcher.h"
#include "2d/platform/CCGLViewProtocol.h"
#include "2d/CCIMEDispatcher.h"

#include "CCPlatformConfig.h"
#include "ccMacros.h"
#include "napi/helper/Js_Cocos2dxHelper.h"
#include "napi/helper/NapiHelper.h"
#include "CCGL.h"

#include <stdlib.h>
#include "CCLogOhos.h"
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

GLView::GLView() {
    initExtensions();
}

GLView::~GLView() {

}

bool GLView::initWithRect(const std::string& viewName, Rect rect, float frameZoomFactor) {
    return true;
}

bool GLView::initWithFullScreen(const std::string& viewName) {
    return true;
}

bool GLView::isOpenGLReady() {
    return (_screenSize.width != 0 && _screenSize.height != 0);
}

void GLView::end() {
    OHOS_LOGD("GLViewImpl terminateProcess");
    Js_Cocos2dxHelper::terminateProcess();
}

void GLView::swapBuffers() {
}

GLView* GLView::sharedOpenGLView() {
    static GLView instance;
    return &instance;
}

void GLView::setIMEKeyboardState(bool bOpen) {
    if (bOpen) {
        std::string pszText = cocos2d::IMEDispatcher::sharedDispatcher()->getContentText();
        JSFunction::getFunction("DiaLog.showTextInputDialog").invoke<void>(pszText);
    } else {
        JSFunction::getFunction("DiaLog.hideTextInputDialog").invoke<void>();
    }
}

GLView* GLView::createWithRect(const std::string& viewName, Rect rect, float frameZoomFactor) {
    auto ret = new GLView;
    if(ret && ret->initWithRect(viewName, rect, frameZoomFactor)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

GLView* GLView::create(const std::string& viewName) {
    auto ret = new GLView;
    if(ret && ret->initWithFullScreen(viewName)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

GLView* GLView::createWithFullScreen(const std::string& viewName) {
    auto ret = new GLView();
    if(ret && ret->initWithFullScreen(viewName)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

//default context attributions are setted as follows
GLContextAttrs GLView::_glContextAttrs = {5, 6, 5, 0, 16, 0};

void GLView::setGLContextAttrs(GLContextAttrs& glContextAttrs) {
    _glContextAttrs = glContextAttrs;
}

GLContextAttrs GLView::getGLContextAttrs() {
    return _glContextAttrs;
}

void GLView::pollEvents() {
}
NS_CC_END
