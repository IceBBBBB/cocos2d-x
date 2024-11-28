#/****************************************************************************
# Copyright (c) 2015 Chukong Technologies Inc.
# 
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/

set(APP_NAME js-tests)

if(WIN32)


elseif(OHOS)
    set(PLATFORM_SRC proj.ohos/entry/src/main/cpp/main.cpp)
else()
  set(PLATFORM_SRC
    proj.linux/main.cpp
  )
endif()

set(SAMPLE_SRC
  Classes/AppDelegate.cpp
  Classes/js_DrawNode3D_bindings.cpp
  Classes/js_Effect3D_bindings.cpp
  ${PLATFORM_SRC}
)

if(OHOS)
    add_library(${APP_NAME} SHARED ${SAMPLE_SRC})
    include_directories(Classes)
    add_definitions("-DOpenHarmony")
    include_directories(
            ${CMAKE_CURRENT_SOURCE_DIR}
            Classes
            ${COCOS2DX_ROOT_PATH}
            ${COCOS2DX_ROOT_PATH}/external
            ${COCOS2DX_ROOT_PATH}/external/chipmunk
            ${COCOS2DX_ROOT_PATH}/external/chipmunk/include/chipmunk
            ${COCOS2DX_ROOT_PATH}/external/lib
            ${COCOS2DX_ROOT_PATH}/external/Box2D
            ${COCOS2DX_ROOT_PATH}/external/tiff
            ${COCOS2DX_ROOT_PATH}/external/tiff/include/ohos
            ${COCOS2DX_ROOT_PATH}/cocos
            ${COCOS2DX_ROOT_PATH}/cocos/editor-support
            ${COCOS2DX_ROOT_PATH}/extensions
            ${COCOS2DX_ROOT_PATH}/cocos/base
            ${COCOS2DX_ROOT_PATH}/cocos/2d
            ${COCOS2DX_ROOT_PATH}/cocos/ui
            ${COCOS2DX_ROOT_PATH}/cocos/audio/include
            ${COCOS2DX_ROOT_PATH}/cocos/storage
            ${COCOS2DX_ROOT_PATH}/cocos/network
            ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos/napi
            ${COCOS2DX_ROOT_PATH}/cocos/editor-support/spine
            ${COCOS2DX_ROOT_PATH}/cocos/editor-support/cocosbuilder
            ${COCOS2DX_ROOT_PATH}/cocos/editor-support/cocostudio
            ${COCOS2DX_ROOT_PATH}/deprecated
            ${COCOS2DX_ROOT_PATH}/cocos/platform
            ${COCOS2DX_ROOT_PATH}/cocos/scripting/js-bindings/auto
            ${COCOS2DX_ROOT_PATH}/cocos/scripting/js-bindings/manual
            ${COCOS2DX_ROOT_PATH}/external/spidermonkey/include/ohos
    
    )

    find_library( # Sets the name of the path variable.
            EGL-lib
            # Specifies the name of the NDK library that
            # you want CMake to locate.
            EGL )

    find_library( # Sets the name of the path variable.
            GLES-lib
            # Specifies the name of the NDK library that
            # you want CMake to locate.
            GLESv3 )

    find_library( # Sets the name of the path variable.
            hilog-lib
            # Specifies the name of the NDK library that
            # you want CMake to locate.
            hilog_ndk.z )

    find_library( # Sets the name of the path variable.
            libace-lib
            # Specifies the name of the NDK library that
            # you want CMake to locate.
            ace_ndk.z )

    find_library( # Sets the name of the path variable.
            libnapi-lib
            # Specifies the name of the NDK library that
            # you want CMake to locate.
            ace_napi.z )

    find_library( # Sets the name of the path variable.
            libuv-lib
            # Specifies the name of the NDK library that
            # you want CMake to locate.
            uv )

    target_link_libraries(${APP_NAME} PUBLIC ${EGL-lib} ${GLES-lib} ${hilog-lib}
            ${libace-lib} ${libnapi-lib} ${libuv-lib} cocos2d)
else()
	include_directories(
	  Classes
	  ../../../cocos/scripting/js-bindings/auto
	  ../../../cocos/scripting/js-bindings/manual
	  ../../../cocos/base
	  ../../../cocos/editor-support
	  ../../../cocos/audio/include
	  ../../../external/spidermonkey/include/${PLATFORM_FOLDER}
	  ../../../external/chipmunk/include/chipmunk
	)

	# add the executable
	add_executable(${APP_NAME}
	  ${SAMPLE_SRC}
	)

endif()

target_link_libraries(${APP_NAME}
  jscocos2d
  cocos2d
)

set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}")

set_target_properties(${APP_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")


if(LINUX)
    set(RES_PREFIX "/Resources")
else()
    set(RES_PREFIX "")
endif()

if(NOT OHOS)
	pre_build(${APP_NAME}
	  COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}${RES_PREFIX}/script
	  COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}${RES_PREFIX}/res
	  COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}${RES_PREFIX}/src
	  COMMAND ${CMAKE_COMMAND} -E remove ${APP_BIN_DIR}${RES_PREFIX}/*.js
	  COMMAND ${CMAKE_COMMAND} -E remove ${APP_BIN_DIR}${RES_PREFIX}/*.json
	  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../../cpp-tests/Resources ${APP_BIN_DIR}${RES_PREFIX}/res
	  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../res ${APP_BIN_DIR}${RES_PREFIX}/res
	  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../src ${APP_BIN_DIR}${RES_PREFIX}/src
	  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../../../cocos/scripting/js-bindings/script ${APP_BIN_DIR}${RES_PREFIX}/script
	  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../main.js ${APP_BIN_DIR}${RES_PREFIX}/main.js
	  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../project.json ${APP_BIN_DIR}${RES_PREFIX}/project.json
	  )
endif()
