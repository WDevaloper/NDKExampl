package com.youbesun.myapplication;

public class ZZTest<T> {
    private T calss;
    private String string;


    public void setCalss(T clazz) {
        this.calss = clazz;
    }

    private Bean a;

    public <A extends Bean> void setValue(A clazz) {
        this.a = clazz;

        Inner inner = new Inner();
        inner.a = 9;

    }


    public static void main(String[] args) {
        ZZTest zzTest = new ZZTest<String>();
        zzTest.setCalss("");
        zzTest.setValue(new Bean());


        final int a = 200;
        new Thread(new Runnable() {
            @Override
            public void run() {
                System.out.println(a);
            }
        });
    }


    class Inner {
        int a = 0;
    }
}
