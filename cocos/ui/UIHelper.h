/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef __UIHELPER_H__
#define __UIHELPER_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS)
#include <string>
#include "CCSprite.h"
#include "base/CCPlatformMacros.h"
#include "ui/GUIExport.h"
#endif

NS_CC_BEGIN

namespace ui {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS)
    class Widget;
#endif

/**
*   @js NA
*   @lua NA
*/
class Helper
{
public:
    /**
     * Finds a widget whose tag equals to param tag from root widget.
     *
     * @param root      widget which will be seeked.
     *
     * @tag             tag value.
     *
     * @return finded result.
     */
    static Widget* seekWidgetByTag(Widget* root, int tag);
    
    /**
     * Finds a widget whose name equals to param name from root widget.
     *
     * @param root      widget which will be seeked.
     *
     * @name             name value.
     *
     * @return finded result.
     */
    static Widget* seekWidgetByName(Widget* root, const char* name);
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS)
    /**
     *@brief Convert a node's boundingBox rect into screen coordinates.
     *
     * @param node Any node pointer.
     *
     * @return A Rect in screen coordinates.
     */
    static Rect convertBoundingBoxToScreen(Node* node);
    
#endif
    /*temp action*/
    static Widget* seekActionWidgetByActionTag(Widget* root, int tag);
};
}

NS_CC_END

#endif /* defined(__CocoGUI__UISystem__) */
