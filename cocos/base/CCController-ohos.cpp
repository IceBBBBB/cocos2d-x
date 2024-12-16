#include "base/CCController.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS)
#include <functional>
#include "base/ccMacros.h"
#include "base/CCDirector.h"
#include "base/CCEventController.h"

NS_CC_BEGIN

class ControllerImpl
{
public:
    ControllerImpl(Controller* controller)
            : _controller(controller) {
    }

    static std::vector<Controller*>::iterator findController(const std::string& deviceName, int deviceId) {
        auto iter = std::find_if(Controller::s_allController.begin(), Controller::s_allController.end(), [&](Controller* controller){
                return (deviceName == controller->_deviceName) && (deviceId == controller->_deviceId);
            });

        return iter;
    }

    static void onConnected(const std::string& deviceName, int deviceId) {
        // Check whether the controller is already connected.
        CCLOG("onConnected %s,%d", deviceName.c_str(),deviceId);

        auto iter = findController(deviceName, deviceId);
        if (iter != Controller::s_allController.end())
            return;

        // It's a new controller being connected.
        auto controller = new cocos2d::Controller();
        controller->_deviceId = deviceId;
        controller->_deviceName = deviceName;
        Controller::s_allController.push_back(controller);

        controller->onConnected();
    }

    static void onDisconnected(const std::string& deviceName, int deviceId) {
        CCLOG("onDisconnected %s,%d", deviceName.c_str(),deviceId);

        auto iter = findController(deviceName, deviceId);
        if (iter == Controller::s_allController.end())
        {
            CCLOGERROR("Could not find the controller!");
            return;
        }

        (*iter)->onDisconnected();
        Controller::s_allController.erase(iter);
    }

    static void onButtonEvent(const std::string& deviceName, int deviceId, int keyCode, bool isPressed, float value, bool isAnalog) {
        auto iter = findController(deviceName, deviceId);
        if (iter == Controller::s_allController.end())
        {
            CCLOG("onButtonEvent:connect new controller.");
            onConnected(deviceName, deviceId);
            iter = findController(deviceName, deviceId);
        }

        (*iter)->onButtonEvent(keyCode, isPressed, value, isAnalog);
    }

    static void onAxisEvent(const std::string& deviceName, int deviceId, int axisCode, float value, bool isAnalog) {
        auto iter = findController(deviceName, deviceId);
        if (iter == Controller::s_allController.end())
        {
            CCLOG("onAxisEvent:connect new controller.");
            onConnected(deviceName, deviceId);
            iter = findController(deviceName, deviceId);
        }
        
        (*iter)->onAxisEvent(axisCode, value, isAnalog);
    }

private:
    Controller* _controller;
};

void Controller::startDiscoveryController() {
    // Empty implementation
}

void Controller::stopDiscoveryController() {
    // Empty implementation
}

Controller::~Controller() {
    delete _impl;

    delete _connectEvent;
    delete _keyEvent;
    delete _axisEvent;
}

void Controller::registerListeners() {
}

bool Controller::isConnected() const {
    // If there is a controller instance, it means that the controller is connected.
    // If a controller is disconnected, the instance will be destroyed.
    // So always returns true for this method.
    return true;
}

Controller::Controller()
    : _controllerTag(TAG_UNSET)
    , _impl(new ControllerImpl(this))
    , _connectEvent(nullptr)
    , _keyEvent(nullptr)
    , _axisEvent(nullptr) {
    init();
}

void Controller::receiveExternalKeyEvent(int externalKeyCode,bool receive) {
    // TBD need fixed
//    JniHelper::callStaticVoidMethod("org.cocos2dx.lib.GameControllerHelper", "receiveExternalKeyEvent", _deviceId, externalKeyCode, receive);
}

NS_CC_END
#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS)
