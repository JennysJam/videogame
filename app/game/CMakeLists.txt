# game code

add_executable(game)

target_compile_features(app PRIVATE cxx_std_11)

target_sources(game "main.cpp")

set_target_properties(
    game PRIVATE PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${root}/bin"
)

target_link_libraries(game PRIVATE engine)