workspace "Tag2D"

	filter "system:windows"
		architecture "x64"
	filter "system:macosx"
		architecture "ARM64"

	configurations { "Debug", "Release", "Dist" } -- Debug, Release, Distribution. Debug has symbols, Release has optimizations, Dist has no symbols and optimizations.
	startproject "Client"

	-- Workspace-wide build options for MSVC
	filter "system:windows"
		buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

	flags { "MultiProcessorCompile" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Game"
	include "client/BuildClient.lua"
	include "server/BuildServer.lua"

group "Dependencies"
	include "common/BuildCommon.lua"
	include "client/external/glad/premake5.lua"
	include "client/external/glfw/premake5.lua"
	--include "client/external/ImGui/premake5.lua"