pybind11_add_module(promote pybind_array.cc)
target_include_directories(
  promote PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
                   $<INSTALL_INTERFACE:include>)
target_link_libraries(promote PRIVATE Eigen3::Eigen)

add_custom_target(
  run_py
  DEPENDS promote
)

add_custom_command(
    TARGET run_py
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/test.py" "test.py"
    COMMAND python test.py
    WORKING_DIRECTORY $<TARGET_FILE_DIR:promote>
)
