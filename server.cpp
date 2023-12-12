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
        printf("\033[0;33;40m"); 
        puts("====================================================");
        puts("Client Menu:");
        puts("====================================================");
        printf("\033[0m"); 
        puts("1. Perform Projection");
        puts("2. Read Data");
        puts("3. Shut Down");
        printf("\033[0;34;40m");
        puts("Enter choice:");
        printf("\033[0m"); 
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
                sprintf(ptr, "This is a message to a client!");
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
