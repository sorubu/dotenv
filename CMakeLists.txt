cmake_minimum_required(VERSION 3.22)

project(dotenv
    VERSION 1.0.0
    DESCRIPTION "A simple .env file parser for C++"
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${PROJECT_NAME}
    src/dotenv.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(${PROJECT_NAME}
    PUBLIC
        cxx_std_20
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets

    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}

    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/dotenvConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/dotenvConfig.cmake
    INSTALL_DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/dotenvConfig.cmake
    DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# Test Configuration

option(DOTENV_BUILD_TEST "Build tests" ON)

if (DOTENV_BUILD_TESTS)
    add_executable(${PROJECT_NAME}_test
        tests/main.cpp
    )

    target_link_libraries(${PROJECT_NAME}_test
        PRIVATE
            ${PROJECT_NAME}
    )
endif()