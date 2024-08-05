@echo off
pushd %~dp0\..\
call scripts\premake-5.0.0-beta2-windows\premake5.exe gmake %*
popd
PAUSE