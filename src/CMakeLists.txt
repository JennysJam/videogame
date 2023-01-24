add_library(engine STATIC)

target_include_directories(engine PUBLIC "${root}/include/engine")

target_sources(engine "sample.cpp")