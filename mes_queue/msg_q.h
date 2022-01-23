#ifndef _MSG_Q_H_
#define _MSG_Q_H_

#include <sys/msg.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#define REQUEST 5

typedef struct Msgbuf
{
    int64_t type;
    int64_t client_pid;
    char msg[32];

} Msgbuf;

extern int16_t open_queue(key_t key);
extern int16_t send_message(int32_t qid, Msgbuf *qbuf);
extern int16_t receive_message(int32_t qid, int64_t type, Msgbuf *qbuf);
extern int16_t peek_message(int32_t qid, int64_t type);
extern int16_t remove_queue(int32_t qid);

#endif
