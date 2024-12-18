/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#include "CCAccelerometer.h"
#include "napi/helper/Js_Cocos2dxHelper.h"

#define TG3_GRAVITY_EARTH                    (9.80665f)

namespace cocos2d
{
    CCAccelerometer::CCAccelerometer() : m_pAccelDelegate(NULL)
    {
    }

    CCAccelerometer::~CCAccelerometer() 
    {

    }

    void CCAccelerometer::setDelegate(CCAccelerometerDelegate* pDelegate) {
        m_pAccelDelegate = pDelegate;

        if (pDelegate) {        
            Js_Cocos2dxHelper::enableAccelerometer();
        }
        else {
            Js_Cocos2dxHelper::disableAccelerometer();
        }
    }

    void CCAccelerometer::setAccelerometerInterval(float interval) {
        Js_Cocos2dxHelper::setAccelerometerInterval(interval);
    }

    void CCAccelerometer::update(float x, float y, float z, long sensorTimeStamp) {
        if (m_pAccelDelegate) {
            m_obAccelerationValue.x = -((double)x / TG3_GRAVITY_EARTH);
            m_obAccelerationValue.y = -((double)y / TG3_GRAVITY_EARTH);
            m_obAccelerationValue.z = -((double)z / TG3_GRAVITY_EARTH);
            m_obAccelerationValue.timestamp = (double)sensorTimeStamp;

            m_pAccelDelegate->didAccelerate(&m_obAccelerationValue);
        }    
    }
}

