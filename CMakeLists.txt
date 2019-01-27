cmake_minimum_required(VERSION 3.13)
project(sandbox_evaluation)

set(CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake)

# Dependencies
find_package(Boost COMPONENTS system filesystem program_options REQUIRED)
find_package(OpenMP REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Flann REQUIRED)

# Subdirectories
set(SOURCE_FILES 
        src/eval/Mesh.h
        src/eval/Mesh.cpp
        src/eval/PointCloud.h
        src/eval/PointCloud.cpp
        src/eval/Helpers.h
        src/eval/Helpers.cpp
        src/tinyply/tinyply.h
        src/tinyply/tinyply.cpp)

# Set variables
set(INCLUDE_DIRS
        ${CMAKE_SOURCE_DIR}/src
        ${Boost_INCLUDE_DIRS}
        ${FLANN_INCLUDE_DIRS})

set(LIBRARIES
        Eigen3::Eigen
        OpenMP::OpenMP_CXX
        ${Boost_LIBRARIES}
        ${FLANN_LIBRARIES})

# Targets
add_executable(evaluation_a main_a.cpp ${SOURCE_FILES})
target_include_directories(evaluation_a PRIVATE ${INCLUDE_DIRS})
target_link_libraries(evaluation_a ${LIBRARIES})

add_executable(evaluation_b main_b.cpp ${SOURCE_FILES})
target_include_directories(evaluation_b PRIVATE ${INCLUDE_DIRS})
target_link_libraries(evaluation_b ${LIBRARIES})

add_executable(evaluation_c main_c.cpp ${SOURCE_FILES})
target_include_directories(evaluation_c PRIVATE ${INCLUDE_DIRS})
target_link_libraries(evaluation_c ${LIBRARIES})