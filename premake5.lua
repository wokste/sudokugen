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

-- ALL DEPENDENCIES HERE --
function dependencyCatchLib()
	includedirs "Libs/Catch"
	defines "CATCH_CPP11_OR_GREATER"
end
	
-- The app
project "SudokuGen"
	kind "ConsoleApp"
	files "Src/SudokuGen/**"
	
-- Unittests
project "Tests"
	kind "ConsoleApp"
	dependencyCatchLib()
	files "Src/Tests/**"
	
	-- use the app.
	includedirs "Src/SudokuGen"
	
	--includedirs "Src/SudokuGen/**"
	links "SudokuGen"
	