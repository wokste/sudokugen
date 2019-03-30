workspace "Sudoku Generator"
	location "Projects/VS2017"
	
	language "C++"
	cppdialect "C++17"
	
	architecture "x86_64"
	
	configurations { "Debug", "Release" }
	
	filter { "configurations:Debug" }
		symbols "On"
	
	filter { "configurations:Release" }
		optimize "On"
	
	filter { }

	targetdir ("Build/Bin/%{prj.name}/%{cfg.longname}")
	objdir ("Build/Obj/%{prj.name}/%{cfg.longname}")
	
-- The windowed app
project "Generator"
	kind "ConsoleApp"
	files "Src/SudokuGen/**"
