if(WIN32)
  set(PLATFORM_SRC
    network/WebSocket.cpp
  )

  set(PLATFORM_LINK
    websockets
  )
elseif(OHOS)
 set(PLATFORM_SRC
    network/WebSocket.cpp
  )
  set(PLATFORM_LINK
    ext_websockets
    ext_ssl
    ext_crypto
  )
elseif(NOT APPLE)
  set(PLATFORM_SRC
    network/WebSocket.cpp
  )

  set(PLATFORM_LINK
    websockets
    ssl
    crypto
  )
endif()

set(COCOS_NETWORK_SRC
  network/HttpClient.cpp
  network/SocketIO.cpp
  ${PLATFORM_SRC}
)

if(OHOS)
  include_directories(${COCOS2DX_ROOT_PATH}/external/websockets/include/ohos)
set(COCOS_NETWORK_LINK
    ext_curl
    ${PLATFORM_LINK}
)
else()
set(COCOS_NETWORK_LINK
  curl
  ${PLATFORM_LINK}
)
endif()
