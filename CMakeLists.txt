cmake_minimum_required (VERSION 3.8)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project (asynctest VERSION ${PROJECT_VESRION})

add_subdirectory (async)

find_package(GTest)

configure_file(
        version.h.in 
        ${CMAKE_CURRENT_BINARY_DIR}/version.h
)
add_executable(${PROJECT_NAME} main.cpp)
add_executable(async_gtest test/async_gtest.cpp)


target_include_directories(
    ${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_include_directories(
    async_gtest PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_include_directories(
    async_gtest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/test
)


target_include_directories(
    async_gtest PRIVATE
    ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(
    async_gtest PRIVATE
    ${GTEST_BOTH_LIBRARIES}
)

target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/async/headers
)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    libasync
)

set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE
        /EHsc
        /W4
        /WX
    )

endif()

install(TARGETS asynctest RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(async_gtest async_gtest)