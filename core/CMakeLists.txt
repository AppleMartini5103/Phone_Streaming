add_library(streamcore STATIC
    src/streamcore.cpp
)
target_include_directories(streamcore
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_features(streamcore PUBLIC cxx_std_20)