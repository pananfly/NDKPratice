package com.pananfly.loacalsocket

import android.net.LocalSocket
import android.net.LocalSocketAddress
import android.util.Log
import java.io.BufferedOutputStream
import java.io.ByteArrayOutputStream
import java.io.OutputStream
import java.lang.StringBuilder
import java.nio.ByteBuffer
import java.util.concurrent.atomic.AtomicBoolean

class LocalSocketClient (private val address: String) : Runnable {
    private final val TAG = LocalSocketClient::class.java.simpleName
    private var mLocalSocket: LocalSocket = LocalSocket()
    private val isRunning: AtomicBoolean = AtomicBoolean(false)

    fun start() {
        isRunning.set(true)
        Thread(this).start()
    }

    fun stop() {
        isRunning.set(false)
    }

    override fun run() {
        try {
            mLocalSocket.connect(LocalSocketAddress(address))
        } catch (e: Exception) {
            e.printStackTrace()
        }
        var bos = ByteArrayOutputStream()
        while(isRunning.get()) {
            try {
//                val bytes = ByteArray(100)
//                val read = mLocalSocket.inputStream.read(bytes)
//                val str = String(bytes, 0 , read)
//                Log.i(TAG, "Client rec msg: $str")
                bos.reset()
                var readByte = mLocalSocket.inputStream.read()
                while(readByte != -1) {
                    bos.write(readByte)
                    if('\n'.toInt() == readByte) {
                        Log.i(TAG, "Client rec msg: ${bos.toString("utf-8")}")
                        break
                    }
                    readByte = mLocalSocket.inputStream.read()
                }
            }catch (e: Exception) {
                e.printStackTrace()
            }

        }
        bos.reset()
        mLocalSocket.close()
    }
}