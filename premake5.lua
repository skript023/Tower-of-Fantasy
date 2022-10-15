workspace "tower-of-fantasy"
  architecture "x64"
  startproject "tower-of-fantasy"

  configurations
  {
    "Release"
  }

  outputdir = "%{cfg.buildcfg}"

  IncludeDir = {}
  IncludeDir["json"] = "vendor/json/single_include"
  IncludeDir["MinHook"] = "vendor/MinHook/include"
  IncludeDir["ImGui"] = "vendor/imgui"
  IncludeDir["ImGuiImpl"] = "vendor/imgui/examples"
  IncludeDir["StackWalker"] = "vendor/StackWalker/Main/StackWalker"
  
  CppVersion = "C++20"
  MsvcToolset = "v143"
  WindowsSdkVersion = "10.0"
  
  function DeclareMSVCOptions()
    filter "system:windows"
    staticruntime "Off"
	floatingpoint "Fast"
	vectorextensions "AVX2"
    systemversion (WindowsSdkVersion)
    toolset (MsvcToolset)
    cppdialect (CppVersion)

    defines
    {
      "_CRT_SECURE_NO_WARNINGS",
      "NOMINMAX",
      "WIN32_LEAN_AND_MEAN",
      "_WIN32_WINNT=0x601" -- Support Windows 7
    }
    
    disablewarnings
    {
      "4100", -- C4100: unreferenced formal parameter
      "4201", -- C4201: nameless struct/union
      "4307",  -- C4307: integral constant overflow
      "4996"  -- C4996: deprecated in C++17
    }
  end
  
  function file_exists(name)
   local f=io.open(name,"r")
   if f~=nil then io.close(f) return true else return false end
  end
   
  function DeclareDebugOptions()
    filter "configurations:Debug"
      defines { "_DEBUG" }
      symbols "On"
    filter "not configurations:Debug"
      defines { "NDEBUG" }
  end
   
  project "imgui"
    location "vendor/%{prj.name}"
    kind "StaticLib"
    language "C++"

    targetdir ("bin/lib/" .. outputdir)
    objdir ("bin/lib/int/" .. outputdir .. "/%{prj.name}")
    
    files
    {
      "vendor/%{prj.name}/imgui.cpp",
      "vendor/%{prj.name}/imgui_demo.cpp",
      "vendor/%{prj.name}/imgui_draw.cpp",
      "vendor/%{prj.name}/imgui_tables.cpp",
      "vendor/%{prj.name}/imgui_widgets.cpp",
      "vendor/%{prj.name}/backends/imgui_impl_dx11.cpp",
      "vendor/%{prj.name}/backends/imgui_impl_win32.cpp"
    }

    includedirs
    {
      "vendor/%{prj.name}"
    }

    DeclareMSVCOptions()
    DeclareDebugOptions()

  project "MinHook"
      location "vendor/%{prj.name}"
      kind "StaticLib"
      language "C"

      targetdir ("bin/lib/" .. outputdir)
      objdir ("bin/lib/int/" .. outputdir .. "/%{prj.name}")

      files
      {
        "vendor/%{prj.name}/include/**.h",
        "vendor/%{prj.name}/src/**.h",
        "vendor/%{prj.name}/src/**.c"
      }

      DeclareMSVCOptions()
      DeclareDebugOptions()

  project "StackWalker"
    location "vendor/%{prj.name}"
    kind "StaticLib"
    language "C++"
  
    targetdir ("bin/lib/" .. outputdir)
    objdir ("bin/lib/int/" .. outputdir .. "/%{prj.name}")

    files
    {
      "vendor/%{prj.name}/Main/StackWalker/StackWalker.cpp"
    }

    includedirs
    {
      "vendor/%{prj.name}/include"
    }

    DeclareMSVCOptions()
    DeclareDebugOptions()

  project "tower-of-fantasy"
    location "tower-of-fantasy"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir)
    objdir ("bin/int/" .. outputdir .. "/%{prj.name}")

    PrecompiledHeaderInclude = "common.hpp"
    PrecompiledHeaderSource = "%{prj.name}/src/common.cpp"
 
    files
    {
      "%{prj.name}/src/**.hpp",
      "%{prj.name}/src/**.h",
      "%{prj.name}/src/**.cpp",
      "%{prj.name}/src/**.asm"
    }

    includedirs
    {
      "%{IncludeDir.json}",
      "%{IncludeDir.MinHook}",
      "%{IncludeDir.ImGui}",
      "%{IncludeDir.ImGuiImpl}",
      "%{IncludeDir.StackWalker}",
      "%{prj.name}/src"
    }

    libdirs
    {
      "bin/lib"
    }

    links
    {
      "MinHook",
      "ImGui",
      "StackWalker"
    }

    pchheader "%{PrecompiledHeaderInclude}"
    pchsource "%{PrecompiledHeaderSource}"

    forceincludes
    {
      "%{PrecompiledHeaderInclude}"
    }

    DeclareMSVCOptions()
    DeclareDebugOptions()

    flags { "NoImportLib", "Maps" }

    filter "configurations:Release"
	  flags { "LinkTimeOptimization", "NoManifest", "MultiProcessorCompile" }
      defines { "ScarletNexus_RELEASE" }
      optimize "speed"