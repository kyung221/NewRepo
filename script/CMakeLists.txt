cmake_minimum_required(VERSION 3.1)
project(CheckSymbol)

set(ROOT_DIR 
${PROJECT_SOURCE_DIR})

set(SOURCE ${ROOT_DIR}/check.cpp)

add_executable(${PROJECT_NAME} 
${SOURCE}
)

set_target_properties(${PROJECT_NAME}   PROPERTIES
    COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -g -ldl"
    CXX_STANDARD 14
)
target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})