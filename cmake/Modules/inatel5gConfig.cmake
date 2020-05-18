INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_INATEL5G inatel5g)

FIND_PATH(
    INATEL5G_INCLUDE_DIRS
    NAMES inatel5g/api.h
    HINTS $ENV{INATEL5G_DIR}/include
        ${PC_INATEL5G_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    INATEL5G_LIBRARIES
    NAMES gnuradio-inatel5g
    HINTS $ENV{INATEL5G_DIR}/lib
        ${PC_INATEL5G_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(INATEL5G DEFAULT_MSG INATEL5G_LIBRARIES INATEL5G_INCLUDE_DIRS)
MARK_AS_ADVANCED(INATEL5G_LIBRARIES INATEL5G_INCLUDE_DIRS)

