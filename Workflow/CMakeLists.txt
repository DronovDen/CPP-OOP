cmake_minimum_required(VERSION 3.12)

project(WorkflowLab)

set (SOURCES
    main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Workflow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Parser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Blocks/BlockFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Blocks/Dump.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Blocks/Grep.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Blocks/Readfile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Blocks/Replace.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Blocks/Sort.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Blocks/WriteFile.cpp
)

add_executable(WORKFLOW_MAIN ${SOURCES})