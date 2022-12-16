workspace "DrEngine"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "DrEngine"
    location "DrEngine"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "DE_PLATFORM_WINDOWS",
            "DE_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/".. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "DE_DEBUG"
        optimize "On"

    filter "configurations:Release"
        defines "DE_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "DE_DIST"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "DrEngine/src",
        "DrEngine/vendor/spdlog/include" 
    }

    links
    {
        "DrEngine"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "DE_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "DE_DEBUG"
        optimize "On"

    filter "configurations:Release"
        defines "DE_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "DE_DIST"
        optimize "On"

