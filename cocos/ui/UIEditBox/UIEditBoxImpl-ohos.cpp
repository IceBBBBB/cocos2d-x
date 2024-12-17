#include "UIEditBoxImpl-ohos.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS)

#include "UIEditBox.h"

#include "2d/CCLabel.h"
#include "base/ccUTF8.h"
#include "platform/ohos/napi/helper/NapiHelper.h"
#include <algorithm>
NS_CC_BEGIN

namespace ui {
    static std::unordered_map<int, EditBoxImplOhos*> s_allEditBoxes;
    static int index;

    EditBoxImpl* __createSystemEditBox(EditBox* pEditBox)
    {
        return new EditBoxImplOhos(pEditBox);
    }

    EditBoxImplOhos::EditBoxImplOhos(EditBox* pEditText)
            : EditBoxImpl(pEditText)
            , _label(nullptr)
            , _labelPlaceHolder(nullptr)
            , _editBoxInputMode(EditBox::InputMode::SINGLE_LINE)
            , _editBoxInputFlag(EditBox::InputFlag::INTIAL_CAPS_ALL_CHARACTERS)
            , _keyboardReturnType(EditBox::KeyboardReturnType::DEFAULT)
            , _colText(Color3B::WHITE)
            , _colPlaceHolder(Color3B::GRAY)
            , _maxLength(-1)
    {

    }

    EditBoxImplOhos::~EditBoxImplOhos()
    {

    }

    void EditBoxImplOhos::doAnimationWhenKeyboardMove(float duration, float distance)
    { // don't need to be implemented on android platform.

    }

    static const int CC_EDIT_BOX_PADDING = 5;

    bool EditBoxImplOhos::initWithSize(const Size& size)
    {
        //int fontSize = getFontSizeAccordingHeightJni(size.height-12);
        _label = Label::create();
        _label->setSystemFontSize(size.height-12);
        // align the text vertically center
        _label->setAnchorPoint(Vec2(0, 0.5f));
        _label->setPosition(Vec2(CC_EDIT_BOX_PADDING, size.height / 2.0f));
        _label->setTextColor(_colText);
        _editBox->addChild(_label);

        _labelPlaceHolder = Label::create();
        _labelPlaceHolder->setSystemFontSize(size.height-12);
        // align the text vertically center
        _labelPlaceHolder->setAnchorPoint(Vec2(0, 0.5f));
        _labelPlaceHolder->setPosition(CC_EDIT_BOX_PADDING, size.height / 2.0f);
        _labelPlaceHolder->setVisible(false);
        _labelPlaceHolder->setTextColor(_colPlaceHolder);
        _editBox->addChild(_labelPlaceHolder);

        _editSize = size;

        s_allEditBoxes[index] = this;
        this->currentIndex = index;
        index++;
        return true;
    }

    void EditBoxImplOhos::setFont(const char* pFontName, int fontSize)
    {
        if(_label != NULL) {
            _label->setSystemFontName(pFontName);
            _label->setSystemFontSize(fontSize);
        }

        if(_labelPlaceHolder != NULL) {
            _labelPlaceHolder->setSystemFontName(pFontName);
            _labelPlaceHolder->setSystemFontSize(fontSize);
        }
    }

    void EditBoxImplOhos::setFontColor(const Color4B& color)
    {
        _colText = color;
        _label->setTextColor(color);
    }

    void EditBoxImplOhos::setPlaceholderFont(const char* pFontName, int fontSize)
    {
        if(_labelPlaceHolder != NULL) {
            _labelPlaceHolder->setSystemFontName(pFontName);
            _labelPlaceHolder->setSystemFontSize(fontSize);
        }
    }

    void EditBoxImplOhos::setPlaceholderFontColor(const Color4B& color)
    {
        _colPlaceHolder = color;
        _labelPlaceHolder->setTextColor(color);
    }

    void EditBoxImplOhos::setInputMode(EditBox::InputMode inputMode)
    {
        _editBoxInputMode = inputMode;
    }

    void EditBoxImplOhos::setMaxLength(int maxLength)
    {
        _maxLength = maxLength;
    }

    int EditBoxImplOhos::getMaxLength()
    {
        return _maxLength;
    }

    void EditBoxImplOhos::setInputFlag(EditBox::InputFlag inputFlag)
    {
        _editBoxInputFlag = inputFlag;
    }

    void EditBoxImplOhos::setReturnType(EditBox::KeyboardReturnType returnType)
    {
        _keyboardReturnType = returnType;
    }

    bool EditBoxImplOhos::isEditing()
    {
        return false;
    }

