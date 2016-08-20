cmake_minimum_required(VERSION 3.5)
project(shell)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp parser.h parser.cpp Tokenizer.cpp Tokenizer.h VM.cpp VM.h encEdit.cpp encEdit.h)
add_executable(shell ${SOURCE_FILES})