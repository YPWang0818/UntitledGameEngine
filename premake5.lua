workspace "UntitledGameEngine"
	architecture "x64"
	
	configurations{
		"Debug",
		"Release",
		"Dist"
	}
	
	outdir = "%{cfg.buildcfg}_%{cfg.architecture}_%{cfg.system}"
	workdir = "%{wks.location}"
	
	-- The include directories of dependencies.
	IncludeDir = {}
	IncludeDir["GLFW"] = "UntitledGameEngine/vendor/glfw/include"
	IncludeDir["spdlog"] = "UntitledGameEngine/vendor/spdlog/include"
	IncludeDir["glad"] = "UntitledGameEngine/vendor/glad/include"
	IncludeDir["ImGui"] = "UntitledGameEngine/vendor/ImGui"
	IncludeDir["glm"] = "UntitledGameEngine/vendor/glm"
	IncludeDir["stb_image"] = "UntitledGameEngine/vendor/stb_image"
	
	startproject "Sandbox"
	
	project "UntitledGameEngine"
		location "UntitledGameEngine"
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"
	
		targetdir ("bin/" .. outdir .. "/%{prj.name}")
		objdir ("obj/" .. outdir .. "/%{prj.name}")	
		
		
		pchheader "ugepch.h"
		pchsource "UntitledGameEngine/src/ugepch.cpp"
		
		
		files {
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.hpp",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/src/**.c",
			"%{prj.name}/vendor/spdlog/include/**.h",
			"%{prj.name}/vendor/glm/glm/**.hpp",
			"%{prj.name}/vendor/glm/glm/**.inl",
			"%{prj.name}/vendor/stb_image/**.h",
			"%{prj.name}/vendor/stb_image/**.cpp",
		}
		
		includedirs {
			"%{prj.name}/src/UGE", -- core.h directory
			"%{prj.name}/src", -- ugepch.h directory
			"%{IncludeDir.GLFW}", 
			"%{IncludeDir.spdlog}",
			"%{IncludeDir.glad}",
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.glm}",
			"%{IncludeDir.stb_image}"
		}
		
		links
		{	"GLFW",
			"glad",
			"ImGui",
			"opengl32.lib"
		}
		
		filter {"system:windows"}
			systemversion "latest"
			
			defines{
			"UGE_PLATFORM_WINDOWS",
			"UGE_DLL_BUILD",
			"UGE_ENABLE_ASSERT",
			"UGE_USING_GLFW"
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
		cppdialect "C++17"
		staticruntime "on"
	
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
			"UntitledGameEngine/src/UGE",
			"%{IncludeDir.spdlog}",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.glad}",
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.glm}"
			
		}
		
		links
		{	"UntitledGameEngine"
		}
		
		filter {"system:windows"}
			systemversion "latest"
			
			defines{
			"UGE_PLATFORM_WINDOWS",
			"UGE_USING_GLFW"
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
	
group "Dependencies"
		include "UntitledGameEngine/vendor/glfw"
		include "UntitledGameEngine/vendor/glad"
		include "UntitledGameEngine/vendor/ImGui"
group ""
	