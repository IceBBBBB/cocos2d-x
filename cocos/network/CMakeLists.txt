if(WIN32)
  set(PLATFORM_SRC
    WebSocket.cpp
  )

  set(PLATFORM_LINK
    websockets
  )
elseif(OHOS)
  set(PLATFORM_SRC
    WebSocket.cpp
  )
elseif(NOT APPLE)
  set(PLATFORM_SRC
    WebSocket.cpp
  )

  set(PLATFORM_LINK
    websockets
    ssl
    crypto
  )
endif()

set(NETWORK_SRC
  HttpClient.cpp
  SocketIO.cpp
  ${PLATFORM_SRC}
)

add_library(network STATIC
  ${NETWORK_SRC}
)
if(OHOS)
  # include_directories(${COCOS2DX_ROOT_PATH}/external/curl/include/ohos)
  include_directories(${COCOS2DX_ROOT_PATH}/external/websockets/include/ohos)
  target_link_libraries(network
    ext_curl
    ext_websockets
    ext_ssl
    ext_crypto
  )
else()
target_link_libraries(network
  curl
  ${PLATFORM_LINK}
)
endif()

set_target_properties(network
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

