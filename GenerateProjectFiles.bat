@echo off
echo Copyright Avnish Kirnalli 2022.
echo Make sure to run SetupProject.bat before Generating Project Files
echo Generating Project files for DrEngine Visual Studio 2022
call vendor\bin\premake\premake5.exe vs2022
PAUSE