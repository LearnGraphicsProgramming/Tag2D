project "Common"
	location "../common"
	kind "None"
	language "C++"
	cppdialect "C++20"
	staticruntime "Off"

	files
	{
		"src/**.h",
		"src/**.c",
		"src/**.hpp",
		"src/**.cpp"
	}

	includedirs
	{
		"src",
		"external"
	}

	postbuildcommands
	{
			--'{COPY} "assets" "%{cfg.targetdir}"'
	}

	-- Windows
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"PLATFORM_WINDOWS"
		}

		postbuildcommands
		{
		}

	-- Mac OS
	filter "system:macosx"

		defines
		{
			"PLATFORM_MACOS"
		}

		postbuildcommands
		{
		}

	-- Linux
	filter "system:linux"

		defines
		{
			"PLATFORM_LINUX"
		}

		postbuildcommands
		{
		}