VREP_PATH    :=${HOME}/software/vrep
FAMOUSO_PATH :=${HOME}/software/famouso/

include ${FAMOUSO_PATH}/make/famousoApp.mk

SOURCES      := famousoPlugin.cpp ProximitySensor.cpp VREPSensor.cpp
TARGET       := famouso
SOURCES      := famousoPlugin.cpp
INCLUDES     += ./include
SRC          := ./src
BUILD        := ./build
LIB          := ./lib

include ../make/plugin.mk
