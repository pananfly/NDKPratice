package com.pananfly.loacalsocket

import android.os.Bundle
import android.os.Handler
import androidx.appcompat.app.AppCompatActivity

class LocalSocketActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.localsocket_main)
        val client: LocalSocketClient = LocalSocketClient("123")
        val server: LocalSocketServer = LocalSocketServer("123")
        server.start()
        client.start()
        Handler().postDelayed(Runnable {
            client.stop()
            server.stop()
        }, 5000* 100 )
    }
}