package com.pananfly.loacalsocket

class LocalSocketJNIHelper {
    companion object {
        init {
            System.loadLibrary("localsocket")
        }
    }
    external fun test(): Int
    external fun startSocket(address: String): Int
    external fun stopSocket(): Int
}