 #include <sys/sem.h>
 #include <stdio.h>
 #include <unistd.h>
 
#define MAXSETSIZE 25

void prog(int pid, int semid) 
{
    struct sembuf wait = {0, -1, 0};
    struct sembuf release = {0, 1, 0};

    struct Semum
    {
        int val;
        struct semid_ds buf;
    } arg;

    printf("-------------------------------------\n");
    printf("I'm process: [%d]. Show info.\n", pid);
    semctl(semid, 0, IPC_STAT, &arg.buf);   // Записывает данные в buf - объект структуры semid_ds 
                                            
    arg.val = semctl(semid, 0, GETVAL);
    
    printf("\nИдентификатор пользователя = %d\n", arg.buf.sem_perm.uid);
    printf("Идентификатор группы = %d\n", arg.buf.sem_perm.gid);
    printf("Права на операции = 0%o\n", arg.buf.sem_perm.mode);
    printf("Число семафоров в множестве = %lu\n", arg.buf.sem_nsems);
    printf("Время последней операции = %ld\n", arg.buf.sem_otime);
    printf("Время последнего изменения = %ld\n", arg.buf.sem_ctime);
    printf("Значение семафора = %d\n", arg.val);

    printf("-------------------------------------\n");
    printf("I'm process: [%d]. Take resource.\n", pid);
    semop(semid, &wait, 1); // Уменьшил счётчик на 1
                            // Ключ, указатель на массив операций, кол-во операций
   
    arg.val = semctl(semid, 0, GETVAL);

    semctl(semid, 0, IPC_STAT, arg.buf);
    printf("\nИдентификатор пользователя = %d\n", arg.buf.sem_perm.uid);
    printf("Идентификатор группы = %d\n", arg.buf.sem_perm.gid);
    printf("Права на операции = 0%o\n", arg.buf.sem_perm.mode);
    printf("Число семафоров в множестве = %lu\n", arg.buf.sem_nsems);
    printf("Время последней операции = %ld\n", arg.buf.sem_otime);
    printf("Время последнего изменения = %ld\n", arg.buf.sem_ctime);
    printf("Значение семафора = %d\n", arg.val);
    
    sleep(2);

    printf("-------------------------------------\n");
    printf("I'm process: [%d]. Return resource.\n", pid);
    semop(semid, &release, 1);  // Увеличил счётчик на 1
   
    arg.val = semctl(semid, 0, GETVAL);

    semctl(semid, 0, IPC_STAT, arg.buf);
    printf("\nИдентификатор пользователя = %d\n", arg.buf.sem_perm.uid);
    printf("Идентификатор группы = %d\n", arg.buf.sem_perm.gid);
    printf("Права на операции = 0%o\n", arg.buf.sem_perm.mode);
    printf("Число семафоров в множестве = %lu\n", arg.buf.sem_nsems);
    printf("Время последней операции = %ld\n", arg.buf.sem_otime);
    printf("Время последнего изменения = %ld\n", arg.buf.sem_ctime);
    printf("Значение семафора = %d\n", arg.val);
}

int main() 
{
    key_t key;

    if ((key = ftok("sem.c", 'a')) == -1) 
    {                                       // Cоздание ключа
        perror("get key fail ftok");
        return -1;
    }

    int semid;
    semid = semget(key, 1, 0666 | IPC_CREAT); // Cоздаем множество семафоров ключ, количество, флаги

    // SETVAL Устанавливает значение конкретного семафора множества как элемент
    // val объединения. semctl используется для осуществления управления
    // множеством семафоров
    if (semctl(semid, 0, SETVAL, 1) < 0) // Ключ, номер семафора, команд
    {
        perror("err");
        return -1;
    }

    if (fork() == 0)
    {
        prog(getpid(), semid);
    }
    else
    {
        prog(getpid(), semid);
        sleep(5);
        semctl(semid, 0, IPC_RMID);
    }

    return 0;
}
