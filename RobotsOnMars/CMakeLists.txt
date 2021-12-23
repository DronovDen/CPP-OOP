
cmake_minimum_required(VERSION 3.17)
project(MarsExploration)

set (SOURCES
    main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/World/GameArea.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/World/World.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Robot/Robot.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Robot/Collector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Robot/Sapper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Robot/Server.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameModes/AutoGrab.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameModes/AutoMode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameModes/AutoScan.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameModes/InactiveMode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameModes/ManualMode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameModes/ModeBasement.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Console/Parser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Console/MapLoader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Commands/ChangeMode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Commands/Grab.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Commands/Move.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Commands/SapperManagement.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Commands/Scan.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Application/View.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Application/Manager.cpp
    )

    add_executable(MARS ${SOURCES})
