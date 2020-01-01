workspace "Meteor"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Meteor/third_party/GLFW/include"
IncludeDir["Glad"] = "Meteor/third_party/Glad/include"
IncludeDir["glm"]  = "Meteor/third_party/glm"
IncludeDir["stb_image"] = "Meteor/third_party/stb_image"

group "Dependencies"
	include "Meteor/third_party/GLFW"
	include "Meteor/third_party/Glad"

group ""

project "Meteor"
	location "Meteor"
	kind "StaticLib"
	language "C++"
	cppdialect "C++11"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mtrpch.h"
	pchsource "Meteor/src/mtrpch.cpp"

	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h",
		"%{prj.name}/third_party/stb_image/**.h",
		"%{prj.name}/third_party/stb_image/**.cpp",
		"%{prj.name}/third_party/glm/glm/**.hpp",
		"%{prj.name}/third_party/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/third_party/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"MTR_PLATFORM_WINDOWS",
			"MTR_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"MTR_ENABLE_ASSERTS"			
		}

	filter "configurations:Debug"
		defines "MTR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MTR_RELEASE"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
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
		"Meteor/third_party/spdlog/include",
		"Meteor/src",
		"Meteor/third_party",
		"%{IncludeDir.glm}",
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
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MTR_RELEASE"
		runtime "Release"
		optimize "on"
	