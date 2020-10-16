package com.pananfly.loacalsocket

import android.net.LocalSocket
import android.net.LocalSocketAddress
import android.os.Environment
import android.util.Log
import java.io.BufferedOutputStream
import java.io.ByteArrayOutputStream
import java.io.File
import java.io.FileOutputStream
import java.nio.ByteBuffer
import java.nio.charset.Charset
import java.util.concurrent.atomic.AtomicBoolean

class LocalSocketClient (private val address: String, private val bufFile: File) : Runnable {
    private final val TAG = LocalSocketClient::class.java.simpleName
    private val HEAD = arrayOf('P'.toByte(), 'A'.toByte(), 'N'.toByte(),
        'S'.toByte(), 'O'.toByte(), 'C'.toByte(), 'K'.toByte(), 'E'.toByte(), 'T'.toByte(),
        'H'.toByte(), 'E'.toByte(), 'A'.toByte(), 'D'.toByte(), '0'.toByte(), '0'.toByte(), '0'.toByte())
    private val TAIL = arrayOf('P'.toByte(), 'A'.toByte(), 'N'.toByte(),
        'S'.toByte(), 'O'.toByte(), 'C'.toByte(), 'K'.toByte(), 'E'.toByte(), 'T'.toByte(),
        'T'.toByte(), 'A'.toByte(), 'I'.toByte(), 'L'.toByte(), '0'.toByte(), '0'.toByte(), '0'.toByte())
    private val PACKAGE_OCCUPY_LEN = 4
    private var mLocalSocket: LocalSocket? = null
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
        mLocalSocket = LocalSocket()
        while (!isConnect.get() && isRunning.get()) {
            try {
                mLocalSocket?.connect(LocalSocketAddress(address))

                Log.i(TAG, "Client buffer rec size: ${mLocalSocket?.receiveBufferSize}, send size: ${mLocalSocket?.sendBufferSize}.")
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
        val fos = FileOutputStream(bufFile)
        val fbos = BufferedOutputStream(fos)
        var bos = ByteArrayOutputStream()
        val bytes = ByteArray(1024)
        var reachHead = false
        var reachTail = false
        var reachData = false
        var packageSize = 0
        while(isRunning.get()) {
            try {
                var readByte = mLocalSocket?.inputStream?.read(bytes) ?: 0
                if(readByte != -1) {
                    bos.write(bytes, 0, readByte)
                    val cacheByte = bos.toByteArray()
                    var bIndex = 0
                    var bSize = cacheByte.size
                    while (bIndex + HEAD.size <= bSize) {
                        // find head
                        if(!reachHead && bSize - bIndex >= HEAD.size) {
                            for(index in bIndex until bSize) {
                                val found = cacheByte.copyOfRange(index, index + HEAD.size).contentEquals(HEAD.toByteArray())
                                Log.i(TAG, "Client find head :$address.")
                                if(!found && index + HEAD.size > bSize) {
                                    break
                                }
                                if(!found) {
                                    continue
                                }
                                reachHead = true
                                reachTail = false
                                reachData = false
                                packageSize = 0
                                bIndex = index + HEAD.size;
                                Log.i(TAG, "Client address:$address rec msg reach head.")
                                break
                            }
                        }
                        // get package size
                        if(reachHead && !reachTail && !reachData && packageSize <= 0 && bSize - bIndex >= PACKAGE_OCCUPY_LEN) {
                            packageSize = bytes2Int(cacheByte.copyOfRange(bIndex, bIndex + PACKAGE_OCCUPY_LEN))
                            bIndex += PACKAGE_OCCUPY_LEN
                            Log.i(TAG, "Client address:$address rec msg reach size: $packageSize.")
                        }
                        if(packageSize > 0 && !reachData) {
                            // enough data
                            if(bSize - bIndex >= packageSize + TAIL.size) {
                                // find tail to confirm package receive finish
                                var tailIndex = bIndex
                                if(reachHead && !reachTail && bSize - bIndex - packageSize >= TAIL.size) {
                                    for(index in bIndex + packageSize until bSize) {
                                        Log.i(TAG, "Client find tail :$address.")
                                        val found = cacheByte.copyOfRange(index, index + TAIL.size).contentEquals(TAIL.toByteArray())
                                        if(!found && index + TAIL.size > bSize) {
                                            break
                                        }
                                        if(!found) {
                                            continue
                                        }
                                        reachHead = false
                                        reachTail = true
                                        tailIndex = index
                                        Log.i(TAG, "Client address:$address rec msg reach tail.")
                                        break
                                    }
                                }
                                if(reachTail) {
                                    reachData = true

//                                    try {
//                                        fbos.write(int2Bytes(packageSize))
//                                        fbos.write('\n'.toInt())
//                                        fbos.write(cacheByte, bIndex, packageSize)
//                                        fbos.write('\n'.toInt())
//                                    } catch (e: Exception) {
//                                        e.printStackTrace()
//                                    }
                                    Log.i(TAG, "Client address:$address rec msg size: $packageSize, data:")
                                    packageSize = 0
                                    bIndex = tailIndex + TAIL.size
                                 }
                            } else {
                                // data not receive enough.
                                break
                            }
                        }
                    }
                    bos.reset()
                    if(bIndex <= bSize) {
                        bos.write(cacheByte, bIndex, bSize - bIndex)
                    }
                 }
            }catch (e: Exception) {
                e.printStackTrace()
            }

        }
        try {
            fbos.close()
        } catch (e: Exception) {
            e.printStackTrace()
        }
        try {
            fos.close()
        } catch (e: Exception) {
            e.printStackTrace()
        }
        bos.reset()
        mLocalSocket?.close()
        mLocalSocket = null
    }
}