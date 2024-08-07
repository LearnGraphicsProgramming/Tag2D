@echo off
pushd %~dp0\..\
git submodule update
call scripts\premake-5.0.0-beta2-windows\premake5.exe gmake %*
popd