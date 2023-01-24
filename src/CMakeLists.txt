add_library(engine STATIC)

target_include_directories(engine PUBLIC "${root}/include/engine")

set_target_properties(engine 
    PRIVATE
    PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY "${root}/lib" 
    )

target_sources(engine "sample.cpp")