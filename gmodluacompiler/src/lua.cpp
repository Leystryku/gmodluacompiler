#ifdef _WIN32
    #include <Windows.h>

    #define dlsym GetProcAddress
#else
    #include <dlfcn.h>
    #include <link.h>
#endif
#include <cstdio>

#include "lua.h"

lua_getfieldT lua_getfield = nullptr;
lua_pushbooleanT lua_pushboolean = nullptr;
lua_pcallT lua_pcall = nullptr;
lua_cpcallT lua_cpcall = nullptr;
lua_typeT lua_type = nullptr;
lua_tostringT lua_tostring = nullptr;
lua_tolstringT lua_tolstring = nullptr;
luaL_newstateT luaL_newstate = nullptr;
luaL_openlibsT luaL_openlibs = nullptr;
luaL_loadfileT luaL_loadfile = nullptr;


bool InitializeLuaResolveDependencies(
  #ifdef _WIN32
  HMODULE module
  #else
  void* module
  #endif
)
{
    *(void**)&lua_getfield = (void*)dlsym(module, "lua_getfield");
    *(void**)&lua_pushboolean = (void*)dlsym(module, "lua_pushboolean");
    *(void**)&lua_pcall = (void*)dlsym(module, "lua_pcall");
    *(void**)&lua_cpcall = (void*)dlsym(module, "lua_cpcall");
    *(void**)&lua_type = (void*)dlsym(module, "lua_type");
    *(void**)&lua_tostring = (void*)dlsym(module, "lua_tostring");
    *(void**)&lua_tolstring = (void*)dlsym(module, "lua_tolstring");
    *(void**)&luaL_newstate = (void*)dlsym(module, "luaL_newstate");
    *(void**)&luaL_openlibs = (void*)dlsym(module, "luaL_openlibs");
    *(void**)&luaL_loadfile = (void*)dlsym(module, "luaL_loadfile");

    return true;
}

bool InitializeLua(void *functionToCall)
{
#ifdef _WIN32
    HMODULE module = LoadLibrary(L"lua_shared.dll");
#else
#ifdef __x86_64__
    void *module = dlopen("lua_shared.so", RTLD_LAZY);
#else
    void *module = dlopen("lua_shared_srv.so", RTLD_LAZY);
#endif
#endif

    if (module == nullptr)
    {
        #ifdef _WIN32
            printf("Could not load lua_shared %d\n", GetLastError());
        #else
            printf("Could not load lua_shared %s\n", dlerror());
        #endif

        return false;
    }

    if (!InitializeLuaResolveDependencies(module))
    {
        return false;
    }
    void *L = luaL_newstate();
    luaL_openlibs(L);

    if (L == nullptr)
    {
        printf("cannot create lua state: not enough memory.\n");
        return false;
    }

    if (lua_cpcall(L, functionToCall, nullptr) != 0)
    {
        printf("lua_cpcall failed: %s\n", lua_tostring(L, -1));
        return false;
    }

    return true;
}