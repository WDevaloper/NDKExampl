//
// Created by admin on 2020/5/21.
//
#include <android/log.h>
#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR,"tag",FORMAT,##__VA_ARGS__);


int demo() {
    LOGE("%s",">>>>>>>>>>>>demo")
    return 0;
}