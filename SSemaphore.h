
/*
  A modified semaphore class for use in a std UNIX environment
  that supports both private and non-private semaphores.
  
  Exit codes for class operations:
  1 - Semaphore allocation failure
  2 - Unable remove semaphore
  3 - Unable to LOCK semaphore
  4 - Unable to UNLOCK semaphore
  5 - Failure on wait for ZERO
  6 - Unable to assign value
  7 - Unable to return value
*/

#ifndef SSemaphore_h
#define SSemaphore_h

#define _GNU_SOURCE
#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

class SSemaphore {
public:
    SSemaphore();                           // Private semaphore (default)
    SSemaphore(key_t key, int num_sems);   // Non-private semaphore
    ~SSemaphore();                          // Destructor
    
    int P(int sem_num = 0);
    void V(int sem_num = 0);
    int Z(int sem_num = 0);
    void Put(const int value, int sem_num = 0);
    int Get(int sem_num = 0);
    int GetID() { return semid; }
    bool IsCreator() { return is_creator; }

private:
    #if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)

    #else
        union semun {
            int val;
            struct semid_ds *buf;
            unsigned short int *array;
            struct seminfo *__buf;
        };
    #endif
    
    union semun arg;
    struct sembuf operation;
    int semid;
    pid_t my_pid;
    bool is_creator;
    bool is_private;
};

#endif