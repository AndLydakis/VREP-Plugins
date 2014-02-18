ifeq (${VREP_PATH},)
	$(error "Please set the VREP_PATH")
endif

PLUGIN_INCLUDE := $(abspath $(dir $(lastword ${MAKEFILE_LIST}))/../include)
PLUGIN_SRC     := $(abspath $(dir $(lastword ${MAKEFILE_LIST}))/../src)
PLUGIN_BUILD   := $(abspath $(dir $(lastword ${MAKEFILE_LIST}))/../build)
VREP_INCLUDE  := ${VREP_PATH}/programming/include
VREP_SRC      := ${VREP_PATH}/programming/common

VREP_SOURCES  := v_repLib.cpp
PLUGIN_SOURCES:= pluginSkeleton.cpp vrepPlugin.cpp pluginLog.cpp

VREP_OBJS     := $(addsuffix .o, $(addprefix ${PLUGIN_BUILD}/, $(basename ${VREP_SOURCES})))
PLUGIN_OBJS   := $(addsuffix .o, $(addprefix ${PLUGIN_BUILD}/, $(basename ${PLUGIN_SOURCES})))
OBJECTS       := $(addsuffix .o, $(addprefix ${BUILD}/, $(basename ${SOURCES})))

CXXFLAGS      += -std=gnu++11
LDFLAGS       += -shared
LIBS          := $(addprefix -l, ${LIBS} dl boost_filesystem)
LDPATHS       := $(addprefix -L, ${LDPATHS})
SOURCES       := $(addprefix ${SRC}/,${SOURCES})
INCLUDES      := $(addprefix -I, ${INCLUDES} ${PLUGIN_INCLUDE} ${VREP_INCLUDE})
SYMBOLS       := $(addprefix -D, ${SYMBOLS})
TARGET        := ${LIB}/libv_repExt${TARGET}.so

vpath %.cpp ${VREP_SRC}:${PLUGIN_SRC}:${SRC}
vpath %.o ${PLUGIN_BUILD}:${BUILD}

.PHONY: all install clean distclean

all: ${TARGET}

${PLUGIN_BUILD} ${BUILD} ${LIB}: %:
	mkdir $@

${TARGET}: ${OBJECTS} ${PLUGIN_OBJS} ${VREP_OBJS} | ${LIB}
	${CXX} -o $@ ${LDFLAGS} $^ ${LDPATHS} ${LIBS}

${OBJECTS}: ${BUILD}/%.o: %.cpp | ${BUILD}
	${CXX} -c ${CXXFLAGS} ${SYMBOLS} -o $@ $< ${INCLUDES}

${PLUGIN_BUILD}/%.o: %.cpp | ${PLUGIN_BUILD}
	${CXX} -c ${CXXFLAGS} ${SYMBOLS} -o $@ $< ${INCLUDES}

install: ${TARGET}
	cp $< ${VREP_PATH}

clean:
	rm -f ${TARGET} ${BUILD}/*.o

distclean: clean
	rm -f ${PLUGIN_BUILD}/*.o
