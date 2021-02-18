workspace "HawtLib"
	configurations { "Debug", "Release" }
	platforms { "x86", "x64" }
	startproject "HawtLibDemo"

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "HawtLib"
	location "HawtLib"
	kind "StaticLib"
	language "C++"

	targetdir ("Build/bin/" .. outputDir .. "/%{prj.name}")
	objdir ("Build/bin-obj/" .. outputDir .. "/%{prj.name}")

	files { "%{prj.name}/Source/**.h", "%{prj.name}/Source/**.cpp" }

	filter "system:windows"
		cppdialect "C++17"
		-- staticruntime "On"
		systemversion "latest"
		defines "PLT_Windows"
		postbuildcommands {"cd ../scripts && MakeIncludes.bat"}		

	filter "system:linux"
		defines "PLT_Linux"
		postbuildcommands {"cd ../scripts && ./MakeIncludes.sh"}

	filter "system:macosx"
		defines "PLT_Mac"
		postbuildcommands {"cd ../scripts && ./MakeIncludes.sh"}

	filter "configurations:Debug"
		defines "DEBUG"

	filter "configurations:Release"
		defines "NDEBUG"

	filter "platforms:x86"
		architecture "x86"
		defines "X86"

	filter "platforms:x64"
		architecture "x64"
		defines "X64"


project "HawtLibDemo"
	location "HawtLibDemo"
	kind "ConsoleApp"
	language "C++"

	targetdir ("Build/bin/" .. outputDir .. "/%{prj.name}")
	objdir ("Build/bin-obj/" .. outputDir .. "/%{prj.name}")

	includedirs {"Build/includes"}				-- HawtLib Include Location
	libdirs {"Build/bin/" .. outputDir .. "/HawtLib"}	-- HawtLib lib location
	links {"HawtLib.lib"}					-- link HawtLib.lib

	files { "%{prj.name}/Source/**.h", "%{prj.name}/Source/**.cpp" }

	filter "system:windows"
		cppdialect "C++17"
		-- staticruntime "On"
		systemversion "latest"
		defines "PLT_Windows"

	filter "system:linux"
		defines "PLT_Linux"

	filter "system:macosx"
		defines "PLT_Mac"

	filter "configurations:Debug"
		defines "DEBUG"

	filter "configurations:Release"
		defines "NDEBUG"

	filter "platforms:x86"
		architecture "x86"
		defines "X86"

	filter "platforms:x64"
		architecture "x64"
		defines "X64"

