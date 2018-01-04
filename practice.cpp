#include <dlfcn.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
    if (argc != 3)
        return EXIT_FAILURE;

    const char *libName = argv[1];
    const char *funcName = argv[2];

    cout << "library name : " << libName << endl;
    cout << "function name : " << funcName << endl;

    void *handle = dlopen(libName, RTLD_LAZY);

    if (handle == nullptr)
    {
        cout << dlerror() << endl;
        return EXIT_FAILURE;
    }

    void *pFunc = dlsym(handle, funcName);

    dlclose(handle);

    if (pFunc != nullptr)
    {
        cout << "OK" << endl;
        return EXIT_SUCCESS;
    }
    else
    {
        cout << "FAIL" << endl;
        return EXIT_FAILURE;
    }
}