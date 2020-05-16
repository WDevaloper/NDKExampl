package com.youbesun.myapplication;


import android.util.Log;

public class ReflectBean {
    private String name="origin";
    private static String address = "cd";


    public ReflectBean() {
        Log.e("tag", "ReflectBean");
    }

    public ReflectBean(int a, String b) {
        Log.e("tag", "ReflectBean");
    }

    private static String setAddress() {
        Log.e("tag", "setAddress");
        return "setAddress";
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return "ReflectBean{" +
                "name=\'" + name + "\'" + "address='" + address + "\'" + '}';
    }
}
