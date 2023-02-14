workspace "DrEngine"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

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
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/vendor/SDL2/include",
        "%{prj.name}/vendor/SDL2_ttf/include",
        "%{prj.name}/vendor/SDL2_image/include",
        "%{prj.name}/vendor/SDL2_mixer/include"
    }

    libdirs
    {
        "%{prj.name}/vendor/SDL2/lib/x64",
        "%{prj.name}/vendor/SDL2_ttf/lib/x64/",
        "%{prj.name}/vendor/SDL2_image/lib/x64/",
        "%{prj.name}/vendor/SDL2_mixer/lib/x64/"
    }

    links
    {
        "SDL2.lib",
        "SDL2main.lib",
        "SDL2_ttf.lib",
        "SDL2_image.lib",
        "SDL2_mixer.lib"
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
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/".. outputdir .. "/Sandbox"), -- %{cfg.buildtarget.relpath} the build path, location of the .dll file in this case
            ("{COPY} vendor/SDL2/lib/x64/SDL2.dll ../bin/".. outputdir .. "/Sandbox"),
            ("{COPY} vendor/SDL2_ttf/lib/x64/SDL2_ttf.dll ../bin/".. outputdir .. "/Sandbox"),
            ("{COPY} vendor/SDL2_image/lib/x64/SDL2_image.dll ../bin/".. outputdir .. "/Sandbox"),
            ("{COPY} vendor/SDL2_mixer/lib/x64/SDL2_mixer.dll ../bin/".. outputdir .. "/Sandbox")
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
        "%{prj.name}/Assets/**"
    }

    includedirs
    {
        "DrEngine/src",
        "DrEngine/vendor/spdlog/include",
        "DrEngine/vendor/SDL2/include",
        "DrEngine/vendor/SDL2_ttf/include",
        "DrEngine/vendor/SDL2_image/include",
        "DrEngine/vendor/SDL2_mixer/include"
    }

    libdirs
    {
        "DrEngine/vendor/SDL2/lib/x64",
        "DrEngine/vendor/SDL2_ttf/lib/x64/",
        "DrEngine/vendor/SDL2_image/lib/x64/",
        "DrEngine/vendor/SDL2_mixer/lib/x64/"
    }

    links
    {
        "DrEngine",
        "SDL2.lib",
        "SDL2main.lib",
        "SDL2_ttf.lib",
        "SDL2_image.lib",
        "SDL2_mixer.lib"
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

