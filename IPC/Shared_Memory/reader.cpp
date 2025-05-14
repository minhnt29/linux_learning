#include <iostream>
#include <string>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHARED_MEMORY_SIZE 1024
#define SHARED_MEMORY_KEY  2910

int main() {
    std::string message = "Hello message from writer process";
    
    //Get shared memory segment
    int shm_fd = shmget(SHARED_MEMORY_KEY, SHARED_MEMORY_SIZE, 0666);
    if (shm_fd == -1) {
        std::cerr << "Failed to get shared memory object" << std::endl;
        return 1;
    }

    // Attach that shared memory segment to the process's address space
    char* shm = (char*)shmat(shm_fd, NULL, 0);
    if (shm == (void*)-1) {
        std::cerr << "Failed to attach shared memory segment" << std::endl;
        return 1;
    }

    // Read message from shared memory  
    std::string received_message(shm);
    std::cout << "Received message: " << received_message << std::endl;

    // Detach the shared memory segment
    shmdt(shm);

    // Remove the shared memory segment
    shmctl(shm_fd, IPC_RMID, NULL);

    return 0;
}