# GmodLuaCompiler
[![License](https://img.shields.io/badge/license-MIT-green)](https://opensource.org/licenses/MIT)
[![App Version](https://img.shields.io/badge/version-v1.0-brightgreen)](https://github.com/Leystryku/gmodluacompiler)

A small C++ program which takes the Lua API from Garry's Mod and uses it compile Lua Files. This can be used to turn lua files into lua bytecode. It's compatible with x86/x64 versions of Windows and Linux. This is required lately because Garry's Mod now uses different versions of LuaJit across the different platforms.

# Showcase
none available

# Running
## Windows
Copy the following binaries from GMod to the directory of gmodluacompiler.exe
- lua_shared.dll
- tier0.dll
- vstdlib.dll

## Linux x86
Copy the following binaries from GMod to the directory of gmodluacompiler
- lua_shared_srv.so
- lua_shared.so
- libvstdlib_srv.so
- libvstdlib_s.so
- libvstdlib.so
- libsteam_api.so
- libtier0_srv.so

## Linux x64
Copy the following binaries from GMod to the directory of gmodluacompiler
- lua_shared.so
- libvstdlib.so
- libtier0.so
- libsteam_api.so


#### Troubleshooting
If it crashes with a MessageBox on startup install the VC++ 2019 redists from microsoft https://www.microsoft.com/.


# Compiling
If you wish to compile this yourself:

## Windows
- Run premake5 vs2019
- Open project/gmodluacompiler.sln
- Compile it using MSVC/MSVS

## Linux
- Run premake5 gmake
- Run cd project
- Run make help
- Run make help config=release_x86
(Or whatever platform your heart desires)

# Credits
- Leystryku (me)
  * Creating this project
- Garry's Mod & Valve
  * lua_shared and tier0 etc libraries
- Everyday A/S or HandsomeMatt
  * Inspirating me to recreate gluac because it was overcomplicated (sigscans+symbols,dependencies,...) & not portable enough