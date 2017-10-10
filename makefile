CC=gcc
CFLAGS=-Wall -g
SRCS=transmit_control.c inotify_init.c event_queue.c
OBJS=transmit_control.o inotify_init.o event_queue.o

.c.o:	
	$(CC) $(CFLAGS) -c $<

all: transmit_control

transmit_control: $(OBJS)	
	$(CC) $(CFLAGS) inotify_init.o transmit_control.o event_queue.o -o transmit_control

clean:	
	rm -f $(OBJS) *.bak *.o
