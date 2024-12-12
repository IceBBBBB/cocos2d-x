
set(COCOS_STORAGE_SRC
  storage/local-storage/LocalStorage.cpp
  )

set(COCOS_STORAGE_LINK
    sqlite3
)

if(OHOS)
  include_directories(${COCOS2DX_ROOT_PATH}/external/sqlit3/include)
endif()
