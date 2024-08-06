cd ..
git submodule update
./scripts/premake-5.0.0-beta2-linux/premake5 gmake $1
read -p "Press enter to continue"
