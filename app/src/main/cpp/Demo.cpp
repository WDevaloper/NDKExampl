//
// Created by admin on 2020/5/21.
//
#include <android/log.h>

#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR,"tag",FORMAT,##__VA_ARGS__);

#include <queue>
#include <pthread.h>

using namespace std;


int demo() {
    LOGE("%s", ">>>>>>>>>>>>demo")
    return 0;
}


template<typename T>
class SafeQueue {
public:
    SafeQueue() {
        pthread_mutex_init(&mutex, 0);
        pthread_cond_init(&cond, 0);
    }

    ~SafeQueue() {
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);
    }

    void eneueue(T value) {
        pthread_mutex_lock(&mutex);
        q.push(value);

        pthread_cond_signal(&cond);

        pthread_mutex_unlock(&mutex);
    }


    void pop(T &value) {
        pthread_mutex_lock(&mutex);

        while (q.empty()) {
            pthread_cond_wait(&cond, 0);
        }

        if (!q.empty()) {

        }

        pthread_mutex_unlock(&mutex);
    }

private:
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    queue<T> q;
};