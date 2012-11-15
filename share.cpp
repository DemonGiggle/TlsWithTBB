#include <pthread.h>
#include <tbb/enumerable_thread_specific.h>

struct thread_st
{
    int value;
};

typedef tbb::enumerable_thread_specific<thread_st> tbb_tls;
tbb_tls per_thread_data;

void* thread_func(void* arg)
{
    for (int i = 0; i < 1000000; i++);

    tbb_tls::reference thread_data = per_thread_data.local();
    thread_data.value = 3;
}

int* hello()
{
    pthread_t t;

    pthread_create(&t, NULL, thread_func, NULL);

    void* return_value;
    pthread_join(t, &return_value);
    return NULL;
}
