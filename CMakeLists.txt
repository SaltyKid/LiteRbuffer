cmake_minimum_required(VERSION 3.15)
project(lite_rbuffer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if(WIN32)
else()
set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
endif()

aux_source_directory(source SOURCES_FILES)
set(INCLUDE_PATHS "source")

macro(ADD_SOURCES_FILES sub_files)
    set(SOURCES_FILES "${SOURCES_FILES};${sub_files}" PARENT_SCOPE)
endmacro()

macro(ADD_INCLUDE_PATH sub_include)
    set(INCLUDE_PATHS "${INCLUDE_PATHS};${sub_include}" PARENT_SCOPE)
endmacro()

set(SUBDIR_LIST "")
macro(get_sublist_recursive dir)
    file(GLOB sub_dirs RELATIVE ${dir} ${dir}/*)
    foreach(sub_dir ${sub_dirs})
        if(IS_DIRECTORY ${dir}/${sub_dir})
            if(EXISTS ${dir}/${sub_dir}/CMakeLists.txt)
                list(APPEND SUBDIR_LIST "${dir}/${sub_dir}")
            endif()
            get_sublist_recursive(${dir}/${sub_dir})
        endif()
    endforeach()
endmacro()
get_sublist_recursive(${CMAKE_SOURCE_DIR}/source)

foreach(sub_dir ${SUBDIR_LIST})
    add_subdirectory("${sub_dir}")
endforeach()

include_directories(${INCLUDE_PATHS})
add_executable(${PROJECT_NAME} ${SOURCES_FILES})
