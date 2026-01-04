/*
  SSemaphore implementation with support for non-private semaphores
*/

#include "SSemaphore.h"

SSemaphore::SSemaphore() {
    my_pid = getpid();
    is_creator = true;
    is_private = true;
    
    if ((semid = semget(IPC_PRIVATE, 1, 0660)) == -1) {
        perror("semget - private semaphore");
        exit(1);
    }
    Put(0);
}

SSemaphore::SSemaphore(key_t key, int num_sems) {
    my_pid = getpid();
    is_private = false;
    
    if ((semid = semget(key, num_sems, IPC_CREAT | IPC_EXCL | 0660)) != -1) {
        is_creator = true;
        for (int i = 0; i < num_sems; i++) {
            Put(0, i);
        }
    } else {
        if ((semid = semget(key, num_sems, 0)) == -1) {
            perror("semget - non-private semaphore");
            exit(1);
        }
        is_creator = false;
    }
}

SSemaphore::~SSemaphore() {
    if (is_creator) {
        if (semctl(semid, 0, IPC_RMID) == -1) {
            perror("semctl - removing semaphore");
            exit(2);
        }
    }
}

int SSemaphore::P(int sem_num) {
    operation.sem_num = sem_num;
    operation.sem_op = -1;
    operation.sem_flg = SEM_UNDO;
    
    if (semop(semid, &operation, 1) == -1) {
        perror("semop - P operation");
        exit(3);
    }
    return 0;
}

void SSemaphore::V(int sem_num) {
    operation.sem_num = sem_num;
    operation.sem_op = 1;
    operation.sem_flg = SEM_UNDO;
    
    if (semop(semid, &operation, 1) == -1) {
        perror("semop - V operation");
        exit(4);
    }
}

int SSemaphore::Z(int sem_num) {
    operation.sem_num = sem_num;
    operation.sem_op = 0;
    operation.sem_flg = SEM_UNDO;
    
    if (semop(semid, &operation, 1) == -1) {
        perror("semop - Z operation");
        exit(5);
    }
    return 0;
}

void SSemaphore::Put(int const value, int sem_num) {
    arg.val = value;
    if (semctl(semid, sem_num, SETVAL, arg) == -1) {
        perror("semctl - Put operation");
        exit(6);
    }
}

int SSemaphore::Get(int sem_num) {
    int sem_value;
    if ((sem_value = semctl(semid, sem_num, GETVAL, 0)) == -1) {
        perror("semctl - Get operation");
        exit(7);
    }
    return sem_value;
}