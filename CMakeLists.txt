cmake_minimum_required(VERSION 3.1)
project(Check)

set(ROOT_DIR ${PROJECT_SOURCE_DIR})

message(STATUS ${ROOT_DIR})

include_directories(${PROJECT_NAME} 
    ${ROOT_DIR}/Catch2/single_include/
    # ${ROOT_DIR}/src/
    # ${ROOT_DIR}/test/
    # ${ROOT_DIR}/check/
    ${ROOT_DIR}
)

set(SOURCE_FILES
    # ${ROOT_DIR}/src/mylib.cpp
    # ${ROOT_DIR}/test/version.cpp
    # ${ROOT_DIR}/test/init.cpp
    # ${ROOT_DIR}/test/main.cpp
    # ${ROOT_DIR}/check/check.cpp
    ${ROOT_DIR}/practice.cpp

)

# add_library(${PROJECT_NAME} SHARED
#     ${SOURCE_FILES}
# )

add_executable(${PROJECT_NAME} 
    ${SOURCE_FILES}
)

set_target_properties(${PROJECT_NAME}   PROPERTIES
    COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -g -ldl"
    CXX_STANDARD 14
)
target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})

