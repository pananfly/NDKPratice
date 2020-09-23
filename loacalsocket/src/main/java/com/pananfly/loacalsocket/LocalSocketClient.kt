package com.pananfly.loacalsocket

import android.net.LocalSocket
import android.net.LocalSocketAddress
import android.util.Log
import java.io.ByteArrayOutputStream
import java.nio.ByteBuffer
import java.nio.charset.Charset
import java.util.concurrent.atomic.AtomicBoolean

class LocalSocketClient (private val address: String) : Runnable {
    private final val TAG = LocalSocketClient::class.java.simpleName
    private val HEAD = arrayOf('P'.toByte(), 'A'.toByte(), 'N'.toByte(),
        'S'.toByte(), 'O'.toByte(), 'C'.toByte(), 'K'.toByte(), 'E'.toByte(), 'T'.toByte(),
        'H'.toByte(), 'E'.toByte(), 'A'.toByte(), 'D'.toByte(), '0'.toByte(), '0'.toByte(), '0'.toByte())
    private val TAIL = arrayOf('P'.toByte(), 'A'.toByte(), 'N'.toByte(),
        'S'.toByte(), 'O'.toByte(), 'C'.toByte(), 'K'.toByte(), 'E'.toByte(), 'T'.toByte(),
        'T'.toByte(), 'A'.toByte(), 'I'.toByte(), 'L'.toByte(), '0'.toByte(), '0'.toByte(), '0'.toByte())
    private val PACK_OCCUPY_LEN = 4
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

    private fun int2Bytes(i: Int): ByteArray {
        val bytes = ByteArray(4)
        bytes[0] = ((i shr 24) and 0xFF).toByte()
        bytes[1] = ((i shr 16) and 0xFF).toByte()
        bytes[2] = ((i shr 8)  and 0xFF).toByte()
        bytes[3] = ( i         and 0xFF).toByte()
        return bytes
    }

    private fun bytes2Int(bytes: ByteArray): Int {
        return ByteBuffer.wrap(bytes, 0, 4).int
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
        val bytes = ByteArray(1024)
        var reachHead = false
        var reachTail = false
        var reachData = false
        var packageSize = 0
            while(isRunning.get()) {
            try {
//                Log.i(TAG, "Client address:$address rec msg start.")
                var readByte = mLocalSocket.inputStream.read(bytes)
                if(readByte != -1) {
                    bos.write(bytes, 0, readByte)
                    if(!reachHead && bos.size() >= HEAD.size) {
                        val cacheByte = bos.toByteArray()
                        for(index in cacheByte.indices) {
                            val headByte = cacheByte.copyOfRange(index, index + HEAD.size)
                            val headFound = headByte.contentEquals(HEAD.toByteArray())
                            if(!headFound && index + HEAD.size > cacheByte.size) {
                                break
                            }
                            if(!headFound) {
                                continue
                            }
                            reachHead = true
                            bos.reset()
                            bos.write(cacheByte, index + HEAD.size, cacheByte.size - index - HEAD.size)
                            break
                        }
                    }
                    if(reachHead && packageSize <= 0 && bos.size() > 4) {
                        val cacheByte = bos.toByteArray()
                        packageSize = bytes2Int(cacheByte)
                        bos.reset()
                        bos.write(cacheByte, PACK_OCCUPY_LEN, cacheByte.size - PACK_OCCUPY_LEN)
                    }
                    if(packageSize > 0 && bos.size() >= packageSize && !reachData) {
                        reachData = true
                        val cacheByte = bos.toByteArray()
                        Log.i(TAG, "Client address:$address rec msg: ${String(cacheByte, 0, packageSize, Charset.forName("utf-8"))}")
                        bos.reset()
                        bos.write(cacheByte, packageSize, cacheByte.size - packageSize)
                    }
                    if(reachHead && reachData && !reachTail && bos.size() >= TAIL.size) {
                        val cacheByte = bos.toByteArray()
                        for(index in cacheByte.indices) {
                            val headFound = cacheByte.copyOfRange(index, index + TAIL.size).contentEquals(TAIL.toByteArray())
                            if(!headFound && index + TAIL.size > cacheByte.size) {
                                break
                            }
                            if(!headFound) {
                                continue
                            }
                            reachTail = true
                            reachHead = false
                            reachData = false
                            packageSize = 0;
                            bos.reset()
                            bos.write(cacheByte, index + TAIL.size, cacheByte.size - index - TAIL.size)
                            break
                        }
                    }
                 }
//                var readByte = mLocalSocket.inputStream.read()
//                while(readByte != -1) {
//                    bos.write(readByte)
//                    if('\n'.toInt() == readByte) {
//                        Log.i(TAG, "Client address:$address rec msg: ${bos.toString("utf-8")}")
//                        break
//                    }
//                    readByte = mLocalSocket.inputStream.read()
//                }
            }catch (e: Exception) {
                e.printStackTrace()
            }
//            try {
//                Thread.sleep(1)
//            } catch (e: Exception) {
//                e.printStackTrace()
//            }

        }
        bos.reset()
        mLocalSocket.close()
    }
}