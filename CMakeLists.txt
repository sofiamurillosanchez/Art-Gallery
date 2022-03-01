# Edited CMakeLists.txt from Data Structures (Summer 2021) Final Project
cmake_minimum_required(VERSION 3.16)
project(22s-pa01-material-gworls)

set(CMAKE_CXX_STANDARD 17)

##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....
# if you need more, add them here and in the foreach stmt below.
set (input01 "input/sample-data-5.txt")
#set (input02 "data/test_dataset_10k.csv")
#set (input03 "data/test_dataset_sentiment_10k.csv")

#
##########################################

## Copy data files to build dir
foreach(file IN LISTS input01)
    configure_file(${file} ${file} COPYONLY)
endforeach()


include_directories(.)

add_executable(22s-pa01-material-gworls src/main.cpp src/algos.cpp src/algos.h src/painting.cpp src/painting.h src/manager.cpp src/manager.h)