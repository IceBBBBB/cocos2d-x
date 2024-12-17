#ifndef __UIEDITBOXIMPLOHOS_H__
#define __UIEDITBOXIMPLOHOS_H__

#include "platform/CCPlatformConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS)

#include "UIEditBoxImpl.h"
#include <napi/native_api.h>
NS_CC_BEGIN

class Label;

namespace ui {

    class EditBox;

    class EditBoxImplOhos : public EditBoxImpl
    {
    public:
        /**
         * @js NA
         */
        EditBoxImplOhos(EditBox* pEditText);
        /**
         * @js NA
         * @lua NA
         */
        virtual ~EditBoxImplOhos();

        virtual bool initWithSize(const Size& size);
        virtual void setFont(const char* pFontName, int fontSize);
        virtual void setFontColor(const Color4B& color);
        virtual void setPlaceholderFont(const char* pFontName, int fontSize);
        virtual void setPlaceholderFontColor(const Color4B& color);
        virtual void setInputMode(EditBox::InputMode inputMode);
        virtual void setInputFlag(EditBox::InputFlag inputFlag);
        virtual void setMaxLength(int maxLength);
        virtual int  getMaxLength();
        virtual void setReturnType(EditBox::KeyboardReturnType returnType);
        virtual bool isEditing();

        virtual void setText(const char* pText);
        virtual const char* getText(void);
        virtual void setPlaceHolder(const char* pText);
        virtual void setPosition(const Vec2& pos);
        virtual void setVisible(bool visible);
        virtual void setContentSize(const Size& size);
        virtual void setAnchorPoint(const Vec2& anchorPoint);
        /**
         * @js NA
         * @lua NA
         */
        virtual void visit(void);
        /**
         * @js NA
         * @lua NA
         */
        virtual void onEnter(void);
        virtual void doAnimationWhenKeyboardMove(float duration, float distance);

        virtual void editBoxCallbackFunc(const char* text);

        virtual void openKeyboard();
        virtual void closeKeyboard();

        static void onInsertCallBack(int index, const std::string& text);
        static void onDeleteCallBack(int index);
        static void onCompleteCallBack(int index, const std::string& text);
    private:
        Label* _label;
        Label* _labelPlaceHolder;
        EditBox::InputMode    _editBoxInputMode;
        EditBox::InputFlag    _editBoxInputFlag;
        EditBox::KeyboardReturnType  _keyboardReturnType;

        std::string _text;
        std::string _placeHolder;

        Color4B _colText;
        Color4B _colPlaceHolder;

        int   _maxLength;
        Size _editSize;

        int currentIndex;
    };


}

NS_CC_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS) */

#endif /* __UIEDITBOXIMPLOHOS_H__ */

