set(APP_NAME lua-empty-test)

if(OHOS)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_SRC proj.ohos/entry/src/main/cpp/main.cpp Classes/AppDelegate.cpp)
    file(GLOB resFiles "${CMAKE_CURRENT_LIST_DIR}/../res/*")
    file(COPY ${resFiles} DESTINATION ${CMAKE_CURRENT_LIST_DIR}/proj.ohos/entry/src/main/resources/rawfile)
    file(GLOB srcFiles "${CMAKE_CURRENT_LIST_DIR}/../src/*")
    file(COPY ${srcFiles} DESTINATION ${CMAKE_CURRENT_LIST_DIR}/proj.ohos/entry/src/main/resources/rawfile)
    file(GLOB lualibFiles "${COCOS2DX_ROOT_PATH}/external/lua/luasocket/*")
    file(COPY ${lualibFiles} DESTINATION ${CMAKE_CURRENT_LIST_DIR}/proj.ohos/entry/src/main/resources/rawfile)
    if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/proj.ohos/entry/src/main/resources/rawfile/cocos)
        file(GLOB cocosFiles "${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/script/*")
        file(COPY ${cocosFiles} DESTINATION ${CMAKE_CURRENT_LIST_DIR}/proj.ohos/entry/src/main/resources/rawfile/cocos)
    endif()
    
    include_directories(
      Classes
      ../../../cocos/scripting/lua-bindings/manual
      ../../../external/lua/lua
      ../../../external/lua/tolua
    )
    add_library(${APP_NAME} SHARED ${APP_SRC})
    
    find_library( # Sets the name of the path variable.
                  hilog-lib
                  # Specifies the name of the NDK library that
                  # you want CMake to locate.
                  hilog_ndk.z )
    target_link_libraries(${APP_NAME}  ${hilog-lib})

else()
    set(SAMPLE_SRC
      proj.linux/main.cpp
      Classes/AppDelegate.cpp
    )

    include_directories(
      Classes
      ../../../cocos/scripting/lua/bindings
      ../../../external/lua/lua
      ../../../external/lua/tolua
    )

    # add the executable
    add_executable(${APP_NAME}
      ${SAMPLE_SRC}
    )
endif()
    
target_link_libraries(${APP_NAME}
  luabinding
  cocostudio
  cocosbuilder
  extensions
  audio
  cocos2d
)

set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}")

set_target_properties(${APP_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

pre_build(${APP_NAME}
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../res ${APP_BIN_DIR}/Resources/res
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../src ${APP_BIN_DIR}/Resources/src
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/script ${APP_BIN_DIR}/Resources
  )
