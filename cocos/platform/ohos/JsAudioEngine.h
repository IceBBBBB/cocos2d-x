#ifndef JsAudioEngine_H
#define JsAudioEngine_H

#include <napi/native_api.h>
#include <string>
#include "CCPlatformMacros.h"

NS_CC_BEGIN
class JsAudioEngine{
public:    
    constexpr static const float DEFAULT_VOLUME = 0.5f;
    static napi_value initJsAudioEngine(napi_env env, napi_value exports);
    static void preLoadBackgroundMusic(std::string& audioUri);
    static void playBackgroundMusic(std::string& audioUri, int seek);
    static void playBackgroundMusic(std::string& audioUri);
    static void stopBackgroundMusic(std::string& audioUri);
    static void pauseBackgroundMusic();
    static void resumeBackgroundMusic();
    static void rewindBackgroundMusic();
    static void seekBackgroundMusic(int seek);
    static float getBackgroundMusicVolume();
    static void setBackgroundMusicVolume(const float volume);

    static float getEffectsVolume();
    static void setEffectsVolume(float volume);
    static unsigned int playEffect(const char* pszFilePath, bool bLoop);
    static void pauseEffect(unsigned int nSoundId);
    static void pauseAllEffects();
    static void resumeEffect(unsigned int nSoundId);
    static void resumeAllEffects();
    static void stopEffect(unsigned int nSoundId);
    static void stopAllEffects();
    static void preloadEffect(const char* pszFilePath);
    static void unloadEffect(const char* pszFilePath);    
    
    
    static napi_value getEngineFunc(const char* funcName);
private:
    static napi_env _env;
};
#endif //XComponent_JsAudioEngine_H
NS_CC_END