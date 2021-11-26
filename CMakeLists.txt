cmake_minimum_required(VERSION 3.20)
project(ArtificialLife)

set(CMAKE_CXX_STANDARD 20)

add_executable(ArtificialLife main.cpp Organism/Organism.h Environment/Environment.h Organism/Organism.cpp Environment/Environment.cpp Configuration.h Mutation.h Mutation.cpp)
