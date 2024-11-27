
#include "VideoPlayerTest.h"
#include "../ExtensionsTest.h"
USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocos2d::experimental::ui;


VideoPlayerTest::VideoPlayerTest(){
    _visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
    auto glview = Director::getInstance()->getOpenGLView();
    auto visibleOrigin = glview->getVisibleOrigin();
    auto visibleSize = glview->getVisibleSize();

    MenuItemFont::setFontSize(16);

    auto fullSwitch = MenuItemFont::create("FullScreenSwitch", CC_CALLBACK_1(VideoPlayerTest::menuFullScreenCallback, this));
    fullSwitch->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    fullSwitch->setPosition(Point(_visibleRect.origin.x + 10,_visibleRect.origin.y + 150));

    auto pauseItem = MenuItemFont::create("Pause", CC_CALLBACK_1(VideoPlayerTest::menuPauseCallback, this));
    pauseItem->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    pauseItem->setPosition(Point(_visibleRect.origin.x + 10,_visibleRect.origin.y + 200));

    auto resumeItem = MenuItemFont::create("Resume", CC_CALLBACK_1(VideoPlayerTest::menuResumeCallback, this));
    resumeItem->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    resumeItem->setPosition(Point(_visibleRect.origin.x + 10,_visibleRect.origin.y + 250));

    auto stopItem = MenuItemFont::create("Stop", CC_CALLBACK_1(VideoPlayerTest::menuStopCallback, this));
    stopItem->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    stopItem->setPosition(Point(_visibleRect.origin.x + 10,_visibleRect.origin.y + 300));

    auto hintItem = MenuItemFont::create("Hint", CC_CALLBACK_1(VideoPlayerTest::menuHintCallback, this));
    hintItem->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    hintItem->setPosition(Point(_visibleRect.origin.x + 10,_visibleRect.origin.y + 350));

    //-------------------------------------------------------------------------------------------------------------------
    auto resourceVideo = MenuItemFont::create("Play resource video", CC_CALLBACK_1(VideoPlayerTest::menuResourceVideoCallback, this));
    resourceVideo->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    resourceVideo->setPosition(Point(_visibleRect.origin.x + _visibleRect.size.width - 10,_visibleRect.origin.y + 150));

    auto onlineVideo = MenuItemFont::create("Play online video", CC_CALLBACK_1(VideoPlayerTest::menuOnlineVideoCallback, this));
    onlineVideo->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    onlineVideo->setPosition(Point(_visibleRect.origin.x + _visibleRect.size.width - 10,_visibleRect.origin.y + 200));

    auto ratioSwitch = MenuItemFont::create("KeepRatioSwitch", CC_CALLBACK_1(VideoPlayerTest::menuRatioCallback, this));
    ratioSwitch->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    ratioSwitch->setPosition(Point(_visibleRect.origin.x + _visibleRect.size.width - 10,_visibleRect.origin.y + 250));
    
    auto loopToggle = MenuItemFont::create("LoopToogle", CC_CALLBACK_1(VideoPlayerTest::menuLoopCallback, this));
    loopToggle->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    loopToggle->setPosition(Point(_visibleRect.origin.x + _visibleRect.size.width - 10,_visibleRect.origin.y + 270));

    auto menu = Menu::create(resourceVideo,onlineVideo,ratioSwitch,loopToggle,fullSwitch,pauseItem,resumeItem,stopItem,hintItem,nullptr);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);

    _videoStateLabel = Label::createWithSystemFont("IDLE","Arial",16);
    _videoStateLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    _videoStateLabel->setPosition(Point(_visibleRect.origin.x + _visibleRect.size.width - 10,_visibleRect.origin.y + 300));
    this->addChild(_videoStateLabel);
    
    _loopStatusLabel = Label::createWithSystemFont("(1)","Arial",10);
    _loopStatusLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    _loopStatusLabel->setPosition(Point(_visibleRect.origin.x + _visibleRect.size.width - 10,_visibleRect.origin.y + 185));
   this->addChild(_loopStatusLabel);
    
    createVideo();

             // Back Menu
    auto itemBack = MenuItemFont::create("Back", CC_CALLBACK_1(VideoPlayerTest::toExtensionsMainLayer, this));
    itemBack->setPosition(Point(visibleOrigin.x+visibleSize.width - 50, visibleOrigin.y+25));
    auto menuBack = Menu::create(itemBack, NULL);
    menuBack->setPosition(Point::ZERO);
    addChild(menuBack);

}

