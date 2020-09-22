package com.pananfly.loacalsocket

import android.content.Intent
import android.os.Bundle
import android.os.Handler
import androidx.appcompat.app.AppCompatActivity
import java.io.File
import java.lang.Exception

class LocalSocketActivity : AppCompatActivity() {
    val client: LocalSocketClient = LocalSocketClient(SOCKET_ADDRESS)
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.localsocket_main)
//        val client: LocalSocketClient = LocalSocketClient("123")
//        val server: LocalSocketServer = LocalSocketServer("123")
//        val client2: LocalSocketClient = LocalSocketClient("666")
//        val server2: LocalSocketServer = LocalSocketServer("666")
//        server.start()
//        client.start()
//        server2.start()
//        client2.start()
//        Handler().postDelayed(Runnable {
//            client.stop()
//            server.stop()
//            client2.stop()
//            server2.stop()
//
//        }, 5000 )

        client.start()
        startSocketService()
    }

    override fun onDestroy() {
        super.onDestroy()
        client.stop()
        stopSocketService()
    }

    fun startSocketService() {
        try {
            startService(Intent(this, LocalSocketService::class.java))
        } catch (e: Exception) {
            e.printStackTrace()
        }
    }

    fun stopSocketService() {
        try {
            stopService(Intent(this, LocalSocketService::class.java))
        } catch (e: Exception) {
            e.printStackTrace()
        }
    }
}