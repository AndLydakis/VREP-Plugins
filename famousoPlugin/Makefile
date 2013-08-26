VREP_PATH    :=${HOME}/software/vrep
FAMOUSO_PATH :=${HOME}/software/famouso/
TARGET    :=famouso

SOURCES   := famousoPlugin.cpp

INCLUDE   := ./include ${FAMOUSO_PATH}/include ${FAMOUSO_PATH}/externals/include ${FAMOUSO_PATH}/externals/Boost
SRC       := ./src
BUILD     := ./build
LIB       := ./lib

CXXFLAGS  := -Wall -g -Os -fno-strict-aliasing
LDFLAGS   := -O1
INCLUDES  := ${INCLUDE}
LDPATHS   := ${FAMOUSO_PATH}/lib/linux/standard/gcc-4.7.3
LIBS      := boost_system boost_thread boost_program_options famouso fec
SYMBOLS   := LINUX FAMOUSO_DEBUG_DISABLE

include ../make/plugin.mk
