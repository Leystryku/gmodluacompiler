#include <cstdio>
#include <cstring>

#include "lua.h"

char inputFileName[0xFF] = { 0 };
char outputFileName[0xFF] = { 0 };

bool parseMode = true;
bool stripDebugMode = false;

static int LuaFunction(void *L)
{
    if (parseMode)
    {
        if (luaL_loadfile(L, inputFileName) != 0)
        {
            printf("luaL_loadfile: %s\n", lua_tostring(L, -1));
            return 0;
        }
        printf("Parsed file without any errors\n");
        return 0;
    }

    lua_getglobal(L, "string");
    lua_getfield(L, -1, "dump");

    if (luaL_loadfile(L, inputFileName) != 0)
    {
        printf("%s\n", lua_tostring(L, -1));
        return 0;
    }

    lua_pushboolean(L, stripDebugMode);

    if (lua_pcall(L, 2, 1, 0) != 0)
    {
        printf("%s\n", lua_tostring(L, -1));
        return 0;
    }

    int luaType = lua_type(L, -1);

    if (luaType != 4)
    {
        printf("string.dump returned wrong type %d\n", luaType); 
        return 0;       
    }

    size_t length = 0;
    const char *bytecode = lua_tolstring(L, -1, &length);

    if (length <= 0)
    {
        printf("Lua Bytecode Length must be over 1!\n");
        return 0;
    }

    printf("Compiled successfully: %zu bytes\n", length);

    FILE* handle = fopen(outputFileName, "wb");

    if (handle == nullptr)
    {
        printf("Could not create file %s\n", outputFileName);
        return 0;
    }
    
    fwrite(bytecode, length, 1, handle);
    fclose(handle);

    return 0;
}


int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("Arguments: inputFileName outputFileName stripDebugMode\"\n");
        printf("Not supplying a outputFileName will enable ParsingMode\n");
        return 1;
    }

    strcpy(inputFileName, argv[1]);

    if (argc > 2)
    {
        strcpy(outputFileName, argv[2]);

        parseMode = false;

        if (argc > 3) {
            stripDebugMode = argv[3][0] != '0';
        }
    }

    printf("Input: %s Output: %s ParsingMode: %d StripDebug: %d\n", inputFileName, outputFileName, (int)parseMode, (int)stripDebugMode);

    if (!InitializeLua((void*)LuaFunction))
    {
        printf("Error initializing Lua\n");
        return 1;
    }

    return 0;
}
