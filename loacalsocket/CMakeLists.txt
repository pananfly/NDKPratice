cmake_minimum_required(VERSION 3.4.1)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall")
set(SO_NAME "localsocket")
set(
        libcutils
        ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libcutils.so
)
set(JNI_LOG_TAG "socket")
set(JNI_CLASS_NAME "com/pananfly/loacalsocket/LocalSocketJNIHelper")
configure_file(src/main/cpp/config.h.in config.h @ONLY)

add_library( ${SO_NAME}
             SHARED
        src/main/cpp/localsocket.c
        src/main/cpp/j4a/j4a_allclasses.c
        src/main/cpp/j4a/j4a_base.c
        src/main/cpp/j4a/class/android/net/LocalServerSocket.c
        src/main/cpp/j4a/class/android/net/LocalSocket.c
        src/main/cpp/j4a/class/android/net/LocalSocketAddress.c
        src/main/cpp/j4a/class/java/io/InputStream.c
        src/main/cpp/j4a/class/java/io/OutputStream.c
        src/main/cpp/j4a/class/com/pananfly/loacalsocket/local_socket_helper.c
        src/main/cpp/lsocket.c
        src/main/cpp/common/jni_thread.c
        src/main/cpp/common/p_mutex.c
        src/main/cpp/common/p_thread.c
        src/main/cpp/common/jni_register.c
             )

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
        libs/libcutils/include
        src/main/cpp
        src/main/cpp/common/
        src/main/cpp/j4a/class/com/pananfly/loacalsocket/
        src/main/cpp/j4a/class/android/net/
        src/main/cpp/j4a/class/java/io/
        )

target_link_libraries( # Specifies the target library.
                      ${SO_NAME}
                      ${libcutils}
                      android
                      # Links the target library to the log library
                      # included in the NDK.
                      ${log-lib} )

