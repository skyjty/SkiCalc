workspace "SkiCalc"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "SkiCalcTest"

-- 库项目
project "SkiCalcCore"
    location "src/Core"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    targetdir ("bin/%{cfg.buildcfg}")
    objdir ("bin-int/%{cfg.buildcfg}")

    flags { "MultiProcessorCompile" }
    buildoptions { "/utf-8" }

    files { 
        "src/Core/**.h", 
        "src/Core/**.cpp",
    }

    includedirs { "src/Core" }

    filter "system:windows"
        systemversion "latest"
        defines {
            "_UNICODE",
            "UNICODE"
        }

    filter "configurations:Debug"
        symbols "On"
        defines { "DEBUG" }

    filter "configurations:Release"
        optimize "On"
        defines { "NDEBUG" }

-- 计算器APP
project "SkiCalcApp"
    location "src/App"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir ("bin/%{cfg.buildcfg}")
    objdir ("bin-int/%{cfg.buildcfg}")

    flags { "MultiProcessorCompile" }
    buildoptions { "/utf-8" }

    files {
        "src/App/**.cpp"
    }

    includedirs { "src/Core" }

    links { "SkiCalcCore" }

    filter "system:windows"
        systemversion "latest"
        defines {
            "_UNICODE",
            "UNICODE"
        }

    filter "configurations:Debug"
        symbols "On"
        defines { "DEBUG" }

    filter "configurations:Release"
        optimize "On"
        defines { "NDEBUG" }

-- 测试项目
project "SkiCalcTest"
    location "test"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir ("bin/%{cfg.buildcfg}")
    objdir ("bin-int/%{cfg.buildcfg}")
    
    flags { "MultiProcessorCompile" }
    buildoptions { "/utf-8" }

    files {
        "test/**.cpp",
        "test/**.h",
        "vendor/googletest/googletest/src/gtest-all.cc"
    }

    includedirs {
        "vendor/googletest/googletest/include",
        "vendor/googletest/googletest",
        "src/Core",
    }

    links { "SkiCalcCore" }

    filter "system:windows"
        systemversion "latest"
        defines {
            "_UNICODE",
            "UNICODE"
        }

    filter "configurations:Debug"
        symbols "On"
        defines { "DEBUG" }

    filter "configurations:Release"
        optimize "On"
        defines { "NDEBUG" }