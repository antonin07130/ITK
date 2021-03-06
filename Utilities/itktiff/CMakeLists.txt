project(ITKTIFF)
include_regular_expression("^(itk|tif|fax|port|uv|tconf|t4|mk|itkjpeg|jpeg|mangle|jconfig|jmorecfg).*$")

include_directories(BEFORE ${ITKTIFF_SOURCE_DIR})
include_directories(BEFORE ${ITKTIFF_BINARY_DIR})

# library object files common to compression and decompression
set(common_SRCS
  tif_aux.c
  tif_close.c
  tif_codec.c
  tif_compress.c
  tif_color.c
  tif_dir.c
  tif_dirinfo.c
  tif_dirread.c
  tif_dirwrite.c
  tif_dumpmode.c
  tif_error.c
  tif_extension.c
  tif_fax3.c
  tif_flush.c
  tif_getimage.c
  tif_luv.c
  tif_lzw.c
  tif_next.c
  tif_open.c
  tif_packbits.c
  tif_predict.c
  tif_print.c
  tif_read.c
  tif_strip.c
  tif_swab.c
  tif_tile.c
  tif_version.c
  tif_warning.c
  tif_write.c
  tif_zip.c
  tif_jpeg.c
  )

add_definitions(-DJPEG_SUPPORT -DZIP_SUPPORT -D_HPUX_SOURCE)

if(WIN32)
  if(BUILD_SHARED_LIBS)
    set(TIFFDLL 1)
  else(BUILD_SHARED_LIBS)
    set(TIFFSTATIC 1)
  endif(BUILD_SHARED_LIBS)
endif(WIN32)

if(BORLAND)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w-8004 -w-8057")
endif(BORLAND)

if(NOT UNIX)
  add_definitions( -DTIF_PLATFORM_CONSOLE )
  set(common_SRCS ${common_SRCS} tif_win32.c tif_fax3sm.c)
  if(NOT BORLAND)
    if(NOT MINGW)
      set(common_SRCS ${common_SRCS} itktiff.def)
    endif(NOT MINGW)
  endif(NOT BORLAND)
else(NOT UNIX)
  set(TIFF_RIGHT_VERSION 1)

  set(common_SRCS ${common_SRCS} tif_unix.c tif_fax3sm.c)
  set_source_files_properties(tif_fax3sm.c GENERATED)
  add_executable(itkmkg3states mkg3states.c)
  if(CYGWIN)
    set(EXE_EXTENSION .exe)
  endif(CYGWIN)
  add_custom_command(
    OUTPUT ${ITKTIFF_BINARY_DIR}/tif_fax3sm.c
    COMMAND ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/itkmkg3states${EXE_EXTENSION}
    ARGS -c const ${ITKTIFF_BINARY_DIR}/tif_fax3sm.c
    DEPENDS itkmkg3states
    )
endif(NOT UNIX)

