package com.pananfly.loacalsocket

import com.pananfly.loacalsocket.annotations.AccessdByNative

class LocalSocketJNIHelper {
    @AccessdByNative
    private var mNativeInstance: Long = 0
    companion object {
        init {
            System.loadLibrary("localsocket")
        }
    }
    external fun test(): Int
    external fun startSocket(address: String): Int
    external fun stopSocket(): Int
}