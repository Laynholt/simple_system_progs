#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include "msg_q.h"

static int32_t qid;

void signal_int(int32_t sig)
{
    printf("[SERVER] Closing server...\n");
    remove_queue(qid);
    exit(sig);
}

int main() 
{
    key_t qkey;

    signal(SIGINT, signal_int);
    qkey = ftok("/home/", 'q');

    if (qkey == -1) 
    {
        perror("Can't create key: ");
        return -1;
    }
    printf("%s", "Key for queue was build\n");
    
    if ((qid = open_queue(qkey)) == -1) 
    {
        perror("Can't open queue: ");
        return -1;
    }

    printf("qid = %d\n", qid);
    
    Msgbuf msgbuf;

    uint8_t was_peek = 0;
    while (1) 
    {
        while (peek_message(qid, REQUEST)) 
        {
            was_peek = 1;
            receive_message(qid, REQUEST, &msgbuf);

            printf("[SERVER] RECEIVED message from client [%ld]: [%s]\n", msgbuf.client_pid, msgbuf.msg);

            msgbuf.type = msgbuf.client_pid;
            // printf("Type = %ld\n", msgbuf.type);
            
            strcat(msgbuf.msg, " <REPLY>");     
            if (send_message(qid, &msgbuf) == -1)
                printf("-1\n");

        } 
        
        if (!was_peek)
        {
            printf("[SERVER] No message in queue\n");
        }

        was_peek = 0;
        sleep(5);
    }
    return 0;
}