include(${CMAKE_ROOT}/Modules/CheckIncludeFiles.cmake)
include(${CMAKE_ROOT}/Modules/CheckSymbolExists.cmake)
include(${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)

# Check if header file exists and add it to the list.
CHECK_INCLUDE_FILES("assert.h" HAVE_ASSERT_H)
CHECK_INCLUDE_FILES("dlfcn.h" HAVE_DLFCN_H)
CHECK_INCLUDE_FILES("fcntl.h" HAVE_FCNTL_H)
CHECK_INCLUDE_FILES("inttypes.h" HAVE_INTTYPES_H)
CHECK_INCLUDE_FILES("limits.h" HAVE_LIMITS_H)
CHECK_INCLUDE_FILES("malloc.h" HAVE_MALLOC_H)
CHECK_INCLUDE_FILES("memory.h" HAVE_MEMORY_H)
CHECK_INCLUDE_FILES("stdint.h" HAVE_STDINT_H)
CHECK_INCLUDE_FILES("stdlib.h" HAVE_STDLIB_H)
CHECK_INCLUDE_FILES("string.h" HAVE_STRING_H)
CHECK_INCLUDE_FILES("strings.h" HAVE_STRINGS_H)
CHECK_INCLUDE_FILES("sys/stat.h" HAVE_SYS_STAT_H)
CHECK_INCLUDE_FILES("sys/time.h" HAVE_SYS_TIME_H)
CHECK_INCLUDE_FILES("sys/types.h" HAVE_SYS_TYPES_H)
CHECK_INCLUDE_FILES("unistd.h" HAVE_UNISTD_H)
CHECK_INCLUDE_FILES("windows.h" HAVE_WINDOWS_H)
CHECK_INCLUDE_FILES("strings.h" HAVE_STRINGS_H)
CHECK_INCLUDE_FILES("ieeefp.h" HAVE_IEEEFP_H)

CHECK_FUNCTION_EXISTS(floor HAVE_FLOOR)
CHECK_FUNCTION_EXISTS(getopt HAVE_GETOPT)
CHECK_FUNCTION_EXISTS(isascii HAVE_ISASCII)
CHECK_FUNCTION_EXISTS(memmove HAVE_MEMMOVE)
CHECK_FUNCTION_EXISTS(memset HAVE_MEMSET)
CHECK_FUNCTION_EXISTS(mmap HAVE_MMAP)
CHECK_FUNCTION_EXISTS(pow HAVE_POW)
CHECK_FUNCTION_EXISTS(sqrt HAVE_SQRT)
CHECK_FUNCTION_EXISTS(strcasecmp HAVE_STRCASECMP)
CHECK_FUNCTION_EXISTS(strchr HAVE_STRCHR)
CHECK_FUNCTION_EXISTS(strrchr HAVE_STRRCHR)
CHECK_FUNCTION_EXISTS(strstr HAVE_STRSTR)
CHECK_FUNCTION_EXISTS(strtol HAVE_STRTOL)
CHECK_FUNCTION_EXISTS(strtoul HAVE_STRTOUL)


if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.0)
else("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.0)
  include(CheckTypeSize)
endif("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.0)

CHECK_TYPE_SIZE("int" SIZEOF_INT)
CHECK_TYPE_SIZE("long" SIZEOF_LONG)


configure_file(${ITKTIFF_SOURCE_DIR}/.NoDartCoverage
  ${ITKTIFF_BINARY_DIR}/.NoDartCoverage)
configure_file(${ITKTIFF_SOURCE_DIR}/tiffDllConfig.h.in
  ${ITKTIFF_BINARY_DIR}/tiffDllConfig.h)
configure_file(${ITKTIFF_SOURCE_DIR}/tif_config.h.in
  ${ITKTIFF_BINARY_DIR}/tif_config.h)

add_library(itktiff ${common_SRCS})
target_link_libraries(itktiff ${ITK_ZLIB_LIBRARIES}
 ${ITK_JPEG_LIBRARIES})

if(UNIX)
  target_link_libraries(itktiff -lm)
endif(UNIX)

# Apply user-defined properties to the library target.
if(ITK_LIBRARY_PROPERTIES)
  set_target_properties(itktiff PROPERTIES ${ITK_LIBRARY_PROPERTIES})
endif(ITK_LIBRARY_PROPERTIES)

if(NOT ITK_INSTALL_NO_LIBRARIES)
  install(TARGETS itktiff
    RUNTIME DESTINATION ${ITK_INSTALL_BIN_DIR_CM24} COMPONENT RuntimeLibraries
    LIBRARY DESTINATION ${ITK_INSTALL_LIB_DIR_CM24} COMPONENT RuntimeLibraries
    ARCHIVE DESTINATION ${ITK_INSTALL_LIB_DIR_CM24} COMPONENT Development)
endif(NOT ITK_INSTALL_NO_LIBRARIES)

if(ITK_USE_FLAT_DIRECTORY_INSTALL)
  set( ITK_INSTALL_INCLUDE_DIR_CM24_UTILITIES_TIFF ${ITK_INSTALL_INCLUDE_DIR_CM24})
else(ITK_USE_FLAT_DIRECTORY_INSTALL)
  set( ITK_INSTALL_INCLUDE_DIR_CM24_UTILITIES_TIFF ${ITK_INSTALL_INCLUDE_DIR_CM24}/Utilities/itktiff)
endif(ITK_USE_FLAT_DIRECTORY_INSTALL)


if(NOT ITK_INSTALL_NO_DEVELOPMENT)
  install(FILES
    ${ITKTIFF_BINARY_DIR}/tiffDllConfig.h
    ${ITKTIFF_SOURCE_DIR}/tiffvers.h
    ${ITKTIFF_SOURCE_DIR}/itk_tiff_mangle.h
    ${ITKTIFF_SOURCE_DIR}/tiff.h
    ${ITKTIFF_SOURCE_DIR}/tiffio.h
    ${ITKTIFF_SOURCE_DIR}/tconf.h
    DESTINATION ${ITK_INSTALL_INCLUDE_DIR_CM24_UTILITIES_TIFF}
    COMPONENT Development)
endif(NOT ITK_INSTALL_NO_DEVELOPMENT)

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-strict-aliasing")
endif(CMAKE_COMPILER_IS_GNUCXX)
