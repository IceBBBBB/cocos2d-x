if(OHOS)
	cmake_minimum_required(VERSION 3.6)

	project(extensions)
	set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/..)
	set(EXTENSION_SRC
	    AssetsManager/AssetsManager.cpp
	    CCArmature/physics/CCPhysicsWorld.cpp
	    CCBReader/CCBFileLoader.cpp
	    CCBReader/CCBReader.cpp
	    CCBReader/CCControlButtonLoader.cpp
	    CCBReader/CCControlLoader.cpp
	    CCBReader/CCLabelBMFontLoader.cpp
	    CCBReader/CCLabelTTFLoader.cpp
	    CCBReader/CCLayerColorLoader.cpp
	    CCBReader/CCLayerGradientLoader.cpp
	    CCBReader/CCLayerLoader.cpp
	    CCBReader/CCMenuItemImageLoader.cpp
	    CCBReader/CCMenuItemLoader.cpp
	    CCBReader/CCNodeLoader.cpp
	    CCBReader/CCNodeLoaderLibrary.cpp
	    CCBReader/CCParticleSystemQuadLoader.cpp
	    CCBReader/CCScale9SpriteLoader.cpp
	    CCBReader/CCScrollViewLoader.cpp
	    CCBReader/CCSpriteLoader.cpp
	    CCBReader/CCBAnimationManager.cpp
	    CCBReader/CCBKeyframe.cpp
	    CCBReader/CCBSequence.cpp
	    CCBReader/CCBSequenceProperty.cpp
	    CCBReader/CCBValue.cpp
	    CCBReader/CCData.cpp
	    CCBReader/CCNode+CCBRelativePositioning.cpp
	    GUI/CCControlExtension/CCControl.cpp
	    GUI/CCControlExtension/CCControlButton.cpp
	    GUI/CCControlExtension/CCControlColourPicker.cpp
	    GUI/CCControlExtension/CCControlHuePicker.cpp
	    GUI/CCControlExtension/CCControlSaturationBrightnessPicker.cpp
	    GUI/CCControlExtension/CCControlSlider.cpp
	    GUI/CCControlExtension/CCControlSwitch.cpp
	    GUI/CCControlExtension/CCControlUtils.cpp
	    GUI/CCControlExtension/CCInvocation.cpp
	    GUI/CCControlExtension/CCScale9Sprite.cpp
	    GUI/CCControlExtension/CCControlPotentiometer.cpp
	    GUI/CCControlExtension/CCControlStepper.cpp
	    GUI/CCScrollView/CCScrollView.cpp
	    GUI/CCScrollView/CCTableView.cpp
	    GUI/CCScrollView/CCTableViewCell.cpp
	    GUI/CCScrollView/CCSorting.cpp
	    GUI/CCEditBox/CCEditBox.cpp
	    GUI/CCEditBox/CCEditBoxImplOhos.cpp
	    GUI/CCEditBox/CCEditBoxImpl-common.cpp
	    # network/HttpClient.cpp
	    # network/WebSocket.cpp
	    physics_nodes/CCPhysicsDebugNode.cpp
	    physics_nodes/CCPhysicsSprite.cpp
	    LocalStorage/LocalStorageOhos.cpp
	    CCArmature/CCArmature.cpp
	    CCArmature/CCBone.cpp
	    CCArmature/animation/CCArmatureAnimation.cpp
	    CCArmature/animation/CCProcessBase.cpp
	    CCArmature/animation/CCTween.cpp
	    CCArmature/datas/CCDatas.cpp
	    CCArmature/display/CCBatchNode.cpp
	    CCArmature/display/CCDecorativeDisplay.cpp
	    CCArmature/display/CCDisplayFactory.cpp
	    CCArmature/display/CCDisplayManager.cpp
	    CCArmature/display/CCSkin.cpp
	    CCArmature/physics/CCColliderDetector.cpp
	    CCArmature/utils/CCArmatureDefine.h
	    CCArmature/utils/CCArmatureDataManager.cpp
	    CCArmature/utils/CCDataReaderHelper.cpp
	    CCArmature/utils/CCSpriteFrameCacheHelper.cpp
	    CCArmature/utils/CCTransformHelp.cpp
	    CCArmature/utils/CCTweenFunction.cpp
	    CCArmature/utils/CCUtilMath.cpp
	    CCArmature/external_tool/GLES-Render.cpp
	    CCArmature/external_tool/Json/CSContentJsonDictionary.cpp
	    CCArmature/external_tool/Json/lib_json/json_value.cpp
	    CCArmature/external_tool/Json/lib_json/json_reader.cpp
	    CCArmature/external_tool/Json/lib_json/json_writer.cpp
	    CCArmature/display/CCShaderNode.cpp
    
	    Components/CCComAttribute.cpp
	    Components/CCComAudio.cpp
	    Components/CCComController.cpp
	    Components/CCInputDelegate.cpp
	    spine/Animation.cpp
	    spine/AnimationState.cpp
	    spine/AnimationStateData.cpp
	    spine/Atlas.cpp
	    spine/AtlasAttachmentLoader.cpp
	    spine/Attachment.cpp
	    spine/AttachmentLoader.cpp
	    spine/Bone.cpp
	    spine/BoneData.cpp
	    spine/Json.cpp
	    spine/RegionAttachment.cpp
	    spine/Skeleton.cpp
	    spine/SkeletonData.cpp
	    spine/SkeletonJson.cpp
	    spine/Skin.cpp
	    spine/Slot.cpp
	    spine/SlotData.cpp
	    spine/extension.cpp
	    spine/CCSkeletonAnimation.cpp
	    spine/CCSkeleton.cpp
	    spine/spine-cocos2dx.cpp
	)

	add_library(${PROJECT_NAME} STATIC ${EXTENSION_SRC})
	target_link_libraries(${PROJECT_NAME} box2d chipmunk cocosdenshion)
	set(CMAKE_C_FLAGS -fexceptions)
	target_compile_options(${PROJECT_NAME} PUBLIC -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 -DOpenHarmony=1)
	target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/
	                                                  ${CMAKE_CURRENT_SOURCE_DIR}/CCBReader
	                                                  ${CMAKE_CURRENT_SOURCE_DIR}/GUI/CCControlExtension
	                                                  ${CMAKE_CURRENT_SOURCE_DIR}/GUI/CCScrollView
	                                                  ${CMAKE_CURRENT_SOURCE_DIR}/LocalStorage
	                                                  ${CMAKE_CURRENT_SOURCE_DIR}/CocoStudio/Armature
	                                                  ${CMAKE_CURRENT_SOURCE_DIR}/CocoStudio
	                                                  ${CMAKE_CURRENT_SOURCE_DIR}/../cocos2dx/include
	                                                  ${CMAKE_CURRENT_SOURCE_DIR}/../cocos2dx/
	                                                  ${CMAKE_CURRENT_SOURCE_DIR}/../cocos2dx/platform/ohos/
	                                                  ${CMAKE_CURRENT_SOURCE_DIR}/../cocos2dx/kazmath/include/
	                                                  ${CMAKE_CURRENT_SOURCE_DIR}/../external/chipmunk/include/chipmunk/
	                                                  ${CMAKE_CURRENT_SOURCE_DIR}/../CocosDenshion/include/)

	add_subdirectory(${COCOS2DX_ROOT_PATH}/external/Box2D Box2D)
	add_subdirectory(${COCOS2DX_ROOT_PATH}/external/chipmunk chipmunk)
endif()