#include "WebViewTest.h"
#include "../ExtensionsTest.h"
WebViewTest::WebViewTest()
{ 
        Size winSize = Director::getInstance()->getVisibleSize();

           auto glview = Director::getInstance()->getOpenGLView();
    auto visibleOrigin = glview->getVisibleOrigin();
    auto visibleSize = glview->getVisibleSize();
        
        _webView = cocos2d::experimental::ui::WebView::create();
        _webView->setPosition(Point(winSize/2));
        _webView->setContentSize(winSize * 0.5);
        _webView->loadURL("http://www.baidu.com");
        _webView->setScalesPageToFit(true);
        
        _webView->setOnShouldStartLoading(CC_CALLBACK_2(WebViewTest::onWebViewShouldStartLoading, this));
        _webView->setOnDidFinishLoading(CC_CALLBACK_2(WebViewTest::onWebViewDidFinishLoading, this));
        _webView->setOnDidFailLoading(CC_CALLBACK_2(WebViewTest::onWebViewDidFailLoading, this));
        
        this->addChild(_webView);
    
        auto spriteHello = Sprite::create("Hello.png");
        spriteHello->setContentSize(winSize * 0.5);
        spriteHello->setPosition(Point(winSize/2));
        this->addChild(spriteHello);
    
        Button *resetBtn = Button::create("cocosui/animationbuttonnormal.png",
                                       "cocosui/animationbuttonpressed.png");
        resetBtn->setTitleText("Visit URL");
        resetBtn->setPosition(Point(winSize/2) + Point(50, _webView->getContentSize().height/2 +
                                            resetBtn->getContentSize().height/2 + 10));
        resetBtn->addTouchEventListener(this, toucheventselector(WebViewTest::touchEvent));
        this->addChild(resetBtn);

         // Back Menu
    auto itemBack = MenuItemFont::create("Back", CC_CALLBACK_1(WebViewTest::toExtensionsMainLayer, this));
    itemBack->setPosition(Point(visibleOrigin.x+visibleSize.width - 50, visibleOrigin.y+25));
    auto menuBack = Menu::create(itemBack, NULL);
    menuBack->setPosition(Point::ZERO);
    addChild(menuBack);
} 

void WebViewTest::toExtensionsMainLayer(cocos2d::Ref *sender)
{
    auto scene = new ExtensionsTestScene();
    scene->runThisTest();
    scene->release();
}
WebViewTest::~WebViewTest()
{
    
}
void WebViewTest::touchEvent(Ref *pSender, TouchEventType type){
     _webView->loadURL(std::string("http://baidu.com") );
}


bool WebViewTest::onWebViewShouldStartLoading(experimental::ui::WebView *sender, const std::string &url)
{
    CCLOG("onWebViewShouldStartLoading, url is %s", url.c_str());
    //don't do any OpenGL operation here!! It's forbidden!
    return true;
}

void WebViewTest::onWebViewDidFinishLoading(experimental::ui::WebView *sender, const std::string &url)
{
    CCLOG("onWebViewDidFinishLoading, url is %s", url.c_str());
}

void WebViewTest::onWebViewDidFailLoading(experimental::ui::WebView *sender, const std::string &url)
{
    CCLOG("onWebViewDidFailLoading, url is %s", url.c_str());
}



void runWebViewTest()
{
    auto scene = Scene::create();
    WebViewTest *layer = new WebViewTest();
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    layer->release();
}

