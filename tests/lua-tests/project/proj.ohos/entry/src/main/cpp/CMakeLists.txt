cmake_minimum_required(VERSION 3.4.1)
project(nativerender)

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../..)
set(CLASSES_PATH ${COCOS2DX_ROOT_PATH}/tests/lua-tests/project/Classes)

set(OHOS true)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options("-fsigned-char")
add_definitions(-DOHOS)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

add_library(${PROJECT_NAME} SHARED  main.cpp
                                    napi_init.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CLASSES_PATH}
                                           PUBLIC ${COCOS2DX_ROOT_PATH}/cocos
                                           PUBLIC ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos/
                                           )

add_subdirectory(${COCOS2DX_ROOT_PATH} cocos2dx)

find_library(hilog-lib hilog_ndk.z)
find_library(libuv-lib uv)
target_link_libraries(${PROJECT_NAME} PUBLIC cocos2d lua-tests ${hilog-lib} ${libuv-lib})
