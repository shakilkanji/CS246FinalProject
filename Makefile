CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla -g
OBJECTS = main.o game.o player.o square.o building.o academic.o residence.o gym.o textdisplay.o
EXEC = watopoly
DEPENDS = ${OBJECTS:.o=.d}

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
