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
	
	startproject "Sandbox"
	
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
			"%{prj.name}/vendor/spdlog/include/**.h",
			"%{prj.name}/vendor/glm/glm/**.hpp",
			"%{prj.name}/vendor/glm/glm/**.inl"
		
		}
		
		includedirs {
			"%{prj.name}/src/UGE", -- core.h directory
			"%{prj.name}/src", -- ugepch.h directory
			"%{IncludeDir.GLFW}", 
			"%{IncludeDir.spdlog}",
			"%{IncludeDir.glad}",
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.glm}"
		}
		
		links
		{	"GLFW",
			"glad",
			"ImGui",
			"opengl32.lib"
		}
		
		filter {"system:windows"}
			cppdialect "C++17"
			staticruntime "on"
			systemversion "latest"
			
			defines{
			"UGE_PLATFORM_WINDOWS",
			"UGE_DLL_BUILD",
			"UGE_ENABLE_ASSERT",
			"UGE_USING_GLFW"
			}
			
			
		filter {"configurations:Debug"}
			buildoptions "/MDd"
			defines{"UGE_DEBUG"}
			symbols "on"
			
		filter {"configurations:Release"}
			buildoptions "/MD"
			defines{"UGE_RELEASE"}
			optimize "on"
			
		filter {"configurations:Dist"}
			buildoptions "/MD"
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
			cppdialect "C++17"
			staticruntime "on"
			systemversion "latest"
			
			defines{"UGE_USING_GLFW"}
			
		defines{
			"UGE_PLATFORM_WINDOWS"
			}
			
			
		filter {"configurations:Debug"}
			buildoptions "/MDd"
			defines{"UGE_DEBUG"}
			symbols "on"
			
		filter {"configurations:Release"}
			buildoptions "/MD"
			defines{"UGE_RELEASE"}
			optimize "on"
			
		filter {"configurations:Dist"}
			buildoptions "/MD"
			defines{"UGE_DIST"}
			optimize "speed"
	
group "Dependencies"
		include "UntitledGameEngine/vendor/glfw"
		include "UntitledGameEngine/vendor/glad"
		include "UntitledGameEngine/vendor/ImGui"
group ""
	