    void EditBoxImplOhos::setText(const char* pText)
    {
        if (pText != NULL)
        {
            _text = pText;

            if (_text.length() > 0)
            {
                _labelPlaceHolder->setVisible(false);

                std::string strToShow;

                if (EditBox::InputFlag::PASSWORD == _editBoxInputFlag)
                {
                    long length = cc_utf8_strlen(_text.c_str(), -1);
                    for (long i = 0; i < length; i++)
                    {
                        strToShow.append("*");
                    }
                }
                else
                {
                    strToShow = _text;
                }

                _label->setString(strToShow.c_str());

                // Clip the text width to fit to the text box

                float fMaxWidth = _editSize.width - CC_EDIT_BOX_PADDING * 2;
                auto labelSize = _label->getContentSize();
                if(labelSize.width > fMaxWidth) {
                    _label->setDimensions(fMaxWidth,labelSize.height);
                }
            }
            else
            {
                _labelPlaceHolder->setVisible(true);
                _label->setString("");
            }

        }
    }

    const char*  EditBoxImplOhos::getText(void)
    {
        return _text.c_str();
    }

    void EditBoxImplOhos::setPlaceHolder(const char* pText)
    {
        if (pText != NULL)
        {
            _placeHolder = pText;
            if (_placeHolder.length() > 0 && _text.length() == 0)
            {
                _labelPlaceHolder->setVisible(true);
            }

            _labelPlaceHolder->setString(_placeHolder.c_str());
        }
    }

    void EditBoxImplOhos::setPosition(const Vec2& pos)
    { // don't need to be implemented on android platform.

    }

    void EditBoxImplOhos::setVisible(bool visible)
    { // don't need to be implemented on android platform.

    }

    void EditBoxImplOhos::setContentSize(const Size& size)
    { // don't need to be implemented on android platform.

    }

    void EditBoxImplOhos::setAnchorPoint(const Vec2& anchorPoint)
    { // don't need to be implemented on android platform.

    }

    void EditBoxImplOhos::visit(void)
    { // don't need to be implemented on android platform.

    }

    void EditBoxImplOhos::onEnter(void)
    { // don't need to be implemented on android platform.

    }

    void EditBoxImplOhos::editBoxCallbackFunc(const char* text)
    {
        setText(text);

        if (getDelegate() != NULL)
        {
            getDelegate()->editBoxTextChanged(getEditBox(), getText());
            getDelegate()->editBoxEditingDidEnd(getEditBox());
            getDelegate()->editBoxReturn(getEditBox());
        }

#if CC_ENABLE_SCRIPT_BINDING
        EditBox* pEditBox = getEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        CommonScriptData data(pEditBox->getScriptEditBoxHandler(), "changed",pEditBox);
        ScriptEvent event(kCommonEvent,(void*)&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
        memset(data.eventName, 0, sizeof(data.eventName));
        strncpy(data.eventName, "ended", sizeof(data.eventName));
        event.data = (void*)&data;
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
        memset(data.eventName, 0, sizeof(data.eventName));
        strncpy(data.eventName, "return", sizeof(data.eventName));
        event.data = (void*)&data;
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#endif
    }

    void EditBoxImplOhos::openKeyboard()
    {
        if (_delegate != NULL)
        {
            _delegate->editBoxEditingDidBegin(_editBox);
        }

#if CC_ENABLE_SCRIPT_BINDING
        EditBox* pEditBox = this->getEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        CommonScriptData data(pEditBox->getScriptEditBoxHandler(), "began",pEditBox);
        ScriptEvent event(cocos2d::kCommonEvent,(void*)&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#endif
        JSFunction::getFunction("CocosEditBox.setEditBoxVisible").invoke<void>(currentIndex, true);
    }

    void EditBoxImplOhos::closeKeyboard()
    {        
	
		JSFunction::getFunction("CocosEditBox.setEditBoxVisible").invoke<void>(currentIndex, false);

    }

    void EditBoxImplOhos::onInsertCallBack(int index, const std::string& text)
    {
        OHOS_LOGE("textinput onInsertCallBack");
        auto it = s_allEditBoxes.find(index);
        if (it != s_allEditBoxes.end())
        {
            std::string temp;
            temp = s_allEditBoxes[index]->getText();
            temp += text;
            s_allEditBoxes[index]->editBoxCallbackFunc(temp.c_str());
        }
    }

    void EditBoxImplOhos::onDeleteCallBack(int index)
    {
        OHOS_LOGE("textinput onDeleteCallBack");
        auto it = s_allEditBoxes.find(index);
        if (it != s_allEditBoxes.end())
        {
            std::string temp;
            temp = s_allEditBoxes[index]->getText();
            temp = temp.substr(0,std::fmax(temp.size()-1,0));
            s_allEditBoxes[index]->editBoxCallbackFunc(temp.c_str());
        }
    }
    
    void EditBoxImplOhos::onCompleteCallBack(int index, const std::string& text)
    {
        OHOS_LOGE("textinput onCompleteCallBack");
        auto it = s_allEditBoxes.find(index);
        if (it != s_allEditBoxes.end())
        {
            s_allEditBoxes[index]->editBoxCallbackFunc(text.c_str());
        }
    }
}

NS_CC_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS) */

