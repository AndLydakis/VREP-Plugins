VREP_PATH    :=${HOME}/software/vrep
FAMOUSO_PATH :=${HOME}/software/famouso/

include ${FAMOUSO_PATH}/make/famousoApp.mk

CXXFLAGS     += -O0
SOURCES      := famousoPlugin.cpp ProximitySensor.cpp VREPSensor.cpp
TARGET       := famouso
INCLUDES     += ./include
SRC          := ./src
BUILD        := ./build
LIB          := ./lib

include ../make/plugin.mk
