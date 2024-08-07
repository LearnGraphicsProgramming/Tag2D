project "Server"
	location "../server"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "Off"

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.c",
		"src/**.hpp",
		"src/**.cpp",
		"../common/src/**.c",
		"../common/src/**.h",
		"../common/src/**.cpp",
		"../common/src/**.hpp",
	}

	includedirs
	{
		"src",
		"external",
		"../common/src",
		--"../common/external/glm"
	}

	links
	{
	}

	postbuildcommands
	{
			--'{COPY} "assets" "%{cfg.targetdir}"'
	}

	filter "configurations:Debug"
		defines { "BUILD_DEBUG" }
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines { "BUILD_RELEASE" }
		runtime "Release"
		optimize "On"
		symbols "On"

	filter "configurations:Dist"
		defines { "BUILD_DIST" }
		runtime "Release"
		optimize "On"
		symbols "Off"

	-- Windows
	filter "system:windows"
		systemversion "latest"

		links
		{
		}

		defines
		{
			"PLATFORM_WINDOWS"
		}

		postbuildcommands
		{
		}

	-- Mac OS
	filter "system:macosx"

		links
		{
		}

		defines
		{
			"PLATFORM_MACOS"
		}

		postbuildcommands
		{
		}

	-- Linux
	filter "system:linux"

		links
		{
			--"GL",
			--"X11",
			--"Xi",
			--"Xrandr",
			--"Xxf86vm",
			--"Xinerama",
			--"Xcursor",
			--"rt",
			--"m",
			--"pthread"
		}

		defines
		{
			"PLATFORM_LINUX"
		}

		postbuildcommands
		{
		}