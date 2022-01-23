#include "shrm.h"
#include <stdint.h>
#include <signal.h>
#include <stdlib.h>

Shrm shrm_ent;

void signal_int(int32_t sig)
{
    printf("Disconnect\n");
    dettach_shared_memory(shrm_ent.shrm_ptr);
    exit(sig);
}

void print_entity(const Entity* entity)
{
    printf("Key - [%lu], Name - [%s], Surname - [%s], Age - [%u]\n", entity->key, entity->data.name, entity->data.surname, entity->data.age);
}

int main()
{
    Entity entity;
 
    signal(SIGINT, signal_int);  
    
    printf("Enter segment id of shared memory: ");
    scanf("%d", &shrm_ent.seg_id);

    if ((shrm_ent.shrm_ptr = attach_shared_memory(shrm_ent.seg_id)) == (void*)-1)
    {
        perror("Can't attach to shared memory: ");
        return -1;
    }

    printf("Shared memory was attached!\n");
        
    char choice = 'n';
    char _kill_line;

    scanf("%c", &_kill_line);

    while(1)
    {
        printf("Do you want get another data? [y|n]. Or enter [e] to exit >> ");
        scanf("%c", &choice);
        
        if (choice == 'e')
            break;
        else if (choice != 'y')
            continue;

        pull_entity_shared_memory(shrm_ent.seg_id, shrm_ent.shrm_ptr, &entity);
        print_entity(&entity);
    }

    dettach_shared_memory(shrm_ent.shrm_ptr);
    return 0;
}
