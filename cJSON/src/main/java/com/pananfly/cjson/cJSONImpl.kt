package com.pananfly.cjson

class cJSONImpl {
    companion object {
        init {
            System.loadLibrary("cJSON")
        }
    }

    external fun parseJSON()
}