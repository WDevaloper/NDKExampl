package com.youbesun.myapplication;

import java.util.List;

public class NDKTool {
    static {
        System.loadLibrary("native-lib");
    }

    public static native String test();

    public static native String stringFromJNI();


    public static native int getAppSecrect(int[] intArr, String[] strArr,int r);
    native void parseObject(Bean bean);
}
