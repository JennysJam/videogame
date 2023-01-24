# game code

add_executable(game)

target_compile_features(game PRIVATE cxx_std_11)

target_sources(game PRIVATE "main.cpp")

set_target_properties(
    game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${root}/bin"
)

target_link_libraries(game PRIVATE engine)

target_link_libraries(
    game PRIVATE
    SDL2::SDL2main
)