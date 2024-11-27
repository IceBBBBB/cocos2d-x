#ifndef __CCGLVIEW_H__
#define __CCGLVIEW_H__

#include "ccTypes.h"
#include "2d/platform/CCGLViewProtocol.h"
#include "CCGeometry.h"
#include "CCGLView.h"
#include "CCPlatformConfig.h"

#include <vector>

/** @struct GLContextAttrs Have six opengl Context Attrs. */
struct GLContextAttrs {
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
class CC_DLL GLView : public GLViewProtocol, public Ref {
public:
    /**
     * @js ctor
     */
    GLView();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~GLView();
    bool initWithRect(const std::string& viewName, Rect rect, float frameZoomFactor);
    bool initWithFullScreen(const std::string& viewName);	
    static GLView* create(const std::string &viewname);
    static GLView* createWithRect(const std::string& viewName, Rect rect, float frameZoomFactor = 1.0f);
    
    static GLView* createWithFullScreen(const std::string& viewName);	

    // static function
    bool isOpenGLReady() override;

    // keep compatible
    void end() override;
    void swapBuffers() override;
    void setIMEKeyboardState(bool bOpen) override;
    
    // static function
    /**
    @brief    get the shared main open gl window
    */
    static GLView* sharedOpenGLView();
    
    /** When the window is closed, it will return false if the platforms is Ios or Android.
     * If the platforms is windows or Mac,it will return true.
     *
     * @return In ios and android it will return false,if in windows or Mac it will return true.
     */
    virtual bool windowShouldClose() { return false; };

    /** Static method and member so that we can modify it on all platforms before create OpenGL context. 
     *
     * @param glContextAttrs The OpenGL context attrs.
     */
    static void setGLContextAttrs(GLContextAttrs& glContextAttrs);
    
    /** Return the OpenGL context attrs. 
     *
     * @return Return the OpenGL context attrs.
     */
    static GLContextAttrs getGLContextAttrs();
    
    /** The OpenGL context attrs. */
    static GLContextAttrs _glContextAttrs;

    /** Polls the events. */
    virtual void pollEvents();

    /** Set zoom factor for frame. This methods are for
     * debugging big resolution (e.g.new ipad) app on desktop.
     * 
     * @param zoomFactor The zoom factor for frame.
     */
    virtual void setFrameZoomFactor(float zoomFactor) {}
    
    /** Get zoom factor for frame. This methods are for
     * debugging big resolution (e.g.new ipad) app on desktop.
     *
     * @return The zoom factor for frame.
     */
    virtual float getFrameZoomFactor() const { return 1.0; }
    
    /**
     * Hide or Show the mouse cursor if there is one.
     *
     * @param isVisible Hide or Show the mouse cursor if there is one.
     */
    virtual void setCursorVisible(bool isVisible) {}

    /** Get retina factor.
     *
     * @return The retina factor.
     */
    virtual int getRetinaFactor() const { return 1; }

    /** Only works on ios platform. Set Content Scale of the Factor. */
    virtual bool setContentScaleFactor(float scaleFactor) { return false; }
    
    /** Only works on ios platform. Get Content Scale of the Factor. */
    virtual float getContentScaleFactor() const { return 1.0; }
    
    /** Returns whether or not the view is in Retina Display mode.
     *
     * @return Returns whether or not the view is in Retina Display mode.
     */
    virtual bool isRetinaDisplay() const { return false; }

};

// end of platform group
/// @}

NS_CC_END

#endif /* __CCGLVIEW_H__ */
