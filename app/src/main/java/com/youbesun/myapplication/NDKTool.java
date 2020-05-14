package com.youbesun.myapplication;

public class NDKTool {
    static {
        System.loadLibrary("native-lib");
    }

    public static native String test();

    public static native String stringFromJNI();

}
