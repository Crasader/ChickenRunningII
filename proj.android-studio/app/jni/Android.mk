LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../../Classes/AppDelegate.cpp                           \
                   ../../../Classes/Layer/GameIntroLayer.cpp                  \
                   ../../../Classes/Layer/GameLayer.cpp                       \
                   ../../../Classes/Layer/GameMenuLayer.cpp                   \
                   ../../../Classes/Layer/GameWarningLayer.cpp                \
                   ../../../Classes/Layer/GameWinLayer.cpp                    \
                   ../../../Classes/Layer/InstructionLayer.cpp                \
                   ../../../Classes/Layer/LevelSelectLayer.cpp                \
                   ../../../Classes/Layer/WarningLayer.cpp                    \
                   ../../../Classes/Scene/AchievementsScene.cpp               \
                   ../../../Classes/Scene/GameScene.cpp                       \
                   ../../../Classes/Scene/InstructionsScene.cpp               \
                   ../../../Classes/Scene/LoadingScene.cpp                    \
                   ../../../Classes/Scene/MapScene.cpp                        \
                   ../../../Classes/Scene/MenuScene.cpp                       \
                   ../../../Classes/Scene/OptionsScene.cpp                    \
                   ../../../Classes/Scene/SelectLevelScene.cpp                \
                   ../../../Classes/Singletons/Achievements.cpp               \
                   ../../../Classes/Singletons/GameData.cpp                   \
                   ../../../Classes/Singletons/GameDataKey.cpp                \
                   ../../../Classes/Singletons/Helpers.cpp                    \
                   ../../../Classes/Singletons/Level.cpp                      \
                   ../../../Classes/Singletons/Levels.cpp                     \
                   ../../../Classes/Singletons/Options.cpp                    \
                   ../../../Classes/Singletons/Sound.cpp                      \
                   ../../../Classes/SonarCocosHelper/JNI/JNIHelpers.cpp \
                   ../../../Classes/SonarCocosHelper/JNI/JNIResults.cpp \
                   ../../../Classes/SonarCocosHelper/SonarFrameworks.cpp      \
                   ../../../Classes/Sprite/ExtensibleSettingButton.cpp        \
                   ../../../Classes/Sprite/GameTile.cpp                       \
                   ../../../Classes/Sprite/LevelSelect.cpp                    \
                   ../../../Classes/Sprite/MapIcon.cpp                        \
                   ../../../Classes/Sprite/Pagination.cpp                     \
                   ../../../Classes/Utility/DataCenter.cpp                    \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes \
$(LOCAL_PATH)/../../../Classes/Layer \
$(LOCAL_PATH)/../../../Classes/Scene \
$(LOCAL_PATH)/../../../Classes/Singletons \
$(LOCAL_PATH)/../../../Classes/SonarCocosHelper/JNI  \
$(LOCAL_PATH)/../../../Classes/SonarCocosHelper  \
$(LOCAL_PATH)/../../../Classes/Sprite \
$(LOCAL_PATH)/../../../Classes/Utility \

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
