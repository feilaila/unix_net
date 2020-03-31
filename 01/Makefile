include ../Make.defines
serv: timeserv.o common.o
	${CC} ${CFLAGS} -o $@ timeserv.o common.o ${LIBS}

cli: time.o common.o
	${CC} ${CFLAGS} -o $@ time.o common.o ${LIBS}
clean:
		rm -f ${PROGS} ${CLEANFILES} *.exe