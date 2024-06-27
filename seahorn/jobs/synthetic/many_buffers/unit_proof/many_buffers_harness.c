#include "seahorn/seahorn.h"
#include <stdbool.h>
#include <stdlib.h>
#include <seahorn_util.h>
#include <string.h>

extern bool nd_bool(void);
extern size_t nd_size_t(void);
#define ND __declspec(noalias)
extern ND void memhavoc(void *ptr, size_t size);

#define MAX_BUFS NUM_OUT_RECORDS
static size_t buffer_counter = 0;

typedef struct buf {
    char *data;
    size_t len;    
    size_t ghost;
    size_t buf_ghost;
    char stash[4096];
    size_t stash_len;
} Buffer;


void inline process_buffer(size_t *ghost, char *buffer, size_t len ) {
  memhavoc(buffer, len);
  //size_t counter = sea_get_shadowmem(TRACK_CUSTOM0_MEM, buffer);
  //sea_set_shadowmem(TRACK_CUSTOM0_MEM, buffer, counter + buffer_counter);
  *ghost = *ghost + buffer_counter;
  buffer_counter = buffer_counter + 1;   
}  

int main(int argc, char **argv) {
  //sea_tracking_on();
  Buffer bufs[MAX_BUFS];
  for(int i=0; i < MAX_BUFS; i++) {
    size_t buf_size = nd_size_t();
    assume(buf_size < 4096);
    bufs[i].data = (char *) malloc(buf_size);
    bufs[i].len = buf_size;
    // sea_set_shadowmem(TRACK_CUSTOM0_MEM, bufs[i].data, 1);
    bufs[i].buf_ghost = 1;
  }  
  
  for(int i=0; i < MAX_BUFS; i++) { 
    size_t garbage_len = nd_size_t();
    assume(garbage_len < 4096);
    char *garbage = (char *) malloc(garbage_len);
    memhavoc(garbage, garbage_len);
    memcpy(&bufs[i].stash, garbage, garbage_len);
    bufs[i].stash_len = garbage_len;
  }

  size_t choice1 = nd_size_t();
  size_t choice2 = nd_size_t();
  assume(choice1 < MAX_BUFS);
  assume(choice2 < MAX_BUFS);
  assume(choice1 != choice2);
  process_buffer(&(bufs[choice1].buf_ghost), bufs[choice1].data, bufs[choice1].len);  
  process_buffer(&(bufs[choice2].buf_ghost), bufs[choice2].data, bufs[choice2].len);  
  size_t counter1 = bufs[choice1].buf_ghost; // sea_get_shadowmem(TRACK_CUSTOM0_MEM, bufs[choice1].data);  
  size_t counter2 = bufs[choice2].buf_ghost; // sea_get_shadowmem(TRACK_CUSTOM0_MEM, bufs[choice2].data);  
  sassert(counter1 + 1 == counter2);
  // sassert(bufs[choice1].data[0] + 1  == bufs[choice2].data[0]);
  //sea_tracking_off();
  return 0;
}
