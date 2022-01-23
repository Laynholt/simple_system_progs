#include "shrm.h"

int32_t create_shared_memory(uint64_t shm_size, uint32_t client_id)
{
    int32_t segment_id;
    
    key_t key = ftok("shrm.h", client_id);
    if(key == -1)
    {
        printf("Cant create key!\n");
        perror(NULL);
        return -1;
    }

    segment_id = shmget(key, shm_size, IPC_CREAT | 0666);
    if (segment_id == -1)
    {
        printf("Cant create shared memory!\n");
        perror(NULL);
        return -1;
    }
    return segment_id;
}

int16_t destroy_shared_memory(int32_t segment_id)
{
    int16_t ret_val = shmctl(segment_id, IPC_RMID, NULL);
    
    if (ret_val == -1)
    {
        printf("Cant destroy shared memory!\n");
    } 
    return ret_val;
}

void* attach_shared_memory(int32_t segment_id)
{
    void* shm_ptr = shmat(segment_id, NULL, 0);

    if ((void*)-1 == shm_ptr)
    {
        printf("Cant attach to shared memory!\n");
        perror(NULL);
        return (void*)-1;
    }
    return shm_ptr;
}

int16_t dettach_shared_memory(void* shm_ptr)
{
    int16_t ret_val = shmdt(shm_ptr);

    if (ret_val == -1)
    {
        printf("Cant dettach from shared memory!\n");
    }
    return ret_val;
}

int16_t push_entity_shared_memory(int32_t segment_id, void* shm_ptr, const Entity* entity)
{
    memcpy(shm_ptr, entity, sizeof(Entity));
    return 1;
}

int16_t pull_entity_shared_memory(int32_t segment_id, void* shm_ptr, Entity* entity)
{
    memcpy(entity, shm_ptr, sizeof(Entity));
    return 1;
}
