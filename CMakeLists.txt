cmake_minimum_required(VERSION 3.10)
project(KPM)

SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/mnt/data/home/codes/libs/include/")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/mnt/data/home/codes/libs/lib/")
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


set(CMAKE_CXX_STANDARD 17)
find_package(Boost REQUIRED COMPONENTS program_options)
find_package (Eigen3 REQUIRED)
find_package (Spectra REQUIRED)
find_package(MPI REQUIRED)

# find_package (Eigen3 3.4.0 REQUIRED NO_MODULE)

include_directories(include ${Boost_INCLUDE_DIRS})
add_executable(KPM src/main.cpp src/FileManager.cpp src/KPM.cpp src/KPMParameters.cpp)
# target_link_libraries(KPM Boost::program_options)
# target_link_libraries(KPM ${Boost_LIBRARIES})
target_link_libraries(KPM  ${Boost_PROGRAM_OPTIONS_LIBRARY})
target_link_libraries(KPM Eigen3::Eigen)
target_link_libraries(KPM MPI::MPI_CXX)

add_executable(KPM_Deterministic src/main.cpp src/FileManager.cpp src/KPM.cpp src/KPMParameters.cpp)
target_link_libraries(KPM_Deterministic  ${Boost_PROGRAM_OPTIONS_LIBRARY})
target_link_libraries(KPM_Deterministic Eigen3::Eigen)
target_link_libraries(KPM_Deterministic MPI::MPI_CXX)
target_compile_definitions(KPM_Deterministic PUBLIC DETERMINISTIC)

add_executable(Eminmax src/eminemax.cpp src/FileManager.cpp src/EminEmaxFinder.cpp)
target_link_libraries(Eminmax ${Boost_PROGRAM_OPTIONS_LIBRARY})
target_link_libraries(Eminmax Eigen3::Eigen)
target_link_libraries(Eminmax Spectra::Spectra)
target_link_libraries(Eminmax MPI::MPI_CXX)