void VideoPlayerTest::toExtensionsMainLayer(cocos2d::Ref *sender)
{
    auto scene = new ExtensionsTestScene();
    scene->runThisTest();
    scene->release();
}
 VideoPlayerTest::~VideoPlayerTest(){
    
    _videoPlayer->release();
 }
void VideoPlayerTest::menuCloseCallback(Ref* sender)
{
    Director::getInstance()->end();
}

void VideoPlayerTest::menuFullScreenCallback(Ref* sender)
{
    if (_videoPlayer)
    {
        _videoPlayer->setFullScreenEnabled(! _videoPlayer->isFullScreenEnabled());
    }
}

void VideoPlayerTest::menuRatioCallback(Ref* sender)
{
    if (_videoPlayer)
    {
        _videoPlayer->setKeepAspectRatioEnabled(! _videoPlayer->isKeepAspectRatioEnabled());
    }
}

void VideoPlayerTest::menuLoopCallback(Ref* sender)
{
    if (_videoPlayer)
    {
        _videoPlayer->setLooping(! _videoPlayer->isLooping());
        _loopStatusLabel->setString(_videoPlayer->isLooping() ? "(OO)" : "(1)");
    }
}


void VideoPlayerTest::menuResourceVideoCallback(Ref* sender)
{
    if (_videoPlayer)
    {
        _videoPlayer->setFileName("cocosvideo.mp4");
        _videoPlayer->play();
    }
}

void VideoPlayerTest::menuOnlineVideoCallback(Ref* sender)
{
    if (_videoPlayer)
    {
        _videoPlayer->setURL("http://benchmark.cocos2d-x.org/cocosvideo.mp4");
        _videoPlayer->play();
    }
}

void VideoPlayerTest::menuPauseCallback(Ref* sender)
{
    if (_videoPlayer)
    {
        _videoPlayer->pause();
    }
}

void VideoPlayerTest::menuResumeCallback(Ref* sender)
{
    if (_videoPlayer)
    {
        _videoPlayer->resume();
    }
}

void VideoPlayerTest::menuStopCallback(Ref* sender)
{
    if (_videoPlayer)
    {
        _videoPlayer->stop();
    }
}

void VideoPlayerTest::menuHintCallback(Ref* sender)
{
    if (_videoPlayer)
    {
        _videoPlayer->setVisible(! _videoPlayer->isVisible());
    }
}

void VideoPlayerTest::createVideo()
{
    auto widgetSize =  Director::getInstance()->getVisibleSize();
 auto centerPos = Point(_visibleRect.origin.x + _visibleRect.size.width / 2,_visibleRect.origin.y + _visibleRect.size.height /2);
    

    _videoPlayer = VideoPlayer::create();
    _videoPlayer->setPosition(centerPos);
    _videoPlayer->setAnchorPoint(Point::ANCHOR_MIDDLE);
    _videoPlayer->setContentSize(Size(widgetSize.width * 0.4f,widgetSize.height * 0.4f));
    this->addChild(_videoPlayer);
    
    _videoPlayer->addEventListener(CC_CALLBACK_2(VideoPlayerTest::videoEventCallback, this));
}

void VideoPlayerTest::videoEventCallback(Ref* sender, VideoPlayer::EventType eventType)
{
    switch (eventType) {
        case VideoPlayer::EventType::PLAYING:
            _videoStateLabel->setString("PLAYING");
            break;
        case VideoPlayer::EventType::PAUSED:
            _videoStateLabel->setString("PAUSED");
            break;
        case VideoPlayer::EventType::STOPPED:
            _videoStateLabel->setString("STOPPED");
            break;
        case VideoPlayer::EventType::COMPLETED:
            _videoStateLabel->setString("COMPLETED");
            break;
        default:
            break;
    }
}
void runVideoPlayerTest()
{
    auto scene = Scene::create();
    VideoPlayerTest *layer = new VideoPlayerTest();
    scene->addChild(layer);
    
    Director::getInstance()->replaceScene(scene);
    layer->release();
}