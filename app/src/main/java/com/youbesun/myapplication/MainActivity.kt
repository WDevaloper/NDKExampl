package com.youbesun.myapplication

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import kotlinx.android.synthetic.main.activity_main.*
import java.sql.Ref

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        sample_text.text = NDKTool.stringFromJNI()
        sample_text2.text = NDKTool.test()

        val intArr = intArrayOf(1, 2, 3, 4)
        val strArr = arrayOf("asc", "abc")
        NDKTool.testArray(intArr, strArr)


        intArr.forEach { Log.e("tag", "Java数组输出:$it") }


        val reflectBean = ReflectBean()
        NDKTool().cReflectJava(reflectBean)
        Log.e("tag", "$reflectBean")
    }


    fun printf() {
        Log.e("tag", "printf")
    }
}
