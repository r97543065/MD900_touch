#include <string.h>
#include <stdlib.h>

#include "sys_mq.h"

static struct  MessageQueue_ Queue;

// md660p 's queue machninum
int GetMessage(unsigned char *num,unsigned char *para)
{
  if(Queue.i_head == Queue.i_tail)
  {
    *num = 0;
    *para = 0;
    return -1;
  }

  Queue.i_tail = (Queue.i_tail + 1) & (QUEUE_I_MASK);

  *num = Queue.Q[Queue.i_tail].MessageNum;
  *para = Queue.Q[Queue.i_tail].MessageParameter;

  return 0;
}

int PutMessage(unsigned char num,unsigned char para)
{
  if((Queue.i_head - Queue.i_tail) == -1){return -1;}
  
  Queue.i_head = (Queue.i_head + 1) & (QUEUE_I_MASK);
  
  Queue.Q[Queue.i_head].MessageNum = num;
  Queue.Q[Queue.i_head].MessageParameter = para;
  
  return 0;
}
