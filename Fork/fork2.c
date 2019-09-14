#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
        int fd;
        int pid;
        char msg1[] = "Test 1 2 3 ...\n";
        char msg2[] = "Hello, hello\n";

        if ((fd = creat("testfile.txt", 0644)) == -1)
                printf("no open\n");
                return 0;
        if (write(fd, msg1, strlen(msg1)) == -1)
                printf("no write\n");
                return 0;

        if ((pid = fork()) == -1)
                return 0;
        if (write(fd, msg2, strlen(msg2)) == -1)
                return 0;
        close(fd);
        return 1;
}
