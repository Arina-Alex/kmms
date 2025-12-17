@echo off

set BUILD_TYPE=Ninja
set BUILD_SUFFIX=ninja

chcp 65001

set BUILD_FOLDER=build_%BUILD_SUFFIX%
set SOURCE_FOLDER=projects

if not exist %BUILD_FOLDER% mkdir %BUILD_FOLDER%

cd %BUILD_FOLDER%

cmake -G %BUILD_TYPE% ..\%SOURCE_FOLDER%
cmake --build .

copy ..\%SOURCE_FOLDER%\obuchaika\run_obuchaika.bat .\obuchaika
copy ..\%SOURCE_FOLDER%\bubble_sort\compile.bat .\bubble_sort
copy ..\%SOURCE_FOLDER%\bubble_sort_mf\compile_mf.bat .\bubble_sort_mf
	
copy ..\run_tests.bat .