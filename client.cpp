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
        std::cout << "Client Menu:\n"
                  << "1. Perform Projection\n"
                  << "2. Read Data\n"
                  << "3. Shut Down\n"
                  << "Enter choice: ";
        int choice;
        std::cin >> choice;
        switch (choice) 
        {
            case 1:
                fd = open(FILENAME, O_RDONLY);
                fstat(fd, &st);
                ptr = static_cast<char *>(mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0));
                break;
            case 2:
                std::cout << "Client received: " << ptr << std::endl;
                break;
            case 3:
                munmap(ptr, st.st_size);
                close(fd);
                running = false;
                break;
        }
    }
    return 0;
}
