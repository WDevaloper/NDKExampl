//
// Created by admin on 2020/5/21.
//

#include "NewTest.h"
#include <android/log.h>

#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR,"tag",FORMAT,##__VA_ARGS__);

int Test::newTest() {

    LOGE("%s", "newTest");

    return 0;
}