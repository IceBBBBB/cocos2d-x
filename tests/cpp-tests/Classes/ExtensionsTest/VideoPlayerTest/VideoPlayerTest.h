
#ifndef __tests__VideoPlayerTest__
#define __tests__VideoPlayerTest__

#include "cocos2d.h"
#include "../CocoStudioGUITest/UIScene.h"


class VideoPlayerTest : public UIScene
{
public:
    VideoPlayerTest();

     ~VideoPlayerTest();

    void menuCloseCallback(cocos2d::Ref* sender);

    void menuRatioCallback(cocos2d::Ref* sender);
    void menuResourceVideoCallback(cocos2d::Ref* sender);
    void menuOnlineVideoCallback(cocos2d::Ref* sender);

    void menuFullScreenCallback(cocos2d::Ref* sender);
    void menuPauseCallback(cocos2d::Ref* sender);
    void menuResumeCallback(cocos2d::Ref* sender);
    void menuStopCallback(cocos2d::Ref* sender);
    void menuHintCallback(cocos2d::Ref* sender);
    void menuLoopCallback(cocos2d::Ref* sender);
    
    //void sliderCallback(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType eventType);

    void videoEventCallback(cocos2d::Ref* sender, cocos2d::experimental::ui::VideoPlayer::EventType eventType);

private:
    void createVideo();
    void createSlider();

    cocos2d::MenuItemFont* _hintItem;
    cocos2d::experimental::ui::VideoPlayer* _videoPlayer;
    cocos2d::Label* _videoStateLabel;
    cocos2d::Label* _loopStatusLabel;
    cocos2d::Rect _visibleRect;
   void toExtensionsMainLayer(cocos2d::Ref *sender);
    cocos2d::Layer* _rootLayer;

};
void runVideoPlayerTest();

#endif // __tests__VideoPlayerTest__
