#include "napi/helper/Js_Cocos2dxHelper.h"
#include "napi/helper/NapiHelper.h"
#include "napi/render/plugin_render.h"
#include "CCApplication.h"
#include "CCDirector.h"
#include "CCLogOhos.h"
#include <cstring>

NS_CC_BEGIN

// sharedApplication pointer
CCApplication * CCApplication::sm_pSharedApplication = nullptr;

CCApplication::CCApplication()
{
    CCAssert(! sm_pSharedApplication, "");
    sm_pSharedApplication = this;
}

CCApplication::~CCApplication()
{
    CCAssert(this == sm_pSharedApplication, "");
    sm_pSharedApplication = nullptr;
}

int CCApplication::run()
{
    // Initialize instance and cocos2d.
    if (! applicationDidFinishLaunching())
    {
        return 0;
    }
    
    return -1;
}
std::string CCApplication::getVersion()
{
    return JSFunction::getFunction("ApplicationManager.getVersionName").invoke<std::string>();
}

bool CCApplication::openURL(const std::string &url)
{
    try {
        JSFunction::getFunction("JumpManager.openUrl").invoke<void>(url);
    } catch (std::exception& e) {
        return false;
    }
    return true;
}

void CCApplication::applicationScreenSizeChanged(int newWidth, int newHeight)
{
    // u can implement this method in the appdelgate
}

void CCApplication::setAnimationInterval(double interval)
{
    OHOS_LOGD("setAnimationInterval param is [%{public}lf] =========", interval);
    PluginRender::GetInstance()->changeFPS((uint64_t)(interval * 1000));  // s to ms
}

//////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////
CCApplication* CCApplication::sharedApplication()
{
    CCAssert(sm_pSharedApplication, "");
    return sm_pSharedApplication;
}

const char * CCApplication::getCurrentLanguageCode()
{
    static char code[3]={0};
    std::string systemLanguage = JSFunction::getFunction("DeviceUtils.getSystemLanguage").invoke<std::string>();
    OHOS_LOGD("==========getCurrentLanguageCode is [%{public}s] =========",systemLanguage.c_str());
    strncpy(code, systemLanguage.c_str(), 2);
    code[2]='\0';
    return code;
}

ccLanguageType CCApplication::getCurrentLanguage()
{
    const char* pLanguageName = getCurrentLanguageCode();
    ccLanguageType ret = kLanguageEnglish;

    if (0 == strcmp("zh", pLanguageName))
    {
        ret = kLanguageChinese;
    }
    else if (0 == strcmp("en", pLanguageName))
    {
        ret = kLanguageEnglish;
    }
    else if (0 == strcmp("fr", pLanguageName))
    {
        ret = kLanguageFrench;
    }
    else if (0 == strcmp("it", pLanguageName))
    {
        ret = kLanguageItalian;
    }
    else if (0 == strcmp("de", pLanguageName))
    {
        ret = kLanguageGerman;
    }
    else if (0 == strcmp("es", pLanguageName))
    {
        ret = kLanguageSpanish;
    }
    else if (0 == strcmp("nl", pLanguageName))
    {
        ret = kLanguageDutch;
    }
    else if (0 == strcmp("ru", pLanguageName))
    {
        ret = kLanguageRussian;
    }
    else if (0 == strcmp("ko", pLanguageName))
    {
        ret = kLanguageKorean;
    }
    else if (0 == strcmp("ja", pLanguageName))
    {
        ret = kLanguageJapanese;
    }
    else if (0 == strcmp("hu", pLanguageName))
    {
        ret = kLanguageHungarian;
    }
    else if (0 == strcmp("pt", pLanguageName))
    {
        ret = kLanguagePortuguese;
    }
    else if (0 == strcmp("ar", pLanguageName))
    {
        ret = kLanguageArabic;
    }
    
    return ret;
}

TargetPlatform CCApplication::getTargetPlatform() { return kTargetOhos; }

NS_CC_END
