#include "msg_q.h"

#define TRUE 1
#define FALSE 0

int16_t open_queue(key_t key)
{
    int16_t qid;

    if ((qid = msgget(key, IPC_CREAT | 0660)) == -1)
    {
        perror("Get error: ");
        return -1;
    }
    return qid;
}

int16_t send_message(int32_t qid, Msgbuf *qbuf)
{
    int16_t result;
    size_t length;

    length = sizeof(Msgbuf) - sizeof(int64_t);
    if ((result = msgsnd(qid, qbuf, length, IPC_NOWAIT)) == -1)
    {
        perror("Send error: ");
        return -1;
    }
    return result;
}

int16_t receive_message(int32_t qid, int64_t type, Msgbuf *qbuf)
{
    int16_t result;
    size_t length;

    length = sizeof(Msgbuf) - sizeof(int64_t);
    if ((result = msgrcv(qid, qbuf, length, type, IPC_NOWAIT)) == -1)
    {
        perror("Receive error: ");
        return -1;
    }
    return result;
}

int16_t peek_message(int32_t qid, int64_t type)
{
    if ((msgrcv(qid, 0, 0, type, IPC_NOWAIT)) == -1)
    {
        if (errno == E2BIG)
            return TRUE;
    }
    return FALSE;
}

int16_t remove_queue(int32_t qid)
{
    if (msgctl(qid, IPC_RMID, 0) == -1)
    {
        perror("Control error: ");
        return -1;
    }
    return 0;
}
