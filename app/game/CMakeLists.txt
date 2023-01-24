# game code

add_executable(game)

target_compile_features(app PRIVATE cxx_std_11)

target_sources(game "main.cpp")

target_link_libraries(game PRIVATE engine)