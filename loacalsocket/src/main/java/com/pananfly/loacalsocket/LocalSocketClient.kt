package com.pananfly.loacalsocket

import android.net.LocalSocket
import android.net.LocalSocketAddress
import android.util.Log
import java.io.ByteArrayOutputStream
import java.util.concurrent.atomic.AtomicBoolean

class LocalSocketClient (private val address: String) : Runnable {
    private final val TAG = LocalSocketClient::class.java.simpleName
    private var mLocalSocket: LocalSocket = LocalSocket()
    private val isRunning: AtomicBoolean = AtomicBoolean(false)
    private val isConnect: AtomicBoolean = AtomicBoolean(false)

    fun start() {
        isRunning.set(true)
        isConnect.set(false)
        Thread(this).start()
    }

    fun stop() {
        isRunning.set(false)
        isConnect.set(true)
    }

    override fun run() {
        while (!isConnect.get() && isRunning.get()) {
            try {
                mLocalSocket.connect(LocalSocketAddress(address))
                isConnect.set(true)
                break
            } catch (e: Exception) {
                e.printStackTrace()
            }
            try {
                Thread.sleep(1)
            } catch (e: Exception) {
                e.printStackTrace()
            }
        }
        var bos = ByteArrayOutputStream()
        while(isRunning.get()) {
            try {
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