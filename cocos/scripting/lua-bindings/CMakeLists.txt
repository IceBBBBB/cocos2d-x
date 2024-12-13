set(LUABINDING_SRC
  auto/lua_cocos2dx_auto.cpp
  auto/lua_cocos2dx_extension_auto.cpp
  auto/lua_cocos2dx_studio_auto.cpp
  auto/lua_cocos2dx_ui_auto.cpp
  auto/lua_cocos2dx_spine_auto.cpp
  auto/lua_cocos2dx_physics_auto.cpp
  manual/tolua_fix.cpp
  manual/CCLuaBridge.cpp
  manual/CCLuaEngine.cpp
  manual/CCLuaStack.cpp
  manual/CCLuaValue.cpp
  manual/Cocos2dxLuaLoader.cpp
  manual/CCBProxy.cpp
  manual/LuaOpengl.cpp
  manual/LuaScriptHandlerMgr.cpp
  manual/LuaBasicConversions.cpp
  manual/lua_cocos2dx_manual.cpp
  manual/lua_cocos2dx_extension_manual.cpp
  manual/lua_cocos2dx_coco_studio_manual.cpp
  manual/lua_cocos2dx_ui_manual.cpp
  manual/lua_cocos2dx_spine_manual.cpp
  manual/lua_cocos2dx_physics_manual.cpp
  manual/lua_cocos2dx_deprecated.cpp
  manual/lua_xml_http_request.cpp
  manual/LuaSkeletonAnimation.cpp
)

include_directories(
  auto
  manual
  ../../editor-support/cocosbuilder
  ../../editor-support/cocostudio
  ../../editor-support/spine
  ../../ui
  ../../../external/lua/lua
  ../../../external/lua/tolua
)


if(OHOS)
  list(APPEND LUABINDING_SRC 
	  manual/LuaBasicConversions.h 
	  manual/Lua_web_socket.cpp
	  manual/lua_extensions.c
	  manual/tolua_fix.h
	  )
  include_directories(
    ../../../cocos/2d
    ../../../cocos/2d/platform/ohos 
    ../../../external/lua
    ../../../cocos
    ../../../cocos/2d
    ../../../cocos/2d/platform
  )
  add_definitions(-D_GNU_SOURCE)
  
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
endif()

add_library(luabinding STATIC ${LUABINDING_SRC})

target_link_libraries(luabinding
  tolua
  # lua
  ext_luajit
  spine
)
if(OHOS)
  target_link_libraries(luabinding cocos2d ${GLES-lib} ${EGL-lib} ext_luasocket)
endif()
set_target_properties(luabinding
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

