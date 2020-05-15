#include <jni.h>
#include <string>
#include <cstring>
#include "Test.h"
#include <iostream>
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
        jobject thiz, //非静态方法，就是方法定义本身对象NDKTool的对象
        jobject bean) {


    //NDKTool
    jclass pJclass = env->GetObjectClass(thiz);
    jmethodID methodId = env->GetMethodID(pJclass, "printf", "()V");
    env->CallVoidMethod(thiz, methodId);

    jclass beanCls = env->GetObjectClass(bean);


    //反射setName方法
    jmethodID setMethodId = env->GetMethodID(beanCls, "setName", "(Ljava/lang/String;)V");
    jstring pJstring = env->NewStringUTF("999999");
    //调用setName方法
    env->CallVoidMethod(bean, setMethodId, pJstring);

    jmethodID getMethodId = env->GetMethodID(beanCls, "getName", "()Ljava/lang/String;");
    //调用getName方法
    jobject getMethodRes = env->CallObjectMethod(bean, getMethodId);
    //将jbject转换为jstring
    jstring pJobject = static_cast<jstring>(getMethodRes);

    const char *utfChars = env->GetStringUTFChars(pJobject, NULL);
    LOGE("get返回值：%s", utfChars);


    // 静态方法
    jmethodID staticMethodId = env->GetStaticMethodID(beanCls, "setAddress",
                                                      "()Ljava/lang/String;");
    jobject staticMethodVal = env->CallStaticObjectMethod(beanCls, staticMethodId);
    jstring staticMethodValStr = static_cast<jstring>(staticMethodVal);
    const char *chars = env->GetStringUTFChars(staticMethodValStr, NULL);
    LOGE("静态方法返回：%s", chars)


    //对象Field
    jfieldID pJfieldId = env->GetFieldID(beanCls, "name", "Ljava/lang/String;");
    jstring filedStr = env->NewStringUTF("reflect filed");
    env->SetObjectField(bean, pJfieldId, filedStr);

    //静态Filed
    jfieldID staticFieldId = env->GetStaticFieldID(beanCls, "address", "Ljava/lang/String;");
    jstring staticFiledStr = env->NewStringUTF("static reflect filed");
    env->SetStaticObjectField(beanCls, staticFieldId, staticFiledStr);


    env->DeleteLocalRef(beanCls);
    env->DeleteLocalRef(pJclass);
    env->DeleteLocalRef(pJstring);
}


//创建对象
extern "C"
JNIEXPORT jobject JNICALL
Java_com_youbesun_myapplication_NDKTool_createBean(JNIEnv *env, jclass thiz) {
    const char *clsName = "com/youbesun/myapplication/ReflectBean";
    jclass refCls = env->FindClass(clsName);
    jmethodID construct = env->GetMethodID(refCls, "<init>", "()V");
    jobject refObject = env->NewObject(refCls, construct);

    env->DeleteLocalRef(refCls);
    return refObject;
}