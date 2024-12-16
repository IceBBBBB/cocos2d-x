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

#ifndef __CC_EGLVIEWIMPL_OHOS_H__
#define __CC_EGLVIEWIMPL_OHOS_H__

#include "base/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_OHOS
#include "platform/CCGLViewProtocol.h"
#include "math/CCGeometry.h"
#include "CCGLView.h"

/** @struct GLContextAttrs Have six opengl Context Attrs. */
struct GLContextAttrs
{
    int redBits;
    int greenBits;
    int blueBits;
    int alphaBits;
    int depthBits;
    int stencilBits;
};

NS_CC_BEGIN

/**
 * @addtogroup platform
 * @{
 */
/**
 * @brief By GLView you can operate the frame information of EGL view through some function.
 */
class CC_DLL GLView : public GLViewProtocol, public Ref
{
public:	
    static GLView* create(const std::string &viewname);
    static GLView* createWithRect(const std::string& viewName, Rect rect, float frameZoomFactor = 1.0f);
    static GLView* createWithFullScreen(const std::string& viewName);	

    bool isOpenGLReady() override;
    void end() override;
    void swapBuffers() override;
    void setIMEKeyboardState(bool bOpen) override;
    
    static GLView* sharedOpenGLView();
    
protected:
    GLView();
    virtual ~GLView();

    bool initWithRect(const std::string& viewName, Rect rect, float frameZoomFactor);
    bool initWithFullScreen(const std::string& viewName);

};
NS_CC_END

#endif /* __CCGLVIEW_H__ */
#endif __CC_EGLVIEWIMPL_OHOS_H__