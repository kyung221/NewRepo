#include <dlfcn.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
    if (argc != 3)
        return EXIT_FAILURE;

    const char *library = argv[1];
    const char *symbol= argv[2];

    cout << "library name : " << library << endl;
    cout << "symbol name : " << symbol << endl;

    void *handle = dlopen(library, RTLD_LAZY);

    if (handle == nullptr)
    {
        cout << dlerror() << endl;
        return EXIT_FAILURE;
    }

    void *pFunc = dlsym(handle, symbol);

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