add_library(ImGuizmo ImGuizmo.cpp)
target_include_directories(ImGuizmo PRIVATE ${PROJECT_SOURCE_DIR}/libraries)
target_link_libraries(ImGuizmo imgui)