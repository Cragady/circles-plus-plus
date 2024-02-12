# Overview

This is another stint into OpenGL, but using C++ instead of Lisp on Windows.

This repo assumes a Windows 10/11 OS on 64 bit. I don't want to use Visual Studio, or its build tools, so I'll be utilizing MinGW's gcc/g++ (MinGW-64).

This README may not include everything needed to get this compiled on your architecture, or my targeted architecture. This can be resolved with a little bit of elbow-grease, but I will do my best to keep this file updated if I don't get too caught up in the creation of this program.

As you may notices, this repo's name insinuates that there will be more circles. That's the goal, but I feel pretty accomplished getting this repo to the point where it's at.


## Where It's at currently

This will likely need to be combed through with a debugger and a profiler to make sure I'm not abusing memory. This can be run via CLI, but clicking on the executable doesn't work and gives an error.

I would like to resolve this, and then get this to a point where this can run on Linux and Windows.

Pretty much Finished:

<img src="./assets/demo/color-shift-circle-2.gif" width="300" height="300" />
<img src="./assets/demo/color-shift-circle.gif" width="300" height="300" />

## Dependencies - Linux (Ubuntu)

### Mesa-Utils

`sudo apt-get install mesa-utils`

### libgl1-mesa-dev libglu1-mesa-dev

`sudo apt-get install libgl1-mesa-dev`

### libglu1-mesa-dev (optional)

`sudo apt-get install libglu1-mesa-dev`

### libxrandr-dev

`sudo apt-get install libxrandr-dev`

### libxi-dev

`sudo apt-get install libxi-dev`

### Nvidia

As per ubuntu's [docs](https://ubuntu.com/server/docs/nvidia-drivers-installation#:~:text=for%20your%20hardware%3A-,sudo%20ubuntu%2Ddrivers%20install,-Or%20you%20can):

`sudo ubuntu-drivers install`

Or if another distro: https://docs.nvidia.com/datacenter/tesla/tesla-installation-notes/index.html#package-manager

### GLFW

If you don't have it, [compile it](https://github.com/glfw/glfw?tab=readme-ov-file).

[Compile guide](https://www.glfw.org/docs/latest/compile.html).

#### Commands I used (Ubuntu)

TODO: see about making shared libs if wanted

* `sudo apt-get install xorg-dev`
* `sudo apt-get install cmake`
* `sudo apt-get install libwayland-dev libxkbcommon-dev wayland-protocols extra-cmake-modules`
* `cd libs-and-headers`
* `git clone git@github.com:glfw/glfw`
* `cd glfw`
* `git checkout 3.3.9`
* `cmake -S . -B build -G "Unix Makefiles"`
* `cd build`
* `make`
* `cd ../../../`
* `mkdir lib/gcc`
* `cp -r libs-and-headers/glfw/build/src/libglfw3.a lib/gcc`

(If necessary):
* `cp libs-and-headers/glfw/build/src/libglfw3.a lib/gcc`

Of course, you can do what you want, even installing it on the system, but I wanted this to be local.

## Dependencies - (Windows) Local

* glm

I think this could be a system dependency instead if wanted, and can install, but I decided to add a git submodule to the `modules/` dir.

Run: `make dependencies` after cloning w/modules, or after updating submodules.

## Dependencies - (Windows) System

This section may not be needed for you, as I'm using an `includes/` and `lib/win64` directory that git will be tracking, but if you want to kaibosh this folder, and set it up yourself, then this section is for you. If not, then skip this section.

I've created a folder, `libs-and-headers` to throw libraries and headers into that would've been handled by Visual Studio. 

Dependencies in this section, `Dependencies - System` that are needed, will be put in the aforementioned directory.

### libstdc++-6.dll

I was having issues with [this](https://stackoverflow.com/questions/74734500/cant-find-entry-point-zst28-throw-bad-array-new-lengthv-in-dll-filepath).

I didn't want to mess around with the path variable for this, so I just copied the `libstdc++-6.dll` from mingw and put it in `libs-and-headers`.

`make mingw-deps` should put that dll in the project root where the exe is generated.

### GLFW

Version:  3.3.9 (WIN64)

Go to [GLFW's download page](https://www.glfw.org/download.html) and grab the binaries for 64-bit Windows. Or whatever is appropriate for your system.

Unzip this wherever you like, take the contents and place them in the `libs-and-headers` directory. If you unzipped directly into `libs-and-headers`, and you get a crazy name like `glfw-3.3.9.bin.WIN64`, rename it to `glfw` (or don't, it's up to you).

Put everyting in `glfw's` `include/` dir into the project root's `include/` dir, and put the appropriate compiler lib folder into the project root's `lib/` dir.

Structure:
```
./
  .git
  ...
  libs-and-headers
    glfw/
      docs/
      include/
      lib-mingw-w64/
      ...
    ...
  src/
  ...
```

### GLAD

This is the permalink that was given for the setup I used following the instructions at the [creating a window portion of learnopengl](https://learnopengl.com/Getting-started/Creating-a-window#:~:text=configuration%20of%20GLFW.-,GLAD,-We%27re%20still%20not): [glad generated](https://glad.dav1d.de/#language=c&specification=gl&api=gl%3D4.3&api=gles1%3Dnone&api=gles2%3Dnone&api=glsc2%3Dnone&profile=compatibility&loader=on).

If I did things correctly, and you're on a similar architecture, this should work for you as well.

Follow the instructions left for the glad portion after downloading the zip file.

It's up to you if you want to put it in the `libs-and-headers` dir, or just put it straight into your `includes` folder.

Structure:
```
./
  ...
  libs-and-headers/
    glad/
      include/
      src/
      ...
    ...
  ...
```


## Other Resources

* https://www.khronos.org/opengl/wiki/Main_Page
* https://learnopengl.com/Introduction
