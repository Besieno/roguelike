cmake_minimum_required(VERSION 3.20)

project(RoguelikeReference LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(roguelike
    main.cpp
    src/Combat.cpp
    src/Enemy.cpp
    src/Game.cpp
    src/Item.cpp
    src/Map.cpp
    src/NPC.cpp
    src/Player.cpp
    src/UI.cpp
    src/Utils.cpp
)

target_include_directories(roguelike PRIVATE src)

find_package(raylib CONFIG QUIET)

if(raylib_FOUND)
    target_link_libraries(roguelike PRIVATE raylib)
else()
    find_path(RAYLIB_INCLUDE_DIR raylib.h
        PATHS
            "C:/msys64/ucrt64/include"
            "C:/msys64/mingw64/include"
    )
    find_library(RAYLIB_LIBRARY raylib
        PATHS
            "C:/msys64/ucrt64/lib"
            "C:/msys64/mingw64/lib"
    )

    if(NOT RAYLIB_INCLUDE_DIR OR NOT RAYLIB_LIBRARY)
        message(FATAL_ERROR "Raylib nao encontrado. Instale com MSYS2: pacman -S mingw-w64-ucrt-x86_64-raylib")
    endif()

    target_include_directories(roguelike PRIVATE "${RAYLIB_INCLUDE_DIR}")
    target_link_libraries(roguelike PRIVATE "${RAYLIB_LIBRARY}" opengl32 gdi32 winmm)
endif()

if(MSVC)
    target_compile_options(roguelike PRIVATE /W4)
else()
    target_compile_options(roguelike PRIVATE -Wall -Wextra -pedantic)
endif()
