#Setup a cmake project called BGO
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(bgo)

#Pulls from Geant4Config.cmake and pulls all relevant
#paths and libraries
find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE}) 

#Add root and GSL (GNU scientific library for saving and plotting)
#find_package(ROOT REQUIRED COMPONENTS Core RIO Hist etc.)
#find_package(GSL REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)

file(GLOB macro_files ${PROJECT_SOURCE_DIR}/macros/*.mac)
file(COPY ${macro_files} DESTINATION ${PROJECT_BINARY_DIR})

add_executable(main ${sources})

target_include_directories(main PRIVATE ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/macros)

target_link_libraries(main ${Geant4_LIBRARIES}) #add ${GSL_LIBRARIES} ${ROOT_LIBRARIES}  

