#include <stdio.h>
#include <unistd.h>
#include "msg_q.h"

int main()
{
    int32_t qid;
    key_t qkey;

    pid_t pid = getpid();
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

    printf("qid = %d, pid = %d\n", qid, pid);

    Msgbuf msgbuf;

    int32_t choice = 1;
    char _kill_null;
    while (1)
    {
        printf("[CLIENT] Enter your choice: [1] - send | [2] - receive | [3] exit | >> ");
        scanf("%d", &choice);
        scanf("%c", &_kill_null);

        if (choice == 2)
        {
            while (peek_message(qid, pid))
            {
                receive_message(qid, pid, &msgbuf);
                printf("[CLIENT] RECEIVED answer from server: [%s]\n", msgbuf.msg);
            }
        }
        else if (choice == 3)
        {
            break;
        }
        else        
        {
            msgbuf.type = (int64_t)REQUEST;
            msgbuf.client_pid = (int64_t)pid;
            printf("[CLIENT] Enter string: ");
            scanf("%[^\n]", msgbuf.msg);
            
            send_message(qid, &msgbuf);
            printf("[CLIENT] SENT message to server: [%s]\n", msgbuf.msg);
        }
    }

    printf("[CLIENT] Disconnected!\n");
    return 0;
}

