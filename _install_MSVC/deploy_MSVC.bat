@echo off

rem MSVC deployment script for IsomerAPI
rem If your MSVC build output is still C:\IsomerAPI\_install, change APPDIR below.

set "APPDIR=C:\IsomerAPI\_install_MSVC"

rem Select the Qt MSVC kit. Edit this path if your installed Qt version/kit is different.
set "WDEP=C:\Qt\6.7.0\msvc2019_64\bin\windeployqt.exe"

if not exist "%APPDIR%\IsomerAPI.exe" (
  echo ERROR: Cannot find "%APPDIR%\IsomerAPI.exe"
  echo Check APPDIR path.
  pause
  exit /b 1
)

if not exist "%WDEP%" (
  echo ERROR: Cannot find "%WDEP%"
  echo Check Qt path / version / kit folder.
  echo Typical alternatives:
  echo   C:\Qt\6.7.3\msvc2019_64\bin\windeployqt.exe
  echo   C:\Qt\6.7.0\msvc2022_64\bin\windeployqt.exe
  echo   C:\Qt\6.7.3\msvc2022_64\bin\windeployqt.exe
  pause
  exit /b 1
)

cd /d "%APPDIR%" || (
  echo ERROR: cd failed to "%APPDIR%"
  pause
  exit /b 1
)

"%WDEP%" --release --compiler-runtime --dir . "IsomerAPI.exe"

echo DONE
pause
