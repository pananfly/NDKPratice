package com.pananfly.loacalsocket

class LocalSocketJNIHelper {
    companion object {
        init {
            System.loadLibrary("localsocket")
        }
    }
    external fun test(): Int
    external fun startSocket(): Int
    external fun stopSocket(): Int
}