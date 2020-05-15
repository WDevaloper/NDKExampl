package com.youbesun.myapplication;


public class ReflectBean {
    private String name;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return "ReflectBean{" +
                "name=" + name +
                '}';
    }
}
