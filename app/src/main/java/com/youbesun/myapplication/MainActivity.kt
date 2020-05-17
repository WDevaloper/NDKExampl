package com.youbesun.myapplication

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import kotlinx.android.synthetic.main.activity_main.*
import kotlin.concurrent.thread
import androidx.core.app.ComponentActivity.ExtraData
import androidx.core.content.ContextCompat.getSystemService
import android.icu.lang.UCharacter.GraphemeClusterBreak.T
import org.fmod.FMOD


//adb connect 127.0.0.1:62001
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


        val bean = NDKTool.createBean()
        Log.e("tag", "JNI 返回对象：$bean")

        NDKTool.dynomicRegisterTest(3)
        NDKTool.dynomicRegisterTest2(6)
        NDKTool().dynomicRegisterTest3(999)


        NDKTool().testThread()


        val path = "file:///android_asset/opportunity_is_here.wav"
        FMOD.init(this)
        thread { NDKTool.fmodTest(path) }
    }


    fun printf() {
        Log.e("tag", "printf")
    }
}
