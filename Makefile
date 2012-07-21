CXX = g++                                       # compiler
CXXFLAGS = -g -Wall -MMD                        # compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}   # makefile name

OBJECTS = plant.o PRNG.o NameServer.o printer.o student.o truck.o
        VendingMachine2.o Watcard.o office.o driver.o
                        # object files forming executable

EXEC = soda                                     # executable name
DEPENDS = ${OBJECTS:.o=.d}                      # substitute ".o" with ".d"

.PHONY : all clean

all : ${EXECS}

${EXEC} : ${OBJECTS}                            # link step
        ${CXX} $^ -o $@

${OBJECTS} : ${MAKEFILE_NAME}                   # OPTIONAL : changes to this file => recompile

-include ${DEPENDS}                             # include *.d files containing program dependences

clean :
        rm -f ${DEPENDS} ${OBJECTS} ${EXEC}     # remove files that can be regenerated
