#include <pthread.h>

__thread int* tls_value = 0;

void* thread_func(void* arg)
{
    for (int i = 0; i < 1000000; i++);

    int g = 12222;
    tls_value = &g;
}

int* hello()
{
    pthread_t t;

    pthread_create(&t, NULL, thread_func, NULL);

    void* return_value;
    pthread_join(t, &return_value);
    return tls_value;
}
