#include "platform/CCDevice.h"
#include "napi/helper/NapiHelper.h"

NS_CC_BEGIN

int CCDevice::getDPI()
{
    return JSFunction::getFunction("DeviceUtils.getDpi").invoke<int>();
}

NS_CC_END
