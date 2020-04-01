workspace "UntitledGameEngine"
	architecture "x64"
	
	configurations{
		"Debug",
		"Release",
		"Dist"
	}
	
	outdir = "%{cfg.buildcfg}_%{cfg.architecture}_%{cfg.system}"
	
	
	project "UntitledGameEngine"
		location "UntitledGameEngine"
		kind "SharedLib"
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
			"%{prj.name}/vendor/spdlog/include", --spdlog
			"%{prj.name}/src/UGE" -- core.h directory
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
	
		postbuildcommands {
			("{COPY}   %{cfg.buildtarget.relpath} ./bin/".. outdir .. "/Sandbox")  
			}	
			
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
			"UntitledGameEngine/vendor/spdlog/include" --spdlog
			
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
	

	