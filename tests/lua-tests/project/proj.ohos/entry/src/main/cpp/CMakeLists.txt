cmake_minimum_required(VERSION 3.4.1)
project(nativerender)

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../..)

set(CLASSES_PATH ${COCOS2DX_ROOT_PATH}/tests/lua-tests/project/Classes)

set(OHOS true)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")


add_definitions(-DOHOS)

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

message("***************  GLES-lib: ${GLES-lib} ****************")

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
find_library( # Sets the name of the path variable.
              rawfile-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              rawfile.z )

#[[if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/../resources/rawfile)
    file(GLOB ALL_RESOURCES_FILES "${CMAKE_CURRENT_LIST_DIR}/../../../../../tests/lua-empty-tests/Resources/*")
    file(COPY ${ALL_RESOURCES_FILES}
        DESTINATION ${CMAKE_CURRENT_LIST_DIR}/../resources/rawfile)
endif()]]

add_library(${PROJECT_NAME} SHARED  main.cpp
                                    napi_init.cpp
                                    ${CLASSES_PATH}/AppDelegate.cpp)


target_include_directories(${PROJECT_NAME}  PUBLIC  ${CLASSES_PATH}
                                            PUBLIC  ${CLASSES_PATH}/../..
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos/2d
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos/2d/platform/ohos/napi/common
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos/2d/platform/ohos/napi/modules
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos/2d/platform/ohos/napi/render
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos/2d/platform/ohos/napi
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos/base
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos/editor-support
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/extensions
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos/audio/include
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos/math/kazmath
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos/physics
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/external/chipmunk/include
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/manual
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/external/lua/lua
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/external/lua/tolua
)


include_directories( 
                    ${COCOS2DX_ROOT_PATH}/cocos/2d/platform/ohos 
                    ${COCOS2DX_ROOT_PATH}/external/openssl/include/ohos 
                    ${COCOS2DX_ROOT_PATH}/external/sqlit3/include)
#TBD need fixed
target_include_directories(${PROJECT_NAME} PUBLIC ${COCOS2DX_ROOT_PATH}/external/chipmunk/include)

# add_subdirectory(${COCOS2DX_ROOT_PATH}/tests/lua-tests/project lua_test)
target_link_libraries(${PROJECT_NAME} PUBLIC cocos2d lua-tests ui ${libnapi-lib} ${GLES-lib} ${libace-lib} ${EGL-lib} ${hilog-lib} ${rawfile-lib} ${libnapi-lib} ${libuv-lib} ${rawfile-lib})

add_subdirectory(${COCOS2DX_ROOT_PATH} cocos2dx)