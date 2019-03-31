IMPL:=EXT
OUTPUT:=OUTPUT
OPT:= -multi # -O2

CXX = u++					# compiler
CXXFLAGS = -g -w -O2 -std=c++11 -Wall -Wextra -MMD ${OPT} -D${OUTPUT} # compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS = main.o config.o # list of object files for question 1 prefixed with "q2"
EXEC = soda

DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"

############################################################ #

.PHONY : all clean

all : ${EXEC}
#build all executables

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXEC}
