package com.pananfly.loacalsocket

import android.content.Intent
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.pananfly.loacalsocket.service.*
import java.io.File
import java.lang.Exception

class LocalSocketActivity : AppCompatActivity() {
    var client: LocalSocketClient? = null
    var client2: LocalSocketClient? = null
    var client3: LocalSocketClient? = null
    var client4: LocalSocketClient? = null
    var client5: LocalSocketClient? = null
    var client6: LocalSocketClient? = null
    var client7: LocalSocketClient? = null
    var client8: LocalSocketClient? = null
    var client9: LocalSocketClient? = null
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.localsocket_main)
        client = LocalSocketClient(SOCKET_ADDRESS, File(this.externalCacheDir?.absolutePath, "client1.txt") .apply {  if(!this.exists()) {  this.parentFile?.mkdirs(); this.createNewFile() } })
        client2 = LocalSocketClient(SOCKET_ADDRESS1, File(this.externalCacheDir?.absolutePath, "client2.txt") .apply {  if(!this.exists()) {  this.parentFile?.mkdirs(); this.createNewFile() } })
        client3 = LocalSocketClient(SOCKET_ADDRESS2, File(this.externalCacheDir?.absolutePath, "client3.txt") .apply {  if(!this.exists()) {  this.parentFile?.mkdirs(); this.createNewFile() } })
        client4 = LocalSocketClient(SOCKET_ADDRESS3, File(this.externalCacheDir?.absolutePath, "client4.txt") .apply {  if(!this.exists()) {  this.parentFile?.mkdirs(); this.createNewFile() } })
        client5 = LocalSocketClient(SOCKET_ADDRESS4, File(this.externalCacheDir?.absolutePath, "client5.txt") .apply {  if(!this.exists()) {  this.parentFile?.mkdirs(); this.createNewFile() } })
        client6 = LocalSocketClient(SOCKET_ADDRESS5, File(this.externalCacheDir?.absolutePath, "client6.txt") .apply {  if(!this.exists()) {  this.parentFile?.mkdirs(); this.createNewFile() } })
        client7 = LocalSocketClient(SOCKET_ADDRESS6, File(this.externalCacheDir?.absolutePath, "client7.txt") .apply {  if(!this.exists()) {  this.parentFile?.mkdirs(); this.createNewFile() } })
        client8 = LocalSocketClient(SOCKET_ADDRESS7, File(this.externalCacheDir?.absolutePath, "client8.txt") .apply {  if(!this.exists()) {  this.parentFile?.mkdirs(); this.createNewFile() } })
        client9 = LocalSocketClient(SOCKET_ADDRESS8, File(this.externalCacheDir?.absolutePath, "client9.txt") .apply {  if(!this.exists()) {  this.parentFile?.mkdirs(); this.createNewFile() } })

        client?.start()
        client2?.start()
        client3?.start()
        client4?.start()
        client5?.start()
        client6?.start()
        client7?.start()
        client8?.start()
        client9?.start()
        startSocketService()
    }

    override fun onDestroy() {
        super.onDestroy()
        client?.stop()
        client2?.stop()
        client3?.stop()
        client4?.stop()
        client5?.stop()
        client6?.stop()
        client7?.stop()
        client8?.stop()
        client9?.stop()
        stopSocketService()
    }

    fun startSocketService() {
        try {
            startService(Intent(this, LocalSocketService::class.java))
        } catch (e: Exception) {
            e.printStackTrace()
        }
//        try {
//            startService(Intent(this, LocalSocketService2::class.java))
//        } catch (e: Exception) {
//            e.printStackTrace()
//        }
    }

    fun stopSocketService() {
        try {
            stopService(Intent(this, LocalSocketService::class.java))
        } catch (e: Exception) {
            e.printStackTrace()
        }
    }
}