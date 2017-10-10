#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/inotify.h>
#include <signal.h>

#include"event_queue.h"
#include"inotify_init.h"

int keep_running;

void signal_handler(int signum){
  keep_running = 0;
}
int main(int argc, char **argv){
  int inotify_fd;
  queue_t q; /* place to enqueue inotify events */
	
  keep_running = 1;
  /* ctrl+c can close the terminal */
  if (signal (SIGINT, signal_handler) == SIG_IGN){
      /* Reset to SIG_IGN (ignore) if that was the prior state */
    signal (SIGINT, SIG_IGN);
  }
	
  inotify_fd = open_inotify_fd ();
  if(inotify_fd > 0){		
	q = queue_create(128);
		
	int wd; /* watch descriptor returned for each item we are watching */
	int index;
		
	wd = 0;
	printf("\n");
		
	/* input the watching catalog and print it */
	for (index = 1; (index < argc) && (wd >= 0); index++) {
	  wd = watch_dir(inotify_fd, argv[index], IN_ALL_EVENTS);
	}
		
	if (wd > 0) {
	  process_inotify_events (q, inotify_fd); /* wait the exent */
	}
		
	printf("\nwatch end !\n");
		
	close_inotify_fd (inotify_fd);
	queue_destroy (q);
		
  }
	
  return 0;
	
}

