objects = epoll-server.o common.o

compile : epoll-server epoll-client

epoll-server : $(objects)
	cc -o epoll-server $(objects)

epoll-server.o : common.h
	cc -c epoll-server.c

epoll-client : epoll-client.o common.o
	cc -o epoll-client epoll-client.o common.o

epoll-client.o : common.h
	cc -c epoll-client.c

common.o : common.h
	cc -c common.c

.PHONY : clean cleanall

clean :
	-rm *.o

cleanall :
	-rm *.o epoll-server epoll-client
