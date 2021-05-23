#ifndef _LUA_H
#define _LUA_H
#pragma once
#ifndef _WIN32
#define __cdecl
#endif

typedef int (__cdecl *lua_getfieldT) (void *L, int index, const char *key);
typedef int (__cdecl *lua_pushbooleanT) (void *L, bool value);
typedef int (__cdecl *lua_pcallT) (void *L, int in, int out, void* errorfn);
typedef int (__cdecl *lua_cpcallT) (void *L, void* cfunction, void* errorfn);
typedef int (__cdecl *lua_typeT) (void *L, int index);
typedef const char* (__cdecl *lua_tostringT) (void *L, int index);
typedef const char* (__cdecl *lua_tolstringT) (void *L, int index, size_t *outLen);
typedef void* (__cdecl *luaL_newstateT) ();
typedef int (__cdecl *luaL_openlibsT) (void *L);
typedef int (__cdecl *luaL_loadfileT) (void *L, const char *filename);

extern lua_getfieldT lua_getfield;
extern lua_pushbooleanT lua_pushboolean;
extern lua_pcallT lua_pcall;
extern lua_cpcallT lua_cpcall;
extern lua_typeT lua_type;
extern lua_tostringT lua_tostring;
extern lua_tolstringT lua_tolstring;
extern luaL_newstateT luaL_newstate;
extern luaL_openlibsT luaL_openlibs;
extern luaL_loadfileT luaL_loadfile;

#define LUA_GLOBALSINDEX	(-10002)
#define lua_getglobal(L,s)	lua_getfield(L, LUA_GLOBALSINDEX, (s))

bool InitializeLua(void *functionToCall);
#endif