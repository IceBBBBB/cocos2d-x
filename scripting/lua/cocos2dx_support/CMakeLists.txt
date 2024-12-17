if(OHOS)
	set(LUABINDING_SRC
	  CCBProxy.cpp
	  CCLuaBridge.cpp
	  CCLuaEngine.cpp
	  CCLuaStack.cpp
	  CCLuaValue.cpp
	  Cocos2dxLuaLoader.cpp
	  lua_extensions_CCB.cpp
	  # Lua_web_socket.cpp
	  LuaCocos2d.cpp
	  tolua_fix.c
	)

	include_directories(
	  ../lua
	  ../tolua
	)

	add_definitions(-D_GNU_SOURCE)

	add_library(luabinding STATIC
	  ${LUABINDING_SRC}
	)

	target_link_libraries(luabinding
	  tolua
	  lua
	)
	target_link_libraries(luabinding cocos2dx_static ${GLES-lib} ${EGL-lib} )
	set_target_properties(luabinding
	    PROPERTIES
	    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	)
endif()
