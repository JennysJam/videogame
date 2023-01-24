cmake_minimum_required(VERSION 3.22.1)

project(
    videogame
    VERSION 0.1
    LANGUAGES CXX
)

# set root element
set(root "${CMAKE_CURRENT_LIST_DIR}")

#library code scope
add_subdirectory("src")

#binary scopes
add_subdirectory("app")

# add thirdparty libraries

add_subdirectory("external")