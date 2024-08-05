workspace "Tag2D"
    configurations { "Debug", "Release" }

    project "Client"
        kind "ConsoleApp"
        language "C++"
        location "build/client"
        files { "./client/src/*" }
        targetdir "bin/%{cfg.buildcfg}"

        filter "configurations:Debug"
           defines { "DEBUG" }
           symbols "On"
     
        filter "configurations:Release"
           defines { "NDEBUG" }
           optimize "On"

    project "Server"
        kind "ConsoleApp"
        language "C++"
        location "build/server"
        files { "./server/src/*" }
        targetdir "bin/%{cfg.buildcfg}"

        filter "configurations:Debug"
           defines { "DEBUG" }
           symbols "On"
     
        filter "configurations:Release"
           defines { "NDEBUG" }
           optimize "On"