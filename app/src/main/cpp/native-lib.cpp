#include <jni.h>
#include <string>
#include "Test.h"
#include <android/log.h>

using namespace std;




extern "C"
JNIEXPORT jstring JNICALL
Java_com_youbesun_myapplication_NDKTool_test(JNIEnv *env, jclass clazz) {
    return env->NewStringUTF("Java_com_youbesun_myapplication_NDKTool_test");
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_youbesun_myapplication_NDKTool_stringFromJNI(JNIEnv *env, jclass clazz) {
    string hello = test();
    return env->NewStringUTF(hello.c_str());
}