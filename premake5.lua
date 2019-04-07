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
function useCatchLib()
	includedirs "Libs/Catch"
	defines "CATCH_CPP11_OR_GREATER"
end

function useSudokuLib()
	includedirs "Src/SudokuLib"
	links "SudokuLib"
end

-- The main lib
project "SudokuLib"
	kind "StaticLib"
	files "Src/SudokuLib/**"

-- The app
project "SudokuGen"
	kind "ConsoleApp"
	useSudokuLib()
	files "Src/SudokuGen/**"
	
-- Unittests
project "Tests"
	kind "ConsoleApp"
	useCatchLib()
	useSudokuLib()
	files "Src/Tests/**"
	