CC=gcc
CFLAGS=-Wall
LDFLAGS=
BIN=bin
INC=include
OBJ=obj
SRC=src

ifeq ($(DEBUG),1)
CFLAGS += -DDEBUG -g
endif

all: directories FROGS

directories: ${OBJ} ${BIN}

${OBJ}:
	mkdir -p ${OBJ}
${BIN}:
	mkdir -p ${BIN}

# =====
# OBJET
# =====
${OBJ}/Frogs.o: ${SRC}/Frogs.c
	${CC} -c -o $@ $< $(CFLAGS) -I${INC}

# ==========
# EXECUTABLE
# ==========
FROGS: ${OBJ}/Frogs.o
	${CC} -o ${BIN}/$@ $^

.PHONY: all proper clean cleanall

proper:
	rm -f ${INC}/*~ ${SRC}/*~ *~

clean: proper
	rm -f ${OBJ}/* ${BIN}/*

cleanall: clean
	rm -rf ${OBJ} ${BIN}
