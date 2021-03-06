project "Glad"
	kind "StaticLib"
	language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/GLAD/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}

	includedirs
	{
		"include"
	}

	filter "system:linux"
		pic "On"
		systemversion "latest"
		staticruntime "On"

	

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"


	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"


	filter "configurations:Release"
		runtime "Release"
		optimize "on"