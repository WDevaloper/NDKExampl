#include <jni.h>
#include <string>
#include "Test.h"
#include <android/log.h>

#define LOG_TAG    "tag"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, ##__VA_ARGS__)

using namespace std;


extern "C"
JNIEXPORT jstring JNICALL
Java_com_youbesun_myapplication_NDKTool_test(JNIEnv *env, jclass clazz) {
    LOGE("%s", "ddddd");
    return env->NewStringUTF("Java_com_youbesun_myapplication_NDKTool_test");
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_youbesun_myapplication_NDKTool_stringFromJNI(JNIEnv *env, jclass clazz) {
    string hello = test();
    return env->NewStringUTF(hello.c_str());
}extern "C"
JNIEXPORT jint JNICALL
Java_com_youbesun_myapplication_NDKTool_getAppSecrect(JNIEnv *env, jclass clazz, jintArray int_arr,
                                                      jobjectArray str_arr, jint r) {


    jint *intArr = env->GetIntArrayElements(int_arr, NULL);
    jsize length = env->GetArrayLength(int_arr);

    for (int i = 0; i < length; i++) {
        LOGE("获取Java传来的数据：%d", *(intArr + i));
        *(intArr + i) = i + 2;
    }


    // 0(刷新Java数组，并释放c/c++数组),1（JNI_COMMIT 不释放），2（JNI_ABORT只是释放）
    env->ReleaseIntArrayElements(int_arr, intArr, 0);

    return 0;
}


//反射
extern "C"
JNIEXPORT void JNICALL
Java_com_youbesun_myapplication_NDKTool_parseObject(JNIEnv *env, jobject thiz, jobject bean) {


}