# Linking module with libiio library
INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_IIO libiio)

# IIO headers search in listed paths.
FIND_PATH(
    IIO_INCLUDE_DIR
    NAMES iio.h
    HINTS ${PC_IIO_INCLUDE_DIR}/include
	  ${IIO_DIR}/include
	  /usr/local/include/
	  /usr/local/src/libiio/
 	  /usr/src/linux-headers-4.4.0-21/include/linux/iio
)

# .so files search in listed paths
FIND_LIBRARY(
    IIO_LIBRARIES
    NAMES libiio.so.0.11
    HINTS $ENV{IIO_DIR}/lib
        ${PC_IIO_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64s
	  /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
	  /usr/pkgs64/lib
)

# Flow control in case the files needed are found
IF (IIO_LIBRARIES AND IIO_INCLUDE_DIR)
    SET(IIO_LIBRARIES ${IIO_LIBRARIES})
    SET(IIO_FOUND "YES")
ELSE (IIO_LIBRARIES AND IIO_INCLUDE_DIR)
    SET(IIO_FOUND "NO")
ENDIF(IIO_LIBRARIES AND IIO_INCLUDE_DIR)

IF (IIO_FOUND)
    IF (NOT IIO_FIND_QUIETLY)
        MESSAGE(STATUS "Found IIO: ${IIO_LIBRARIES}")
    ENDIF(NOT IIO_FIND_QUIETLY)
    
ELSE (IIO_FOUND)
    IF (IIO_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find IIO library")
    ENDIF (IIO_FIND_REQUIRED)
ENDIF (IIO_FOUND)

# This prints in terminal both cases exit and failure
MARK_AS_ADVANCED(
    IIO_LIBRARIES 
    IIO_INCLUDE_DIR
)
