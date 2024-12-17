#include "CCEditBoxImplOhos.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS)

#include "CCEditBox.h"
#include "platform/ohos/napi/helper/NapiHelper.h"
#include "platform/ohos/CCLogOhos.h"
#include "CCEditBoxImpl-common.h"

NS_CC_EXT_BEGIN

static std::unordered_map<int, CCEditBoxImplOhos*> s_allEditBoxes;
static int curIndex = 0;

    CCEditBoxImpl* __createSystemEditBox(CCEditBox* editBox)
    {
        return new CCEditBoxImplOhos(editBox);
    }

    void CCEditBoxImplOhos::createNativeControl(const CCRect& frame)
    {
        OHOS_LOGD("create textinput");

        auto director = CCDirector::sharedDirector();
        auto glView = director->getOpenGLView();
        auto frameSize = glView->getFrameSize();

        auto winSize = director->getWinSize();
        auto leftBottom = m_pEditBox->convertToWorldSpace(CCPoint(0,0));

        auto contentSize = frame.size;
        auto rightTop = m_pEditBox->convertToWorldSpace(CCPoint(contentSize.width, contentSize.height));
        auto uiLeft = frameSize.width / 2 + (leftBottom.x - winSize.width / 2) * glView->getScaleX();
        auto uiTop = frameSize.height / 2 - (rightTop.y - winSize.height / 2) * glView->getScaleY();
        auto uiWidth = (rightTop.x - leftBottom.x) * glView->getScaleX();
        auto uiHeight = (rightTop.y - leftBottom.y) * glView->getScaleY();
        auto paddingW = (int)(5 * glView->getScaleX());
        auto paddingH = (int)(uiHeight * 0.33f / 2);

        s_allEditBoxes[curIndex] = this;
        _editBoxIndex = curIndex;
        JSFunction::getFunction("CocosEditBox.createCocosEditBox").invoke<void>(_editBoxIndex, uiLeft, uiTop, uiWidth, uiHeight, paddingW, paddingH);
        curIndex++;
    }

    CCEditBoxImplOhos::CCEditBoxImplOhos(CCEditBox* pEditText)
        : EditBoxImplCommon(pEditText)
        , _editBoxIndex(-1)
    {

    }

    CCEditBoxImplOhos::~CCEditBoxImplOhos()
    {
        s_allEditBoxes.erase(_editBoxIndex);
        JSFunction::getFunction("CocosEditBox.removeCocosEditBox").invoke<void>(_editBoxIndex);
    }

    void CCEditBoxImplOhos::visit(void)
    { // don't need to be implemented.
    }

    bool CCEditBoxImplOhos::isEditing()
    {
        return false;
    }

    void CCEditBoxImplOhos::setNativeText(const char* pText)
    {
        JSFunction::getFunction("CocosEditBox.setCurrentText").invoke<void>(_editBoxIndex, pText);
    }

    void CCEditBoxImplOhos::setNativeFont(const char* pFontName, int fontSize)
    {
        auto director = CCDirector::sharedDirector();
        auto glView = director->getOpenGLView();
        auto isFontFileExists = cocos2d::CCFileUtils::sharedFileUtils()->isFileExist(pFontName);
        std::string realFontPath = pFontName;
        if (isFontFileExists) {
            realFontPath = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(pFontName);
            if (realFontPath.find("rawfile/") == 0)
            {
                realFontPath = realFontPath.substr(strlen("rawfile/"));   // Chop out the 'assets/' portion of the path.
            }
        }
        auto realFontsize = fontSize * glView->getScaleX();
        JSFunction::getFunction("CocosEditBox.setEditBoxFontSize").invoke<void>(_editBoxIndex, realFontsize);
        JSFunction::getFunction("CocosEditBox.setEditBoxFontPath").invoke<void>(_editBoxIndex, realFontPath);
    }

    void CCEditBoxImplOhos::setNativeFontColor(const ccColor3B& color)
    {
        JSFunction::getFunction("CocosEditBox.setEditBoxFontColor").invoke<void>(_editBoxIndex, (int)color.r, (int)color.g, (int)color.b, 255);
    }

    void CCEditBoxImplOhos::setNativePlaceHolder(const char* pText)
    {
        JSFunction::getFunction("CocosEditBox.setEditBoxPlaceHolder").invoke<void>(_editBoxIndex, pText);
    }

    void CCEditBoxImplOhos::setNativePlaceholderFont(const char* pFontName, int fontSize)
    {
        auto director = CCDirector::sharedDirector();
        auto glView = director->getOpenGLView();
        auto isFontFileExists = cocos2d::CCFileUtils::sharedFileUtils()->isFileExist(pFontName);
        std::string realFontPath = pFontName;
        if (isFontFileExists) {
            realFontPath = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(pFontName);
            if (realFontPath.find("rawfile/") == 0)
            {
                realFontPath = realFontPath.substr(strlen("rawfile/"));   // Chop out the 'assets/' portion of the path.
            }
        }
        auto realFontsize = fontSize * glView->getScaleX();
        JSFunction::getFunction("CocosEditBox.setEditBoxPlaceHolderFontSize").invoke<void>(_editBoxIndex, realFontsize);
        JSFunction::getFunction("CocosEditBox.setEditBoxPlaceHolderFontPath").invoke<void>(_editBoxIndex, realFontPath);
    }

    void CCEditBoxImplOhos::setNativePlaceholderFontColor(const ccColor3B& color)
    {
        JSFunction::getFunction("CocosEditBox.setEditBoxPlaceHolderFontColor").invoke<void>(_editBoxIndex, (int)color.r, (int)color.g, (int)color.b, 127);
    }

    void CCEditBoxImplOhos::setNativeMaxLength(int maxLength)
    {
        JSFunction::getFunction("CocosEditBox.setEditBoxMaxLength").invoke<void>(_editBoxIndex, maxLength);
    }

    void CCEditBoxImplOhos::setNativeInputMode(EditBoxInputMode inputMode)
    {
        JSFunction::getFunction("CocosEditBox.setNativeInputMode").invoke<void>(_editBoxIndex, static_cast<int>(inputMode));
    }

    void CCEditBoxImplOhos::setNativeInputFlag(EditBoxInputFlag inputFlag)
    {
        JSFunction::getFunction("CocosEditBox.setNativeInputFlag").invoke<void>(_editBoxIndex, static_cast<int>(inputFlag));
    }

    void CCEditBoxImplOhos::setNativeReturnType(KeyboardReturnType returnType)
    {
        OHOS_LOGW("OHOS not support returnType %{public}d", returnType);
    }

    void CCEditBoxImplOhos::setNativeVisible(bool visible)
    {   
        JSFunction::getFunction("CocosEditBox.setEditBoxVisible").invoke<void>(_editBoxIndex, visible);
    }

	void CCEditBoxImplOhos::onBeginCallBack(int index)
    {
        OHOS_LOGD("textinput editBoxEditingDidBegin");
        auto it = s_allEditBoxes.find(index);
        if (it != s_allEditBoxes.end())
        {
            s_allEditBoxes[index]->editBoxEditingDidBegin();
        }
    }

    void CCEditBoxImplOhos::updateNativeFrame(const CCRect& rect)
    {
        JSFunction::getFunction("CocosEditBox.setEditBoxViewRect").invoke<void>(_editBoxIndex, (int)rect.origin.x, (int)rect.origin.y, (int)rect.size.width, (int)rect.size.height);
    }

    void CCEditBoxImplOhos::nativeOpenKeyboard()
    {
        JSFunction::getFunction("CocosEditBox.setEditBoxVisible").invoke<void>(_editBoxIndex, true);
    }

    void CCEditBoxImplOhos::nativeCloseKeyboard()
    {
        JSFunction::getFunction("CocosEditBox.setEditBoxVisible").invoke<void>(_editBoxIndex, false);
    }

    void CCEditBoxImplOhos::hideAllEditBox() {
        JSFunction::getFunction("CocosEditBox.hideAllEditBox").invoke<void>();
    }

    void CCEditBoxImplOhos::onChangeCallBack(int index, const std::string& text)
    {
        OHOS_LOGD("textinput onChangeCallBack");
        auto it = s_allEditBoxes.find(index);
        if (it != s_allEditBoxes.end())
        {
            s_allEditBoxes[index]->editBoxEditingChanged(text);
        }
    }

    void CCEditBoxImplOhos::onEnterCallBack(int index, const std::string& text)
    {
        OHOS_LOGD("textinput onEnterCallBack");
        JSFunction::getFunction("CocosEditBox.setEditBoxVisible").invoke<void>(index, false);
        auto it = s_allEditBoxes.find(index);
        if (it != s_allEditBoxes.end())
        {
            s_allEditBoxes[index]->editBoxEditingDidEnd(text);
        }
    }

    const char* CCEditBoxImplOhos::getNativeDefaultFontName()
    {
        return "sans-serif";
    }

NS_CC_EXT_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS) */

