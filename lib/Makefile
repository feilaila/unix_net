include Make.defines

all:	${LIB_OBJS}
		ar rv ${LIBUNP_NAME} $?
		${RANLIB} ${LIBUNP_NAME}
TEMPOBJS = error.o signal.o host_serv.o sock_ntop_host.o wrapsock.o wrapunix.o
temp:  ${TEMPOBJS}
		ar rv ${LIBUNP_NAME} $?
		${RANLIB} ${LIBUNP_NAME}

test:   common.o test.o 
		${CC} ${CFLAGS} -o $@ test.o common.o
clean:
		rm -f ${PROGS} ${CLEANFILES}
