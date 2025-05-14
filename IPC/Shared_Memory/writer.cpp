#include <iostream>
#include <string>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHARED_MEMORY_SIZE 1024
#define SHARED_MEMORY_KEY  2910

int main() {
    std::string message = "Hello message from writer process";
    
    //Create shared memory segment
    int shm_id = shmget(SHARED_MEMORY_KEY, SHARED_MEMORY_SIZE, 0666 | IPC_CREAT);
    if (shm_id == -1) {
        std::cerr << "Failed to create shared memory object" << std::endl;
        return 1;
    }

    std::cout << "Shared memory object created with ID: " << shm_id << std::endl;

    // Attach that shared memory segment to the process's address space
    char* shm = (char*)shmat(shm_id, NULL, 0);
    if (shm == (void*)-1) {
        std::cerr << "Failed to attach shared memory segment" << std::endl;
        return 1;
    }

    // Write message to shared memory
    strcpy(shm, message.c_str());

    // Detach the shared memory segment
    shmdt(shm);

    std::cout << "Message written to shared memory" << std::endl;
    
    return 0;
}