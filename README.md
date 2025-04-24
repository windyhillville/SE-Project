# Elysium
Discover random exoplanets, compare them to Earth, favorite your finds and explore future climate scenarios!
# Installation Instructions
Elysium uses a singular framework for implementing and connecting our backend to our frontend, while using a broad range of libraries for graphics processing. Therefore, we have provided instructions for installing each tool, whether you’re using Windows or MacOS.

# Crow (C++ Framework) Dependencies

**MacOS**

type the following prompt on the terminal.
brew install asio

In your CMakeLists.txt, comment out the lines specified in the file.

**Windows**

Download Visual Studio Build Tools using the link below or have Visual Studio installed with the C++ environment tools.

_https://visualstudio.microsoft.com/visual-cpp-build-tools/_

Clone a C++ package manager called vcpkg by typing in the following prompt:

_git clone https://github.com/microsoft/vcpkg.git_

Go to the directory where you cloned the repo and then use Command Prompt to run these commands in the directory that you choose. (It is easier to put this in the /external folder)

_cd vcpkg_

_.\bootstrap-vcpkg.bat_

Install ASIO in that directory by using the following prompt:

_.\vcpkg install asio_

In Clion, go to → Settings → Build, Execution, Deployment → Cmake

In cmake options, put this in the field there and click apply.

_-DCMAKE_TOOLCHAIN_FILE=external/vcpkg/scripts/buildsystems/vcpkg.cmake_

It will take a few moments for Clion to apply these changes.

If it does not find the file, you can use an absolute path to that directory.

# Processing

**MacOS**

Install Processing using the link below:

_https://processing.org/tutorials/gettingstarted_

Per the website, “Processing comes as a .dmg disk image. Open the file from your Downloads folder, then drag the Processing icon to your Applications folder.”

For the libraries, in Processing’s menu bar:

→ Sketch → Import Library → Manage Libraries, and then search for and install Peasy Cam, HTTP Requests for Processing, and ControlP5.

**Windows**

Install Processing using the link below:

_https://processing.org/tutorials/gettingstarted_

Per the website, “Processing comes as a .msi installer file. Locate the file in your Downloads folder and double-click it to install Processing.”

Choose a typical install in the installer wizard. That has all the features that are required to run this program.

Once it finishes installing Processing, it is normally located in your Program Files on your C drive.

Once you find the folder, open up the folder and double click “Processing.exe” to open the program.

For the libraries, in Processing’s menu bar:

→ Sketch → Import Library → Manage Libraries and then search for Peasy Cam, HTTP Requests for Processing, and ControlP5

# Running the Application

**MacOs**

In Terminal, go to the project directory and then go to the cmake-build-debug folder.

Once in the correct directory, type the following command and the server will start running:

./server

Open the main sketch in Processing titled CEN3031.pde it is located in → frontend → SystemUI  directory.

Now, run the Processing application.

Once you’re finished and exited out of the program, close out of the server by entering the following command prompt:
Ctrl + c

**__Windows__**

Doubleclick the “run_windows.bat” and that will open up the Crow server backend.

Open the main sketch in Processing titled CEN3031.pde, it is located in → frontend → SystemUI  directory.

Now, run the Processing application.

Once you’re finished and exited out of the program, close out of the server by entering the following command prompt:

Ctrl + c 



