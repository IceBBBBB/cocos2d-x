cmake_minimum_required(VERSION 3.4.1)
project(nativerender)

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../..)

set(CLASSES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../Classes)

set(OHOS true)
set(platform_name "ohos")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
add_compile_options(-Wno-error=int-conversion)
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

add_definitions(-DOpenHarmony)
add_library(${PROJECT_NAME} SHARED  main.cpp
                                    napi_init.cpp
                                    ${CLASSES_PATH}/AppDelegate.cpp
                                    ${CLASSES_PATH}/lua_test_bindings.cpp
                                    ${CLASSES_PATH}/lua_assetsmanager_test_sample.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CLASSES_PATH})
target_include_directories(${PROJECT_NAME}  PUBLIC  ${COCOS2DX_ROOT_PATH}
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos/editor-support
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/extensions
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/external/lua/tolua
                                                    )
include_directories(${COCOS2DX_ROOT_PATH}/external/lua/luajit/include)
#TBD need fixed
target_include_directories(${PROJECT_NAME} PUBLIC ${COCOS2DX_ROOT_PATH}/external/chipmunk/include
    )

add_subdirectory(${COCOS2DX_ROOT_PATH}/external/lua/luajit luajit)
add_subdirectory(${COCOS2DX_ROOT_PATH}/tests/lua-tests/project lua_test)
message("***************  entry link gles  ****************")
#target_link_libraries(${PROJECT_NAME} PUBLIC cocos2d luacocos2d lua_ohos_spec lua_empty_test ${libnapi-lib} ${GLES-lib} ${hilog-lib})
target_link_libraries(${PROJECT_NAME} PUBLIC cocos2d luacocos2d luajit ${libnapi-lib} ${GLES-lib} ${hilog-lib} ${libace-lib} ${rawfile-lib})