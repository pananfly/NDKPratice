package com.pananfly.cjson

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity

class CJSONActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val c: cJSONImpl = cJSONImpl()
        c.parseJSON()
    }
}