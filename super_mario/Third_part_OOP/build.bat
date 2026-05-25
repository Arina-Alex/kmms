@echo off
chcp 1251 > log
del log

set CPP_FILES="main.cpp game.cpp player.cpp enemy.cpp brick.cpp coin.cpp moving.cpp object.cpp"
set EXE=main.exe
set CHARSET="-finput-charset=utf-8 -fexec-charset=windows-1251"

if exist %EXE% del %EXE%

g++ "%CHARSET%" "%CPP_FILES%" -o %EXE%

%EXE%
pause
