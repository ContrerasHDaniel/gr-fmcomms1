INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_FMCOMMS1 fmcomms1)

FIND_PATH(
    FMCOMMS1_INCLUDE_DIRS
    NAMES fmcomms1/api.h
    HINTS $ENV{FMCOMMS1_DIR}/include
        ${PC_FMCOMMS1_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    FMCOMMS1_LIBRARIES
    NAMES gnuradio-fmcomms1
    HINTS $ENV{FMCOMMS1_DIR}/lib
        ${PC_FMCOMMS1_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(FMCOMMS1 DEFAULT_MSG FMCOMMS1_LIBRARIES FMCOMMS1_INCLUDE_DIRS)
MARK_AS_ADVANCED(FMCOMMS1_LIBRARIES FMCOMMS1_INCLUDE_DIRS)

