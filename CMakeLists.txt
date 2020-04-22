cmake_minimum_required(VERSION 3.16)
project(shapeshooter)

set(CMAKE_CXX_STANDARD 20)

add_executable(shapeshooter main.cpp Game.cpp Game.h Player.cpp Player.h Bullet.cpp Bullet.h Enemy.cpp Enemy.h)

add_subdirectory(include/SFML)

target_link_libraries(
        shapeshooter
        PUBLIC
        sfml-graphics sfml-window sfml-system
)

target_include_directories(shapeshooter PRIVATE)


