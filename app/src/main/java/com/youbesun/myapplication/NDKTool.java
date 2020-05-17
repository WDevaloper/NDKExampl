package com.youbesun.myapplication;

import android.util.Log;


public class NDKTool {
    static {
        System.loadLibrary("native-lib");
    }

    public static native String test();

    public static native String stringFromJNI();

    public static native int testArray(int[] int_arr, String[] str_arr);


    public native void cReflectJava(ReflectBean bean);

    public native void testThread();

    public native static ReflectBean createBean();


    public static native void dynomicRegisterTest(int a);

    public static native int dynomicRegisterTest2(int a);

    public native int dynomicRegisterTest3(int a);


    public static native void fmodTest(String path_);


    public void printf() {
        Log.e("tag", "NDKTool printf");
    }
}
