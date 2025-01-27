cmake_minimum_required(VERSION 3.20)
project(PvZ)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "Проект: ${PROJECT_NAME}")
message(STATUS "Компилятор: ${CMAKE_CXX_COMPILER}")
message(STATUS "Версия CMake: ${CMAKE_VERSION}")
message(STATUS "Сборка с C++${CMAKE_CXX_STANDARD}")

set(SOURCE_FILES
	ThreadPool.cpp
    Block.cpp
    Elements.cpp
    Firepea.cpp
    Fireshooter.cpp
    Icepea.cpp
    Iceshooter.cpp
    Icons.cpp
    Level.cpp
    Peashooter.cpp
    Plant.cpp
    Player.cpp
    Sun.cpp
    Sunflower.cpp
    Walnut.cpp
    Zombie.cpp
    main.cpp
    Pea.cpp
    rsdl.cpp
    Display.cpp
)

include_directories(/usr/local/include)

link_directories(/usr/local/lib)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

if (SDL2_FOUND)
    message(STATUS "SDL2 найден: ${SDL2_INCLUDE_DIRS}")
endif()

if (SDL2_IMAGE_FOUND)
    message(STATUS "SDL2_image найден: ${SDL2_IMAGE_INCLUDE_DIRS}")
endif()

if (SDL2_TTF_FOUND)
    message(STATUS "SDL2_ttf найден: ${SDL2_TTF_INCLUDE_DIRS}")
endif()

if (SDL2_MIXER_FOUND)
    message(STATUS "SDL2_mixer найден: ${SDL2_MIXER_INCLUDE_DIRS}")
endif()

add_executable(PvZ ${SOURCE_FILES})

target_link_libraries(PvZ SDL2 SDL2_image SDL2_ttf SDL2_mixer)
