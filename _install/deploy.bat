@echo off

set "APPDIR=C:\IsomerAPI\_install"
set "WDEP=C:\Qt\6.7.0\mingw_64\bin\windeployqt.exe"

if not exist "%APPDIR%\IsomerAPI.exe" (
  echo ERROR: Cannot find "%APPDIR%\IsomerAPI.exe"
  echo Check APPDIR path.
  pause
  exit /b 1
)

if not exist "%WDEP%" (
  echo ERROR: Cannot find "%WDEP%"
  echo Check Qt path / version / kit folder.
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

