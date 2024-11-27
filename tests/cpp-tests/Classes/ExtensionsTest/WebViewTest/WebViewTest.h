#ifndef __TestCpp__CCWebViewTest__
#define __TestCpp__CCWebViewTest__

#include "cocos2d.h"
#include "../CocoStudioGUITest/UIScene.h"

USING_NS_CC;

class WebViewTest : public UIScene
{
public:
    WebViewTest();
    virtual ~WebViewTest();
    UI_SCENE_CREATE_FUNC(WebViewTest);
     bool onWebViewShouldStartLoading(experimental::ui::WebView *sender, const std::string &url);
    void onWebViewDidFinishLoading(experimental::ui::WebView *sender, const std::string &url);
    void onWebViewDidFailLoading(experimental::ui::WebView *sender, const std::string &url); 
    void touchEvent(Ref *pSender, TouchEventType type);
    void toExtensionsMainLayer(cocos2d::Ref *sender);
private:
    cocos2d::experimental::ui::WebView *_webView;
    
};
void runWebViewTest();
#endif /* defined(__TestCpp__CCWebViewTest__) */
