workspace "UntitledGameEngine"
	architecture "x64"
	
	configurations{
		"Debug",
		"Release",
		"Dist"
	}
	
	outdir = "%{cfg.buildcfg}_%{cfg.architecture}_%{cfg.system}"
	
	-- The include directories of dependencies.
	IncludeDir = {}
	IncludeDir["GLFW"] = "UntitledGameEngine/vendor/glfw/include"
	IncludeDir["spdlog"] = "UntitledGameEngine/vendor/spdlog/include"
	
	group "Dependencies"
		include "UntitledGameEngine/vendor/glfw"

	group ""
	
	project "UntitledGameEngine"
		location "UntitledGameEngine"
		kind "SharedLib"
		language "C++"
	
		targetdir ("bin/" .. outdir .. "/%{prj.name}")
		objdir ("obj/" .. outdir .. "/%{prj.name}")
		
		pchheader "ugepch.h"
		pchsource "UntitledGameEngine/src/ugepch.cpp"
		
		postbuildcommands {
			("{COPY}   %{cfg.buildtarget.relpath} ../bin/".. outdir .. "/Sandbox/")  
			}	
	
		
		files {
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.hpp",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/src/**.c",
			"%{prj.name}/vendor/spdlog/include/**.h"
		
		}
		
		includedirs {
			"%{prj.name}/src/UGE", -- core.h directory
			"%{prj.name}/src", -- ugepch.h directory
			"%{IncludeDir.GLFW}", 
			"%{IncludeDir.spdlog}"
		}
		
		Links
		{	"GLFW",
			"opengl32.lib"
		}
		
		filter {"system:windows"}
			cppdialect "C++17"
			staticruntime "on"
			systemversion "latest"
			
			defines{
			"UGE_PLATFORM_WINDOWS",
			"UGE_DLL_BUILD"
			}
			
			
		filter {"configurations:Debug"}
			defines{"UGE_DEBUG"}
			symbols "on"
			
		filter {"configurations:Release"}
			defines{"UGE_RELEASE"}
			optimize "on"
			
		filter {"configurations:Dist"}
			defines{"UGE_DIST"}
			optimize "speed"
	

		
	project "Sandbox"
			
			
	location "Sandbox"
		kind "ConsoleApp"
		language "C++"
	
		targetdir ("bin/" .. outdir .. "/%{prj.name}")
		objdir ("obj/" .. outdir .. "/%{prj.name}")
		
		files {
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.hpp",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/src/**.c"
		
		}
		
		includedirs {
			"UntitledGameEngine/src",
			"%{IncludeDir.spdlog}"
			
		}
		
		links
		{	"UntitledGameEngine"
		}
		
		filter {"system:windows"}
			cppdialect "C++17"
			staticruntime "on"
			systemversion "latest"
			
		defines{
			"UGE_PLATFORM_WINDOWS",
			}
			
			
		filter {"configurations:Debug"}
			defines{"UGE_DEBUG"}
			symbols "on"
			
		filter {"configurations:Release"}
			defines{"UGE_RELEASE"}
			optimize "on"
			
		filter {"configurations:Dist"}
			defines{"UGE_DIST"}
			optimize "speed"
	

	