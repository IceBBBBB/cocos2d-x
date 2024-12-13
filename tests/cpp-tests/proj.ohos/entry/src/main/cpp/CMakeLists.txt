cmake_minimum_required(VERSION 3.4.1)
project(nativerender)

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../..)
set(CLASSES_PATH  ${COCOS2DX_ROOT_PATH}/tests/cpp-tests/Classes)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti -fexceptions -fsigned-char")
add_definitions(-DOHOS)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/../resources/rawfile)
    file(GLOB ALL_RESOURCES_FILES "${CMAKE_CURRENT_LIST_DIR}/../../../../../Resources/*")
    file(COPY ${ALL_RESOURCES_FILES} DESTINATION ${CMAKE_CURRENT_LIST_DIR}/../resources/rawfile)
endif()

add_library(${PROJECT_NAME} SHARED main.cpp napi_init.cpp)
 
target_include_directories(${PROJECT_NAME} PUBLIC ${CLASSES_PATH}
        ${COCOS2DX_ROOT_PATH}/cocos
        ${COCOS2DX_ROOT_PATH}/cocos/base
        ${COCOS2DX_ROOT_PATH}/cocos/math/kazmath
        ${COCOS2DX_ROOT_PATH}/cocos/physics
                                                  ${COCOS2DX_ROOT_PATH}/cocos/2d/platform/ohos)

find_library(hilog-lib hilog_ndk.z)
find_library(libuv-lib uv)
target_link_libraries(${PROJECT_NAME} cocos2d cpp-tests GLESv3 ${hilog-lib} ${libuv-lib})

add_subdirectory(${COCOS2DX_ROOT_PATH} cocos2dx)
