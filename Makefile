CC = clang
CC_FLAGS = -Wall -Wextra
SRC = rk4.c
DEST = rk4.elf

all:
	${CC} ${SRC} ${CC_FLAGS} -o ${DEST}
	./${DEST}
