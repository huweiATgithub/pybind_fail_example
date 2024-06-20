cmake_minimum_required(VERSION 3.27)

project(pybind11_example)

option(BUILD_SHARED_LIBS "Build shared libraries (.dll)." OFF)
include(FetchContent)
set(EIGEN_PATCH_SCRIPT_CONTENT "
    function(DisableTesting filepath)
        file(READ \"\${filepath}\" content)
        # the cmake regex replace has limited support for regex;
        # One should be careful with the replacement and make sure it is idempotent
        string(REPLACE \"BUILD_TESTING\" \"EIGEN_TESTING\" content \"\${content}\")
        # write the modified content back to the file
        file(WRITE \"\${filepath}\" \"\${content}\")
    endfunction()
    function(DisableEigen340Testing)
        DisableTesting(\"CMakeLists.txt\")
        DisableTesting(\"unsupported/CMakeLists.txt\")
    endfunction()
    DisableEigen340Testing()
    ")
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/eigen_patch.cmake" "${EIGEN_PATCH_SCRIPT_CONTENT}")
FetchContent_Declare(
        Eigen
        GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
        PATCH_COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/eigen_patch.cmake patch.cmake && ${CMAKE_COMMAND} -P patch.cmake
        GIT_TAG 3.4.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)
set(EIGEN_BUILD_DOC OFF CACHE BOOL "")
set(EIGEN_TESTING OFF CACHE BOOL "")
set(EIGEN_BUILD_PKGCONFIG OFF CACHE BOOL "")
set(EIGEN_SPILE_LARGE_TESTS OFF CACHE BOOL "")
FetchContent_MakeAvailable(Eigen)
find_package(Eigen3 3.4 REQUIRED NO_MODULE)

add_subdirectory(extern/pybind11)
add_subdirectory(src)
