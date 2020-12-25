#include <stdlib.h>
#include "channel.h"
#include <unistd.h> 

  int my_pipe[2];



void channel_init(struct receiver* recv, struct sender* sender, 
  size_t msg_sz) {
	if(recv==NULL || sender ==NULL){
    return;
  }

  if (pipe(my_pipe)<0){
      return;  //pipe error
  }

  recv->msg_sz = msg_sz;
  sender->msg_sz = msg_sz;
}

void channel_get(struct receiver* channel, void* data) {
  if(channel==NULL || data == NULL){
    return;
  }

  read(my_pipe[0],data, channel->msg_sz);
}

void channel_send(struct sender* channel, void* data) {
if(channel==NULL || data == NULL){
    return;
  }
  write(my_pipe[1],data,channel->msg_sz);
}

void sender_dup(struct sender* dest, struct sender* src) {
	if(dest==NULL || src == NULL){
    return;
  }
  dest->msg_sz = src->msg_sz;
}

void channel_destroy(struct receiver* recv, struct sender* sender) {
	if(recv==NULL || sender == NULL){
    return;
  }

  close(my_pipe[0]);
  close(my_pipe[1]);
}

