VREP_PATH    :=${HOME}/software/vrep
FAMOUSO_PATH :=${HOME}/software/famouso/

include ${FAMOUSO_PATH}/make/famousoApp.mk

CXXFLAGS     += -O0
SOURCES      := FamousoPlugin.cpp ProximitySensor.cpp VREPObject.cpp VREPActuator.cpp VelocityMotor.cpp PositionMotor.cpp #PositionSensor.cpp
TARGET       := Famouso
INCLUDES     += ./include ${HOME}/eos/research/AbstractSensorEvents/include
SRC          := ./src
BUILD        := ./build
LIB          := ./lib

include ../make/plugin.mk

PLUGIN_OBJS := ${PLUGIN_OBJS} ${HOME}/eos/research/AbstractSensorEvents/lib/libASE.a
