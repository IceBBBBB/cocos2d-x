/****************************************************************************
Copyright (c) 2016 Chukong Technologies Inc.
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

#pragma once

#include <condition_variable>
#include <memory>
#include <unordered_map>
#include "IAudioPlayer.h"
#include "OpenSLHelper.h"
#include "PcmData.h"
#include "audio_utils/AudioDef.h"


namespace cocos2d { namespace experimental {
// Manage PcmAudioPlayer& UrlAudioPlayer

class PcmAudioPlayer;
class PcmAudioService;
class UrlAudioPlayer;
class AudioMixerController;
class ICallerThreadUtils;
class AssetFd;
class LegacyThreadPool;

        class AudioPlayerProvider {
        public:
            AudioPlayerProvider(SLEngineItf engineItf, int deviceSampleRate,
                        const FdGetterCallback &fdGetterCallback, ICallerThreadUtils *callerThreadUtils);

    virtual ~AudioPlayerProvider();
    bool isFileCached(const std::string &audioFilePath);
    IAudioPlayer *getAudioPlayer(const std::string &audioFilePath);
    bool getPcmHeader(const std::string &audioFilePath, PCMHeader &header);
    bool getPcmData(const std::string &audioFilePath, PcmData &data);
    using PreloadCallback = std::function<void(bool, PcmData)>;
    void preloadEffect(const std::string &audioFilePath, const PreloadCallback &callback);
    void registerPcmData(const std::string &audioFilePath, PcmData &data);
    float getDurationFromFile(const std::string &filePath);
    void clearPcmCache(const std::string &audioFilePath);

    void clearAllPcmCaches();

    void pause();

    void resume();


    struct AudioFileInfo {
        std::string url;
        std::shared_ptr<AssetFd> assetFd;
        off_t start{};
        off_t length;

        AudioFileInfo()
        : assetFd(nullptr) {}

        inline bool isValid() const {
            return !url.empty() && length > 0;
        }
    };

    PcmAudioPlayer *obtainPcmAudioPlayer(const std::string &url, const PcmData &pcmData);

    UrlAudioPlayer *createUrlAudioPlayer(const AudioFileInfo &info);

    void preloadEffect(const AudioFileInfo &info, const PreloadCallback &callback, bool isPreloadInPlay2d);

    AudioFileInfo getFileInfo(const std::string &audioFilePath);

    bool isSmallFile(const AudioFileInfo &info);

    SLEngineItf _engineItf;
    SLObjectItf _outputMixObject;
    int _deviceSampleRate;
    int _bufferSizeInFrames;
    FdGetterCallback _fdGetterCallback;
    ICallerThreadUtils *_callerThreadUtils;

    std::unordered_map<std::string, PcmData> _pcmCache;
    std::mutex _pcmCacheMutex;

    struct PreloadCallbackParam {
        PreloadCallback callback;
        bool isPreloadInPlay2d;
    };

    std::unordered_map<std::string, std::vector<PreloadCallbackParam>> _preloadCallbackMap;
    std::mutex _preloadCallbackMutex;

    std::mutex _preloadWaitMutex;
    std::condition_variable _preloadWaitCond;

    PcmAudioService *_pcmAudioService;
    AudioMixerController *_mixController;

    LegacyThreadPool *_threadPool;
};

}} // namespace cocos2d { namespace experimental
