
if(WINDOWS)
  set(PLATFORM_LINK websockets)
elseif(LINUX)
  set(PLATFORM_LINK websockets ssl crypto)
else()
  set(PLATFORM_LINK websockets)
endif()

if(OHOS)
set(COCOS_NETWORK_SRC
    network/HttpClient.cpp
)
else()
set(COCOS_NETWORK_SRC
    network/HttpClient.cpp
    network/SocketIO.cpp
    network/WebSocket.cpp

)
endif()

if(MSVC)
  set(COCOS_NETWORK_LINK 
    libcurl_imp 
    ${PLATFORM_LINK}
  )
else()
  set(COCOS_NETWORK_LINK 
    curl
    ${PLATFORM_LINK} 
  )
endif()
