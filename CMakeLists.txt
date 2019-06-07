cmake_minimum_required(VERSION 3.13)
project(sandbox_evaluation)

set(CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

# Dependencies
find_package(Boost COMPONENTS system filesystem program_options REQUIRED)
find_package(OpenMP REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Flann REQUIRED)

# Set variables
set(SOURCE_FILES
        src/eval/Mesh.h
        src/eval/Mesh.cpp
        src/eval/PointCloud.h
        src/eval/PointCloud.cpp
        src/eval/nanoflann.hpp
        src/eval/Pca.h
        src/eval/Helpers.h
        src/eval/Helpers.cpp
        src/eval/IPCameraStats.h
        src/eval/IPCameraStats.cpp
        src/eval/EvaluationStats.h
        src/eval/EvaluationStats.cpp
        src/tinyply/tinyply.h
        src/tinyply/tinyply.cpp)

set(INCLUDE_DIRS
        ${CMAKE_SOURCE_DIR}/libraries
        ${CMAKE_SOURCE_DIR}/src
        ${Boost_INCLUDE_DIRS}
        ${FLANN_INCLUDE_DIRS})

set(LIBRARIES
        Eigen3::Eigen
        OpenMP::OpenMP_CXX
        ${Boost_LIBRARIES}
        ${FLANN_LIBRARIES})

# SUBDIRECTORIES
add_subdirectory(libraries)

# Targets
add_executable(single_eval main_single_eval.cpp ${SOURCE_FILES})
target_include_directories(single_eval PRIVATE ${INCLUDE_DIRS})
target_link_libraries(single_eval ${LIBRARIES})

add_executable(batch_eval main_batch_eval.cpp ${SOURCE_FILES})
target_include_directories(batch_eval PRIVATE ${INCLUDE_DIRS})
target_link_libraries(batch_eval ${LIBRARIES})

add_executable(single_quality main_single_quality.cpp ${SOURCE_FILES})
target_include_directories(single_quality PRIVATE ${INCLUDE_DIRS})
target_link_libraries(single_quality ${LIBRARIES})

add_executable(batch_quality main_batch_quality.cpp ${SOURCE_FILES})
target_include_directories(batch_quality PRIVATE ${INCLUDE_DIRS})
target_link_libraries(batch_quality ${LIBRARIES})

add_executable(find_tolerance main_find_tolerance.cpp ${SOURCE_FILES})
target_include_directories(find_tolerance PRIVATE ${INCLUDE_DIRS})
target_link_libraries(find_tolerance ${LIBRARIES})

add_executable(pca main_pca.cpp ${SOURCE_FILES})
target_include_directories(pca PRIVATE ${INCLUDE_DIRS})
target_link_libraries(pca ${LIBRARIES})

add_executable(sandbox sandbox.cpp ${SOURCE_FILES})
target_include_directories(sandbox PRIVATE ${INCLUDE_DIRS})
target_link_libraries(sandbox ${LIBRARIES})

add_executable(parse_camera_stats main_parse_camera_stats.cpp ${SOURCE_FILES})
target_include_directories(parse_camera_stats PRIVATE ${INCLUDE_DIRS})
target_link_libraries(parse_camera_stats ${LIBRARIES} ImGuizmo)