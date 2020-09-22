package com.pananfly.loacalsocket

import android.net.LocalServerSocket
import android.net.LocalSocket
import android.net.LocalSocketAddress
import android.util.Log
import java.lang.StringBuilder
import java.util.concurrent.atomic.AtomicBoolean

class LocalSocketServer (private val address: String) : Runnable {
    private final val TAG = LocalSocketServer::class.java.simpleName
    private var mLocalServerSocket: LocalServerSocket = LocalServerSocket(address)
    private val isRunning: AtomicBoolean = AtomicBoolean(false)

    fun start() {
        isRunning.set(true)
        Thread(this).start()
    }

    fun stop() {
        isRunning.set(false)
    }

    override fun run() {
        var localSocket: LocalSocket? = null
        try {
            localSocket = mLocalServerSocket.accept()
            localSocket.receiveBufferSize = 1024 * 1024
            localSocket.sendBufferSize = 1024 * 1024
        } catch (e: Exception) {
            e.printStackTrace()
        }
        while(isRunning.get()) {
            try {
//                val bytes = ByteArray(100)
//                val read = localSocket?.inputStream?.read(bytes)
//                val str = read?.let { String(bytes, 0 , it) }
//                Log.i(TAG, "Server rec msg: $str")
                localSocket?.outputStream?.write("Server msg $address\n".toByteArray())
                Thread.sleep(1)
            }catch (e: Exception) {
                e.printStackTrace()
            }
        }
        localSocket?.close()
    }
}