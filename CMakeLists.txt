cmake_minimum_required(VERSION 3.10)
project(Genetic VERSION 1.0.0)

set(SOURCES
    src/AdjacencyMatrix.cpp
    src/Algorithm.cpp
    src/FileHandler.cpp
    src/GeneticAlgorithm.cpp
    src/MenuHandler.cpp
    src/Organism.cpp
    src/Population.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} stdc++fs)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CSS_STANDARD 17
    CSS_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
)
