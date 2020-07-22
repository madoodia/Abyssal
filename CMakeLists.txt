# --------------------- #
# (C) 2020 madoodia.com #
#  All Rights Reserved. #
# --------------------- #

cmake_minimum_required(VERSION 3.3)

project($ENV{TARGET_NAME}_Project CXX)

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(src)