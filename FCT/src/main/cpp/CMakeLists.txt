# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.22.1)

project("fct")

# Creates your game shared library. The name must be the same as the
# one used for loading in your Kotlin/Java or AndroidManifest.txt files.
add_library(fct SHARED
        ../../../main.cpp
        ../../../AndroidOut.cpp
        #../../../Renderer.cpp
        ../../../Shader.cpp
        ../../../TextureAsset.cpp
        ../../../Android_Window.cpp
        ../../../AndroidActivitySwap.cpp
        ../../../GLES3_0_Context.cpp
        ../../../GLES3_0_Image.cpp
        ../../../hander.cpp
        ../../../Utility.cpp)

# Searches for a package provided by the game activity dependency
find_package(game-activity REQUIRED CONFIG)

# Configure libraries CMake uses to link your target library.
target_link_libraries(fct
        # The game activity
        #game-activity::game-activity

        # EGL and other dependent libraries required for drawing
        # and interacting with Android system
        EGL
        GLESv3
        jnigraphics
        android
        log)