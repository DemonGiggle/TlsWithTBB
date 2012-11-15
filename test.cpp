#include <stdlib.h>
#include <dlfcn.h>

int main()
{
    int* (*hello)();

    void* handle = dlopen("./libshared.so", RTLD_LAZY);
    *(void**)(&hello) = dlsym(handle, "_Z5hellov");

    hello();
    dlclose(handle);
    return 0;
}
