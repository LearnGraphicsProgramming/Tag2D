# Tag2D

Tag2D Description..

# Build
To generate your preferred build files, navigate into the `scripts/` directory and run your preferred script.

Visual Studio 2022: [`GenerateVS2022.bat`](scripts/GenerateVS2022.bat)

Windows GNU Make: [`GenerateWindowsMake.bat`](scripts/GenerateWindowsMake.bat)

Linux GNU Make: [`GenerateLinuxMake.sh`](scripts/GenerateLinuxMake.sh)

MacOS GNU Make: [`GenerateMacOSMake.sh`](scripts/GenerateMacOSMake.sh)

# Visual Studio Project Configuration
In order to succesfully build the project, the `common` folder must be added as an additional included directory. Go in `Solution Explored` and right click the project you want to configure then go to Properties -> Configuration Properties -> C/C++ -> General -> Additional Include Directories -> Edit -> New Line and add `$(SolutionDir)common\src\`.