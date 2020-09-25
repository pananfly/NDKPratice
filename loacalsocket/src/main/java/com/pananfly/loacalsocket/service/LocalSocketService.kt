package com.pananfly.loacalsocket.service

import android.app.Service
import android.content.Intent
import android.os.IBinder
import com.pananfly.loacalsocket.LocalSocketJNIHelper

const val SOCKET_ADDRESS: String = "com.pananfly.localsocket/test1"
const val SOCKET_ADDRESS1: String = "com.pananfly.localsocket/test2"
const val SOCKET_ADDRESS2: String = "com.pananfly.localsocket/test3"
const val SOCKET_ADDRESS3: String = "com.pananfly.localsocket/test4"
const val SOCKET_ADDRESS4: String = "com.pananfly.localsocket/test5"
const val SOCKET_ADDRESS5: String = "com.pananfly.localsocket/test6"
const val SOCKET_ADDRESS6: String = "com.pananfly.localsocket/test7"
const val SOCKET_ADDRESS7: String = "com.pananfly.localsocket/test8"
const val SOCKET_ADDRESS8: String = "com.pananfly.localsocket/test9"
class LocalSocketService : Service() {

    private var localSocket1: LocalSocketJNIHelper? = null
    private var localSocket2: LocalSocketJNIHelper? = null
    private var localSocket3: LocalSocketJNIHelper? = null
    private var localSocket4: LocalSocketJNIHelper? = null
    private var localSocket5: LocalSocketJNIHelper? = null
    private var localSocket6: LocalSocketJNIHelper? = null
    private var localSocket7: LocalSocketJNIHelper? = null
    private var localSocket8: LocalSocketJNIHelper? = null
    private var localSocket9: LocalSocketJNIHelper? = null
    override fun onBind(p0: Intent?): IBinder? {
        TODO("Not yet implemented")
    }

    override fun onCreate() {
        super.onCreate()
        localSocket1 = LocalSocketJNIHelper()
        localSocket2 = LocalSocketJNIHelper()
        localSocket3 = LocalSocketJNIHelper()
        localSocket4 = LocalSocketJNIHelper()
        localSocket5 = LocalSocketJNIHelper()
        localSocket6 = LocalSocketJNIHelper()
        localSocket7 = LocalSocketJNIHelper()
        localSocket8 = LocalSocketJNIHelper()
        localSocket9 = LocalSocketJNIHelper()

        localSocket1?.startSocket(SOCKET_ADDRESS)
        localSocket2?.startSocket(SOCKET_ADDRESS1)
        localSocket3?.startSocket(SOCKET_ADDRESS2)
        localSocket4?.startSocket(SOCKET_ADDRESS3)
        localSocket5?.startSocket(SOCKET_ADDRESS4)
        localSocket6?.startSocket(SOCKET_ADDRESS5)
        localSocket7?.startSocket(SOCKET_ADDRESS6)
        localSocket8?.startSocket(SOCKET_ADDRESS7)
        localSocket9?.startSocket(SOCKET_ADDRESS8)
    }

    override fun onDestroy() {
        super.onDestroy()
        localSocket1?.stopSocket()
        localSocket2?.stopSocket()
        localSocket3?.stopSocket()
        localSocket4?.stopSocket()
        localSocket5?.stopSocket()
        localSocket6?.stopSocket()
        localSocket7?.stopSocket()
        localSocket8?.stopSocket()
        localSocket9?.stopSocket()
    }
}