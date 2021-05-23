solution "gmodluacompiler"
   language "C++"
   location "project"
   targetdir "build/"

   flags { "NoMinimalRebuild", "NoBufferSecurityCheck"}

   symbols "On"
   optimize "On"
   staticruntime "On"
   omitframepointer "On"
   vectorextensions "SSE2"
   floatingpoint "Fast"

   if os.istarget("linux") or os.istarget("macosx") then
      buildoptions {"-fPIC"}
      linkoptions  {"-ldl -lstdc++"}
      links { "dl" }
   end

   vpaths {
      ["Header Files/*"] = "src/**.h",
      ["Source Files/*"] = "src/**.cpp",
   }

   kind "ConsoleApp"

   configurations { "Debug", "Release" }
   platforms { "x32", "x86_64"}
   files { "src/**.h", "src/**.cpp" }

   project "gmodluacompiler"
      targetname "gmodluacompiler"

      configuration "Release"
         defines { "_CRT_SECURE_NO_WARNINGS", "NDEBUG" }
         symbols "Off"
         targetdir "build/release"

      configuration "Debug"
         defines { "_CRT_SECURE_NO_WARNINGS", "DEBUG" }
         optimize "Off"
         targetdir "build/debug"