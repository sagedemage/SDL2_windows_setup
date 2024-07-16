# SDL2_window_setup
Setup guide to install SDL2 on Windows with Visual Studio.

## 1. Download the SDL and SDL_mixer Development Libaries
1. Go to this page to download the lastest SDL and SDL_mixer VC++ development libaries:
    - https://github.com/libsdl-org/SDL/releases
    - https://github.com/libsdl-org/SDL_mixer/releases
    - https://github.com/libsdl-org/SDL_image/releases

2. Download these files (**SDL2-devel-2.30.5-VC.zip**, **SDL2_mixer-devel-2.8.0-VC.zip**, **SDL2_image-devel-2.8.2-VC.zip**)

2. Extract the zip files (**SDL2-devel-2.30.5-VC.zip**, **SDL2_mixer-devel-2.8.0-VC.zip**, **SDL2_image-devel-2.8.2-VC.zip**)

3. Create a folder called `vclib` at C drive (`C:\vclib`).

4. Copy the folders (`SDL2-2.30.5`, `SDL2_mixer-2.8.0`) to `C:\vclib`
    - SDL Folder: `SDL2-devel-2.30.5-VC\SDL2-2.30.5`
    - SDL_mixer Folder: `SDL2_mixer-devel-2.8.0-VC\SDL2_mixer-2.8.0`
    - SDL_image Folder: `SDL2_image-devel-2.8.2-VC\SDL2_image-2.8.2`

## 2. Configure the Project in Visual Studio 

1. Make sure your default build setting is `Debug` `x64`.

2. Go to *Project Properties* -> *Configuration Properties* -> Linker -> Input 

**Additional Dependencies** -> Edit:
```
SDL2.lib
SDL2main.lib
SDL2_mixer.lib
SDL2_image.lib
```

3. Go to *Project Properties* -> *Go to Configuration Properties* -> *VC++ Directories*

**Include Directories** -> Edit:
```
C:\vclib\SDL2_image-2.8.2\include
C:\vclib\SDL2_mixer-2.8.0\include
C:\vclib\SDL2-2.30.5\include
```

**Library Directories** -> Edit:
```
C:\vclib\SDL2_image-2.8.2\lib\x64
C:\vclib\SDL2_mixer-2.8.0\lib\x64
C:\vclib\SDL2-2.30.5\lib\x64
```

## 3. Setup Environmental Variables for SDL and SDL_mixer
1. Go to Settings -> Search and click *Edit the system environment variables* -> Click *Environment Variables*

2. Edit the **Path** under the *System varables*:
```
C:\vclib\SDL2-2.30.5\lib\x64
C:\vclib\SDL2_mixer-2.8.0\lib\x64
C:\vclib\SDL2_image-2.8.2\lib\x64
```

**Note**: to add multiple paths add a semicolon after each path

## 4. Build the Program
1. Restart Visual Studio so Visual C++ can get the updated path variable
2. Build and run your program and it should work.

## Resources:
- [Setting up SDL 2 on Visual Studio 2019 Community Edition](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php)