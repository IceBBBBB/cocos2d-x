#ifndef __CCEDITBOXIMPLOHOS_H__
#define __CCEDITBOXIMPLOHOS_H__

#include "cocos2dx/include/cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS)
#include "ExtensionMacros.h"
#include "CCEditBoxImpl-common.h"

NS_CC_EXT_BEGIN

class CCEditBox;

class CCEditBoxImplOhos : public EditBoxImplCommon {
public:
    CCEditBoxImplOhos(CCEditBox* pEditText);
    virtual ~CCEditBoxImplOhos();
    /**
    * @js NA
    * @lua NA
    */
    virtual void visit(void);
    virtual bool isEditing() override;
    virtual void createNativeControl(const CCRect& frame) override;
    virtual void setNativeFont(const char* pFontName, int fontSize);
    virtual void setNativeFontColor(const ccColor3B& color);
    virtual void setNativePlaceholderFont(const char* pFontName, int fontSize);
    virtual void setNativePlaceholderFontColor(const ccColor3B& color);
    virtual void setNativeInputMode(EditBoxInputMode inputMode);
    virtual void setNativeInputFlag(EditBoxInputFlag inputFlag);
    virtual void setNativeReturnType(KeyboardReturnType returnType);
    virtual void setNativeText(const char* pText);
    virtual void setNativePlaceHolder(const char* pText);
    virtual void setNativeVisible(bool visible);
    virtual void updateNativeFrame(const CCRect& rect);
    virtual const char* getNativeDefaultFontName() override ;
    virtual void nativeOpenKeyboard() override ;
    virtual void nativeCloseKeyboard() override ;
    virtual void setNativeMaxLength(int maxLength) override;

    static void hideAllEditBox();
    static void onBeginCallBack(int index);
    static void onChangeCallBack(int index, const std::string& text);
    static void onEnterCallBack(int index, const std::string& text);

private:
    virtual void doAnimationWhenKeyboardMove(float duration, float distance)override {};
    int _editBoxIndex;
};

NS_CC_EXT_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS) */

#endif /* __CCEDITBOXIMPLOHOS_H__ */
