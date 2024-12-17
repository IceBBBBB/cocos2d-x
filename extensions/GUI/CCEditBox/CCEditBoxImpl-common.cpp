/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen
 Copyright (c) 2013-2015 zilongshanren
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
#include "CCEditBoxImpl-common.h"
#include <string>
#include "CCEditBox.h"
#include "CCDirector.h"
#define kLabelZOrder  9999
static const int CC_EDIT_BOX_PADDING = 5;

static cocos2d::CCSize applyPadding(const cocos2d::CCSize& sizeToCorrect) {
    return cocos2d::CCSize(sizeToCorrect.width - CC_EDIT_BOX_PADDING * 2, sizeToCorrect.height);
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define PASSWORD_CHAR "*"
#else
#define PASSWORD_CHAR "\u25CF"
#endif

NS_CC_EXT_BEGIN

EditBoxImplCommon::EditBoxImplCommon(CCEditBox* pEditText)
: CCEditBoxImpl(pEditText)
, _label(nullptr)
, _labelPlaceHolder(nullptr)
, _editBoxInputMode(EditBoxInputMode::kEditBoxInputModeSingleLine)
, _editBoxInputFlag(EditBoxInputFlag::kEditBoxInputFlagInitialCapsAllCharacters)
, _keyboardReturnType(KeyboardReturnType::kKeyboardReturnTypeDefault)
, _colText(ccWHITE)
, _colPlaceHolder(ccGRAY)
, _maxLength(-1)
{
}

EditBoxImplCommon::~EditBoxImplCommon()
{
}


bool EditBoxImplCommon::initWithSize(const CCSize& size)
{
    do 
    {
        CCRect rect = CCRect(0, 0, size.width, size.height);

        this->createNativeControl(rect);
        initInactiveLabels(size);
        setContentSize(size);
        return true;
    }while (0);

    return false;
}

void EditBoxImplCommon::initInactiveLabels(const CCSize& size)
{
    const char* pDefaultFontName = this->getNativeDefaultFontName();

    _label = CCLabelTTF::create();
    _label->setAnchorPoint(CCPoint(0,1));
    _label->setPosition(CCPoint(CC_EDIT_BOX_PADDING, size.height / 2.0f));
    _label->setVisible(false);
    m_pEditBox->addChild(_label, kLabelZOrder);

    _labelPlaceHolder = CCLabelTTF::create();
    _labelPlaceHolder->setAnchorPoint(CCPoint(0, 1.0f));
    _labelPlaceHolder->setPosition(CCPoint(CC_EDIT_BOX_PADDING, size.height / 2.0f));
    _labelPlaceHolder->setColor(ccGRAY);
    m_pEditBox->addChild(_labelPlaceHolder, kLabelZOrder);

    setFont(pDefaultFontName, size.height*2/3);
    setPlaceholderFont(pDefaultFontName, size.height*2/3);
}

void EditBoxImplCommon::placeInactiveLabels(const CCSize& size)
{
    _label->setDimensions(size);
    auto placeholderSize = _labelPlaceHolder->getContentSize();

    if(_editBoxInputMode == EditBoxInputMode::kEditBoxInputModeAny){
        _label->setPosition(CCPoint(CC_EDIT_BOX_PADDING, size.height - CC_EDIT_BOX_PADDING));
        _labelPlaceHolder->setPosition(CCPoint(CC_EDIT_BOX_PADDING, size.height - CC_EDIT_BOX_PADDING));
    }
    else {
        _label->setPosition(CCPoint(CC_EDIT_BOX_PADDING, size.height));
        _labelPlaceHolder->setPosition(CCPoint(CC_EDIT_BOX_PADDING, (size.height + placeholderSize.height) / 2));
    }
    
    auto director = CCDirector::sharedDirector();
    auto glView = director->getOpenGLView();
    auto frameSize = glView->getFrameSize();
    auto winSize = director->getWinSize();
    auto leftBottom = m_pEditBox->convertToWorldSpace(CCPoint(0, 0));
    auto rightTop = m_pEditBox->convertToWorldSpace(CCPoint(size.width, size.height));
    
    auto uiLeft = frameSize.width / 2 + (leftBottom.x - winSize.width / 2) * glView->getScaleX();
    auto uiTop = frameSize.height / 2 - (rightTop.y - winSize.height / 2) * glView->getScaleY();
    auto uiWidth = (rightTop.x - leftBottom.x) * glView->getScaleX();
    auto uiHeight = (rightTop.y - leftBottom.y) * glView->getScaleY();
    this->updateNativeFrame(CCRect(uiLeft, uiTop, uiWidth, uiHeight));
}

void EditBoxImplCommon::setInactiveText(const char* pText)
{
    if(EditBoxInputFlag::kEditBoxInputFlagPassword == _editBoxInputFlag)
    {
        std::string passwordString;
        for(size_t i = 0, len = strlen(pText); i < len; ++i)
            passwordString.append(PASSWORD_CHAR);
        _label->setString(passwordString.c_str());
    }
    else
    {
        _label->setString(pText);
    }
    // Clip the text width to fit to the text box
    const auto maxSize = applyPadding(m_pEditBox->getContentSize());
    CCSize labelSize = _label->getContentSize();
    if(labelSize.width > maxSize.width || labelSize.height > maxSize.height)
    {
        _label->setDimensions(CCSize(maxSize.width, maxSize.height));
    }
}

void EditBoxImplCommon::setFont(const char* pFontName, int fontSize)
{
    _fontName = pFontName;
    _fontSize = fontSize;
    this->setNativeFont(pFontName, fontSize * _label->nodeToWorldTransform().a);
    if (!_fontName.empty())
    {
        _label->setFontName(pFontName);
    }
    if (fontSize > 0)
    {
        _label->setFontSize(fontSize);
    }
}

void EditBoxImplCommon::setFontColor(const ccColor3B& color)
{
    _colText = color;
    this->setNativeFontColor(color);
    _label->setColor(color);
}

void EditBoxImplCommon::setPlaceholderFont(const char* pFontName, int fontSize)
{
    _placeholderFontName = pFontName;
    _placeholderFontSize = fontSize;
    this->setNativePlaceholderFont(pFontName, fontSize * _labelPlaceHolder->nodeToWorldTransform().a);
    if (!_placeholderFontName.empty())
    {
        _labelPlaceHolder->setFontName(pFontName);
    }
    if (fontSize > 0)
    {
        _labelPlaceHolder->setFontSize(fontSize);
    }
}

void EditBoxImplCommon::setPlaceholderFontColor(const ccColor3B &color)
{
    _colPlaceHolder = color;
    this->setNativePlaceholderFontColor(color);
    _labelPlaceHolder->setColor(color);
}

void EditBoxImplCommon::setInputMode(EditBoxInputMode inputMode)
{
    _editBoxInputMode = inputMode;
    this->setNativeInputMode(inputMode);
    this->placeInactiveLabels(applyPadding(m_pEditBox->getContentSize()));
}

void EditBoxImplCommon::setMaxLength(int maxLength)
{
    _maxLength = maxLength;
    this->setNativeMaxLength(maxLength);
}

void EditBoxImplCommon::setInputFlag(EditBoxInputFlag inputFlag)
{
    _editBoxInputFlag = inputFlag;
    this->setNativeInputFlag(inputFlag);
}

void EditBoxImplCommon::setReturnType(KeyboardReturnType returnType)
{
    _keyboardReturnType = returnType;
    this->setNativeReturnType(returnType);
}

void EditBoxImplCommon::refreshInactiveText()
{
    setInactiveText(_text.c_str());
    if (!_editingMode) {
        if (_text.size() == 0) {
            _label->setVisible(false);
            _labelPlaceHolder->setVisible(true);
        } else {
            _label->setVisible(true);
            _labelPlaceHolder->setVisible(false);
        }
    }
}

void EditBoxImplCommon::setText(const char* text)
{
    if (nullptr != text) {
        this->setNativeText(text);
        _text = text;
        refreshInactiveText();
    }
}

void EditBoxImplCommon::setPlaceHolder(const char* pText)
{
    if (pText != NULL)
    {
        _placeHolder = pText;
        this->setNativePlaceHolder(pText);
        _labelPlaceHolder->setString(_placeHolder.c_str());
    }
}

void EditBoxImplCommon::setVisible(bool visible)
{
    if(visible) {
        refreshInactiveText();
    } else {
        this->setNativeVisible(visible);
        _label->setVisible(visible);
        _labelPlaceHolder->setVisible(visible);
    }
}

void EditBoxImplCommon::setContentSize(const CCSize& size)
{
    _contentSize = applyPadding(size);
    CCLOG("[Edit text] content size = (%f, %f)", _contentSize.width, _contentSize.height);
    placeInactiveLabels(_contentSize);
}

// void EditBoxImplCommon::draw(Renderer* /*renderer*/, const Mat4& /*transform*/, uint32_t flags)
// {
//     if(flags)
//     {
//         auto rect = ui::Helper::convertBoundingBoxToScreen(_editBox);
//         this->updateNativeFrame(rect);
//     }
// }

void EditBoxImplCommon::onEnter(void)
{
    const char* pText = getText();
    if (pText) {
        setInactiveText(pText);
    }
}

void EditBoxImplCommon::openKeyboard()
{
    //m_pEditBox->setBrightStyle(Widget::BrightStyle::HIGHLIGHT);
    _label->setVisible(false);
    _labelPlaceHolder->setVisible(false);
    _editingMode = true;
    this->setNativeVisible(true);
    this->nativeOpenKeyboard();
}

void EditBoxImplCommon::closeKeyboard()
{
    this->nativeCloseKeyboard();
    _editingMode = false;
}

void EditBoxImplCommon::onEndEditing(const std::string& /*text*/)
{
    //m_pEditBox->setBrightStyle(Widget::BrightStyle::NORMAL);
    _label->setVisible(false);
    _editingMode = false;
    this->setNativeVisible(false);
    refreshInactiveText();
}

void EditBoxImplCommon::editBoxEditingDidBegin()
{
    // LOGD("textFieldShouldBeginEditing...");
    cocos2d::extension::CCEditBoxDelegate *pDelegate = m_pEditBox->getDelegate();

    if (pDelegate != nullptr)
    {
        pDelegate->editBoxEditingDidBegin(m_pEditBox);
    }

#if CC_ENABLE_SCRIPT_BINDING
    if (NULL != _editBox && 0 != m_pEditBox->getScriptEditBoxHandler())
    {
        cocos2d::CommonScriptData data(m_pEditBox->getScriptEditBoxHandler(), "began", _editBox);
        cocos2d::ScriptEvent event(cocos2d::kCommonEvent, (void *)&data);
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#endif
}

void EditBoxImplCommon::editBoxEditingDidEnd(const std::string& text)
{
    // LOGD("textFieldShouldEndEditing...");
    _text = text;

    cocos2d::extension::CCEditBoxDelegate *pDelegate = m_pEditBox->getDelegate();
    if (pDelegate != nullptr)
    {
        // pDelegate->editBoxEditingDidEndWithAction(_editBox, action);
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (push)
#pragma warning (disable: 4996)
#endif
        pDelegate->editBoxEditingDidEnd(m_pEditBox);
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (pop)
#endif

        pDelegate->editBoxReturn(m_pEditBox);
    }

#if CC_ENABLE_SCRIPT_BINDING
    if (_editBox != nullptr && 0 != m_pEditBox->getScriptEditBoxHandler())
    {
        cocos2d::CommonScriptData data(m_pEditBox->getScriptEditBoxHandler(), "ended", _editBox);
        cocos2d::ScriptEvent event(cocos2d::kCommonEvent, (void *)&data);
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
        memset(data.eventName, 0, sizeof(data.eventName));
        strncpy(data.eventName, "return", sizeof(data.eventName));
        event.data = (void *)&data;
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#endif

    if (m_pEditBox != nullptr)
    {
        this->onEndEditing(_text);
    }
}

void EditBoxImplCommon::editBoxEditingChanged(const std::string& text)
{
    // LOGD("editBoxTextChanged...");
    cocos2d::extension::CCEditBoxDelegate *pDelegate = m_pEditBox->getDelegate();
    _text = text;
    if (pDelegate != nullptr)
    {
        pDelegate->editBoxTextChanged(m_pEditBox, text);
    }

#if CC_ENABLE_SCRIPT_BINDING
    if (NULL != _editBox && 0 != m_pEditBox->getScriptEditBoxHandler())
    {
        cocos2d::CommonScriptData data(m_pEditBox->getScriptEditBoxHandler(), "changed", _editBox);
        cocos2d::ScriptEvent event(cocos2d::kCommonEvent, (void *)&data);
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#endif
}


NS_CC_EXT_END


