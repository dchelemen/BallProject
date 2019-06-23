@echo off

REM ---------------------------------------------------------------------------------------
REM 
REM GIT_NAME is for storing the folder name containing the git repo
REM 
REM ---------------------------------------------------------------------------------------

set GIT_NAME=
for %%a in (%~p0.) do set GIT_NAME=%%~nxa

echo . %GIT_NAME%

REM ---------------------------------------------------------------------------------------
REM 
REM Generate CMake into [repo_folder]_build folder next to [repo_folder]
REM 
REM ---------------------------------------------------------------------------------------

where cmake
cmake --version

set BuildDir=%GIT_NAME%_build

if not exist "%~dp0..\%BuildDir%" (
	mkdir "%~dp0..\%BuildDir%"
)

cmake -G "Visual Studio 14 2015 Win64" -B "%~dp0..\%BuildDir%"