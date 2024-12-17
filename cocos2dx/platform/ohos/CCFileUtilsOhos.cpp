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
#include "CCFileUtilsOhos.h"
#include "platform/CCCommon.h"
#include "RawFileUtils.h"

using namespace std;

NS_CC_BEGIN

string CCFileUtilsOhos::ohWritablePath;

CCFileUtils* CCFileUtils::sharedFileUtils() {

    if (s_sharedFileUtils == NULL) {
        s_sharedFileUtils = new CCFileUtilsOhos();
        s_sharedFileUtils->init();
    }
    return s_sharedFileUtils;
}

CCFileUtilsOhos::CCFileUtilsOhos() { }

CCFileUtilsOhos::~CCFileUtilsOhos() { }

bool CCFileUtilsOhos::init() {
    m_strDefaultResRootPath = "";
    return CCFileUtils::init();
}

bool CCFileUtilsOhos::isFileExist(const std::string& strFilePath) {
    if (0 == strFilePath.length()) {
        return false;
    }

    bool bFound = false;
    if (strFilePath[0] != '/') {
        RawFile* fp = RawFileUtils::GetInstance().Open(strFilePath.c_str());
        CCLOG("===================> open %s", strFilePath.c_str());
            if (fp) {
            bFound = true;
            RawFileUtils::GetInstance().Close(fp);
        }
    } else {
        FILE *fp = fopen(strFilePath.c_str(), "r");
        if(fp)
        {
            bFound = true;
            fclose(fp);
        }
    }
    
    return bFound;
}

bool CCFileUtilsOhos::isAbsolutePath(const std::string& dirPath) {
    if (dirPath[0] == '/' || (!m_strDefaultResRootPath.empty() && dirPath.find(m_strDefaultResRootPath) == 0)) {
        return true;
    }
    return false;
}

bool CCFileUtilsOhos::getRawFileDescriptor(const std::string &filename, RawFileDescriptor &descriptor) {
    if (filename.empty()) {
        return false;
    }
    std::string fullpath = isAbsolutePath(filename)? filename:fullPathForFilename(filename.c_str());

    RawFile *fp = RawFileUtils::GetInstance().Open(fullpath.c_str());//fopen(strFilePath.c_str(), "r");
    if (!fp) {
        OHOS_LOGE("FileUtilsOhos::fp is nullptr");
        return false;
    }

    bool result = RawFileUtils::GetInstance().GetRawFileDescriptor(fp, descriptor);
    RawFileUtils::GetInstance().Close(fp);
    return result;
}

unsigned char* CCFileUtilsOhos::getFileData(const char* pszFileName, const char* pszMode, unsigned long* pSize) {
    return doGetFileData(pszFileName, pszMode, pSize, false);
}

unsigned char* CCFileUtilsOhos::getFileDataForAsync(const char* pszFileName, const char* pszMode, unsigned long* pSize) {
    return doGetFileData(pszFileName, pszMode, pSize, true);
}

unsigned char* CCFileUtilsOhos::doGetFileData(const char* pszFileName, const char* pszMode, unsigned long* pSize, bool forAsync) {
    unsigned char * pData = 0;
    if ((! pszFileName) || (! pszMode) || 0 == strlen(pszFileName))
    {
        return 0;
    }
    
   std::string fullpath = fullPathForFilename(pszFileName);
    if(fullpath[0] != '/') {
        do {
        RawFile *fp = RawFileUtils::GetInstance().Open(fullpath.c_str());
        CCLOG("===================> doGetFileData %s", pszFileName);
        CC_BREAK_IF(!fp);
        long size = RawFileUtils::GetInstance().GetSize(fp);
        pData = new unsigned char[size];
        size = RawFileUtils::GetInstance().Read(fp, pData, size);
        RawFileUtils::GetInstance().Close(fp);
        CCLOG("===================> doGetFileData %d", size);
        if (pSize) {
            *pSize = size;
        }
    } while (0);
        
    } else {
        do {
            // read rrom other path than user set it
	        //CCLOG("GETTING FILE ABSOLUTE DATA: %s", pszFileName);
            FILE *fp = fopen(fullpath.c_str(), pszMode);
            CC_BREAK_IF(!fp);

            unsigned long size;
            fseek(fp,0,SEEK_END);
            size = ftell(fp);
            fseek(fp,0,SEEK_SET);
            pData = new unsigned char[size];
            size = fread(pData,sizeof(unsigned char), size,fp);
            fclose(fp);

            if (pSize) {
                *pSize = size;
            }            
        } while (0);        
    }
    
    
    if (! pData) {
        std::string msg = "Get data from file(";
        msg.append(pszFileName).append(") failed!");
        CCLOG("%s", msg.c_str());
    }
    
    return pData;
}

string CCFileUtilsOhos::getWritablePath() {
    return ohWritablePath;
}

NS_CC_END
