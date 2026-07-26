add_library(dotenv
    src/dotenv.cpp
)

target_include_directories(dotenv
    PUBLIC
        include
)

target_compile_features(dotenv
    PUBLIC
        cxx_std_20
)