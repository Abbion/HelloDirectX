workspace "HelloDirectX"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"
thirdPartyPath = "DxFrameWork/ThirdParty/"

project "GLFW"
    kind "StaticLib"
    language "C"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
        (thirdPartyPath .. "GLFW/include/GLFW/glfw3.h"),
        (thirdPartyPath .. "GLFW/include/GLFW/glfw3native.h"),
        (thirdPartyPath .. "GLFW/src/glfw_config.h"),
        (thirdPartyPath .. "GLFW/src/internal.h"),
        (thirdPartyPath .. "GLFW/src/mappings.h"),
        (thirdPartyPath .. "GLFW/src/platform.h"),
        (thirdPartyPath .. "GLFW/src/context.c"),
        (thirdPartyPath .. "GLFW/src/init.c"),
        (thirdPartyPath .. "GLFW/src/input.c"),
        (thirdPartyPath .. "GLFW/src/monitor.c"),
        (thirdPartyPath .. "GLFW/src/platform.c"),
        (thirdPartyPath .. "GLFW/src/vulkan.c"),
        (thirdPartyPath .. "GLFW/src/window.c"),
        (thirdPartyPath .. "GLFW/src/egl_context.c"),
        (thirdPartyPath .. "GLFW/src/null_init.c"),
        (thirdPartyPath .. "GLFW/src/null_joystick.c"),
        (thirdPartyPath .. "GLFW/src/null_monitor.c"),
        (thirdPartyPath .. "GLFW/src/null_window.c"),
        (thirdPartyPath .. "GLFW/src/osmesa_context.c")
	}

    filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		files
		{
            (thirdPartyPath .. "GLFW/src/win32_init.c"),
            (thirdPartyPath .. "GLFW/src/win32_joystick.c"),
            (thirdPartyPath .. "GLFW/src/win32_monitor.c"),
            (thirdPartyPath .. "GLFW/src/win32_time.c"),
            (thirdPartyPath .. "GLFW/src/win32_thread.c"),
            (thirdPartyPath .. "GLFW/src/win32_window.c"),
            (thirdPartyPath .. "GLFW/src/win32_module.c"),
            (thirdPartyPath .. "GLFW/src/wgl_context.c")
		}

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

    filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

--====================================================================

project "DxFrameWork"
    location "DxFrameWork"
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
        "%{prj.name}/src",
        "%{prj.name}/ThirdParty/GLFW/include"
    }

    links
    {
        "GLFW"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "DXFW_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/ExampleProject")
        }   

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "speed"
        symbols "off"

--====================================================================

project "ExampleProject"
    location "ExampleProject"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "DxFrameWork/src",
        "DxFrameWork/ThirdParty/GLFW/include"
    }

    links
    {
        "DxFrameWork"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
    
    filter "configurations:Release"
        runtime "Release"
        optimize "speed"
        symbols "off"