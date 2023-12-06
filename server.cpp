#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>


using namespace std;
const char *FILENAME = "projected_file";
const int FILESIZE = 4096;


int main()
{
    int fd;
    char *ptr;
    struct stat st;

    bool running = true;
    while (running) 
    {
        std::cout << "Server Menu:\n"
                  << "1. Perform Projection\n"
                  << "2. Record Data\n"
                  << "3. Shut Down\n"
                  << "Enter choice: ";
        int choice;
        std::cin >> choice;

        switch (choice) 
        {
            case 1:
                fd = open(FILENAME, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
                ftruncate(fd, FILESIZE);
                ptr = static_cast<char *>(mmap(NULL, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
                break;
            case 2:
                sprintf(ptr, "Hello, shared memory!");
                break;
            case 3:
                munmap(ptr, FILESIZE);
                close(fd);
                unlink(FILENAME);
                running = false;
                break;
        }
    }
    return 0;
}
