add_library(engine STATIC)

target_include_directories(engine PUBLIC "${root}/include")
target_include_directories(engine PUBLIC "${root}/src/vendor/lua05.1.5/src/")

set_target_properties(engine 
    PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY "${root}/lib" 
    )

target_sources(engine PRIVATE "sample.cpp")

# link in SDL3
target_link_libraries(
    engine
    PUBLIC
    SDL2::SDL2
    glm::glm
)