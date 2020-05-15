#include <jni.h>
#include <string>
#include <cstring>
#include "Test.h"
#include <android/log.h>

using namespace std;

#define LOGI(FORMAT, ...) __android_log_print(ANDROID_LOG_INFO,"tag",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR,"tag",FORMAT,##__VA_ARGS__);
#define LOGD(FORMAT, ...) __android_log_print(ANDROID_LOG_DEBUG,"tag",FORMAT,##__VA_ARGS__);
#define LOGV(FORMAT, ...) __android_log_print(ANDROID_LOG_VERBOSE,"tag",FORMAT,##__VA_ARGS__);


extern "C"
JNIEXPORT jstring JNICALL
Java_com_youbesun_myapplication_NDKTool_test(JNIEnv *env, jclass clazz) {
    return env->NewStringUTF("Java_com_youbesun_myapplication_NDKTool_test");
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_youbesun_myapplication_NDKTool_stringFromJNI(JNIEnv *env, jclass clazz) {
    string hello = test();
    LOGE("%s", hello.c_str());
    return env->NewStringUTF(hello.c_str());
}


extern "C"
JNIEXPORT jint JNICALL
Java_com_youbesun_myapplication_NDKTool_testArray(JNIEnv *env,
                                                  jclass thisCls, //不是静态方法就是jobject，即表示调用者；如果是静态方法就是jclass，不过都是定义方法本身
                                                  jintArray int_arr,
                                                  jobjectArray str_arr) {


    const jsize intArrLength = env->GetArrayLength(int_arr);

    jint *pInt = env->GetIntArrayElements(int_arr, NULL);

    for (int i = 0; i < intArrLength; i++) {
        LOGE("JNI输出数组元素：%d", *(pInt + i));
        *(pInt + i) += 10;//修改数组数据是否同步Java，就需要model指定了
    }

    // JNI申请的内存都在Native Memory中
    //参数3: 0表示刷新Java数组并释放C/C++层内存，1(JNI_COMMIT)表示只刷新不释放,2只释放
    env->ReleaseIntArrayElements(int_arr, pInt, 0);

    //====================操作字符串数组



    jsize str_length = env->GetArrayLength(str_arr);
    //获得字符串数组的数据,操作除了基本数据类型之外的这种方式都可以
    for (int i = 0; i < str_length; ++i) {
        const jobject pJobject = env->GetObjectArrayElement(str_arr, i);
        //强转
        const jstring str = static_cast<jstring>(pJobject);

        const char *c_str = env->GetStringUTFChars(str, 0);
        LOGE("字符串有:%s", c_str);
        //使用完释放
        env->ReleaseStringUTFChars(str, c_str);
    }

    return 0;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_youbesun_myapplication_NDKTool_cReflectJava(
        JNIEnv *env,
        jobject thiz, //非静态方法，就是方法定义本身对象
        jobject bean) {


    jclass pJclass = env->GetObjectClass(thiz);
    jmethodID methodId = env->GetMethodID(pJclass, "printf", "()V");
    env->CallVoidMethod(thiz, methodId);






}