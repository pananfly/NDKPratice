package com.pananfly.loacalsocket

import android.app.Service
import android.content.Intent
import android.os.IBinder

const val SOCKET_ADDRESS: String = "com.pananfly.localsocket/test1"
class LocalSocketService : Service() {

    override fun onBind(p0: Intent?): IBinder? {
        TODO("Not yet implemented")
    }

    override fun onCreate() {
        super.onCreate()
        LocalSocketJNIHelper().startSocket(SOCKET_ADDRESS)
    }

    override fun onDestroy() {
        super.onDestroy()
        LocalSocketJNIHelper().stopSocket()
    }
}