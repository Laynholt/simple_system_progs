#include "shrm.h"
#include <stdint.h>
#include <signal.h>
#include <stdlib.h>

Shrm shrm_ent;

void signal_int(int32_t sig)
{
    printf("Closing server...\n");
    dettach_shared_memory(shrm_ent.shrm_ptr);
    destroy_shared_memory(shrm_ent.seg_id);
    exit(sig);
}

int main()
{
    Entity entity;
    
    signal(SIGINT, signal_int);  

    if ((shrm_ent.seg_id = create_shared_memory(SHRM_ENTITY_MAX_SIZE, 10)) == -1)
    {
        perror("Can't create shared memory: ");
        return -1;
    }

    if ((shrm_ent.shrm_ptr = attach_shared_memory(shrm_ent.seg_id)) == (void*)-1)
    {
        perror("Can't attach to shared memory: ");
        destroy_shared_memory(shrm_ent.seg_id);
        return -1;
    }

    printf("Shared memory was created! Segment id=[%d]\n", shrm_ent.seg_id);
        
    uint8_t is_empty = 1;
    char choice = 'n';
    char _kill_line;

    while(1)
    {
        if (!is_empty)
        {
            printf("Do you want rewrite data? [y|n]. Or enter [e] to exit >> ");
            scanf("%c", &choice);
            
            if (choice == 'e')
                break;
            else if (choice != 'y')
                continue;
        }
        is_empty = 0;

        printf("Enter key: ");
        scanf("%lu", &entity.key);
        printf("Enter name: ");
        scanf("%s", entity.data.name);
        printf("Enter surname: ");
        scanf("%s", entity.data.surname);
        printf("Enter age: ");
        scanf("%u", &entity.data.age);

        scanf("%c", &_kill_line);

        push_entity_shared_memory(shrm_ent.seg_id, shrm_ent.shrm_ptr, &entity);
        printf("Data was written!\n");
    }

    dettach_shared_memory(shrm_ent.shrm_ptr);
    destroy_shared_memory(shrm_ent.seg_id);
    return 0;
}
