#include "CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_OHOS
#include "napi/helper/Js_Cocos2dxHelper.h"
#include "platform/CCDevice.h"
#include "ccTypes.h"
#include "CCTextBitmap.h"
#include "napi/helper/NapiHelper.h"

NS_CC_BEGIN

int Device::getDPI() {
    return JSFunction::getFunction("DeviceUtils.getDpi").invoke<int>();
}

void Device::setAccelerometerEnabled(bool isEnabled) {
    if (isEnabled) {
        Js_Cocos2dxHelper::enableAccelerometer();
    }
    else {
        Js_Cocos2dxHelper::disableAccelerometer();
    }
}

void Device::setAccelerometerInterval(float interval) {
    Js_Cocos2dxHelper::setAccelerometerInterval(interval);
}

class BitmapDC {
public:

    BitmapDC()
    : m_nWidth(0)
    , m_nHeight(0)
    , m_pData(NULL) {
    }

    ~BitmapDC(void) {
        if (m_pData) {
            delete [] m_pData;
        }
    }
   
    bool getBitmapWithDrawing(	const char *text, int nWidth, int nHeight, Device::TextAlign eAlignMask, const FontDefinition& textDefinition) {
        CCTextBitmap *cCtextBitmap = CCTextBitmap::createCCTextBitmap(text, textDefinition._fontName.data(),255,textDefinition._fontFillColor.r,
        textDefinition._fontFillColor.g,textDefinition._fontFillColor.b,eAlignMask, nWidth,nHeight, textDefinition._fontSize);
        void* pixels = cCtextBitmap->getPixelAddr();
        cocos2d::BitmapDC& bitmapDC = sharedBitmapDC();
        bitmapDC.m_nWidth = cCtextBitmap->GetWidth();
        bitmapDC.m_nHeight = cCtextBitmap->GetHeight();
        bitmapDC.m_pData = (unsigned char*)pixels; 
        return true;
    }

public:
    int m_nWidth;
    int m_nHeight;
    unsigned char *m_pData;

    static BitmapDC& sharedBitmapDC() {
        // TBD not safe for multi threads
        static BitmapDC s_BmpDC;
        return s_BmpDC;
    }
};

Data Device::getTextureDataForText(const char * text, const FontDefinition& textDefinition, TextAlign align, int &width, int &height) {
    Data ret;
    do {
        BitmapDC &dc = BitmapDC::sharedBitmapDC();

        if(!dc.getBitmapWithDrawing(text,  (int)textDefinition._dimensions.width,  (int)textDefinition._dimensions.height,  align, textDefinition )) { 
            break;
        };

        width = dc.m_nWidth;
        height = dc.m_nHeight;
        ret.fastSet(dc.m_pData,width * height * 4);
    } while (0);

    return ret;
}	


NS_CC_END
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_OHOS
