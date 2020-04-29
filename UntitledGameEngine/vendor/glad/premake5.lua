project "glad"
	kind "StaticLib"
	language "C"

	targetdir (workdir .. "/bin/" .. outdir .. "/%{prj.name}")
	objdir (workdir .. "/obj/" .. outdir .. "/%{prj.name}")

	files
	{	"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
		}
	
	

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"
		
		includedirs { "include" }

		defines 
		{ 
			"GLFW_INCLUDE_NONE"
		}


	filter "configurations:Debug"
		buildoptions "/MDd"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		buildoptions "/MD"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		buildoptions "/MD"
		runtime "Release"
		optimize "speed"