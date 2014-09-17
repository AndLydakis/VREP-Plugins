VREP_PATH    :=${HOME}/software/vrep
FAMOUSO_PATH :=${HOME}/software/famouso/

include ${FAMOUSO_PATH}/make/famousoApp.mk

CXXFLAGS     += -O0
SOURCES      := FamousoPlugin.cpp ProximitySensor.cpp VREPObject.cpp VREPActuator.cpp VelocityMotor.cpp PositionMotor.cpp #PositionSensor.cpp
TARGET       := Famouso
INCLUDES     += ./include ../../aseia/include
SRC          := ./src
BUILD        := ./build
LIB          := ./lib

CUSTOM_OBJS := ../../aseia/lib/libASE.a

include ../make/plugin.mk
