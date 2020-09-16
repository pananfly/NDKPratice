cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall")
set(SO_NAME "cJSON")

add_library( ${SO_NAME}
             SHARED
        cJSON/cJSON.c
        cJSON/cJSON_Utils.c
        src/main/cpp/cJSONImpl.c
             )

#add_library(libava2 STATIC IMPORTED)
#set_target_properties(libava2 PROPERTIES IMPORTED_LOCATION
#        ${CMAKE_SOURCE_DIR}/../avasdklib/libs/libava2/${ANDROID_ABI}/libavaClient2.a)

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

include_directories(
        cJSON/)

target_link_libraries( # Specifies the target library.
                      ${SO_NAME}
                      android
                      # Links the target library to the log library
                      # included in the NDK.
                      ${log-lib} )

