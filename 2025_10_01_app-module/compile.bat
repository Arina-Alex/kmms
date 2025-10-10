@echo off
chcp 1251 > log
del log

set CPP_FILES="io.cpp sort.cpp main.cpp"
set EXE=bubble-sort.exe
set CHARSET="-finput-charset=utf-8 -fexec-charset=windows-1251"

g++ "%CHARSET%" "%CPP_FILES%" -o %EXE%

%EXE%
