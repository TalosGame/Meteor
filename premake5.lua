workspace "Meteor"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Meteor"
	location "Meteor"
	kind "SharedLib"
	language "C++"
	cppdialect "C++11"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h"
	}

	includedirs
	{
		"%{prj.name}/third_party/spdlog/include"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"MTR_PLATFORM_WINDOWS",
			"MTR_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
		 
	filter "configurations:Debug"
		defines "MTR_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MTR_RELEASE"
		optimize "On"
	

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h"
	}

	includedirs
	{
		"Meteor/third_party/spdlog/include",
		"Meteor/src"
	}

	links
	{
		"Meteor"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"MTR_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MTR_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MTR_RELEASE"
		optimize "On"
	