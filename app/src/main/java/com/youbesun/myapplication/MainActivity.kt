package com.youbesun.myapplication

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        sample_text.text = NDKTool.stringFromJNI()
        sample_text2.text = NDKTool.test()


        val r = 9;
        val intArrayOf = intArrayOf(1, 2, 3, 4)
        NDKTool.getAppSecrect(intArrayOf, arrayOf("", ""),r)
        intArrayOf.forEach {
            Log.e("tag", "$it---r:$r")
        }
    }
}
