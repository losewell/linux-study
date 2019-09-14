#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void child_code(void);
void parent_code(int);

void child_code()
{
        int delay;
        srand((unsigned)time(NULL));
        delay = rand()%10;
        printf("child %d here. will sleep for %d seconds\n", getpid(), delay);
        sleep(delay);
        printf("child done. about to exit\n");
        exit(0);
}

void parent_code(int childpid)
{
        int wait_rv;
        wait_rv = wait(NULL);
        printf("done waiting for %d. Wait returned: %d\n", childpid, wait_rv);
}

int main(int argc, char **argv)
{
        int newpid, i;

        if (argc != 2) {
                fprintf(stderr, "waitdemo usage: %s <numsofpid>\n", argv[0]);
                exit(0);
        }

        for (i = 0; i < atoi(argv[1]); i++) {
                if ((newpid = fork()) == -1)
                        perror("fork");
                else if (newpid == 0)
                        child_code();
                else
                        parent_code(newpid);
        }

//        parent_code(newpid);
        return 0;
}
