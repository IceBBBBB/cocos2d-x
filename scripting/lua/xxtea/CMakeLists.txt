if(OHOS)
	set(XXTEA_SRC
	  xxtea.cpp
	)  
	add_library(xxtea STATIC
	  ${XXTEA_SRC}
	)

	set_target_properties(xxtea
	    PROPERTIES
	    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	)
endif()